<?php

/**
 * @file
 * Subscriptions module mail gateway (cron functions).
 */

/**
 * Implementation of hook_cron().
 *
 * Takes items from {subscriptions_queue} and generates notification emails.
 */
function _subscriptions_mail_cron() {

  global $user, $language;
  _subscriptions_mail_module_load_include('templates.inc');

  $mails_allowed = variable_get('subscriptions_number_of_mails', 0);
  $from = _subscriptions_mail_site_mail();
  $single_count = $single_failed = $digest_count = $digest_failed = 0;
  $loaded_objects = array();
  $fields = array();

  // Strategy for cron:
  // Use a defined percentage of the total cron time (default: 50%), but leave at least 5s.
  $total_seconds = ini_get('max_execution_time');
  $total_seconds = (empty($total_seconds) ? 240 : $total_seconds);
  $lost_seconds = timer_read('page')/1000;
  $available_seconds = $total_seconds - $lost_seconds;
  $usable_seconds = min(array($available_seconds - 5, $total_seconds*subscriptions_mail_get_cron_percentage()/100));
  $watchdog = 'watchdog';  // disable automatic translation
  $watchdog_variables = array('@Subscriptions' => 'Subscriptions');
  //TEST: watchdog('cron', "Subscriptions has $available_seconds of $total_seconds seconds available.");
  if ($usable_seconds <= 0) {
    $watchdog_variables += array('@link' => url(SUBSCRIPTIONS_CONFIG_PATH, array('fragment' => 'edit-subscriptions-cron-percent')));
    if ($usable_seconds == 0) {
      $watchdog('cron', t('@Subscriptions cannot send any notifications because its <a href="@link">cron job time</a> is 0!', $watchdog_variables), NULL, WATCHDOG_WARNING);
    }
    else {
      $watchdog('cron', t('@Subscriptions cannot send any notifications because the cron run has less than 5 available seconds left!', $watchdog_variables), NULL, WATCHDOG_WARNING);
    }
  }

  while ((empty($mails_allowed) || $single_count + $digest_count < $mails_allowed)
          && timer_read('page')/1000 < $lost_seconds + $usable_seconds) {
    $result = db_query_range("SELECT * FROM {subscriptions_queue} WHERE suspended = 0 AND last_sent + send_interval < :time ORDER BY sqid", 0, 1, array(':time' => time()));
    if (!($queue_item = $result->fetchAssoc())) {
      break;  // No more ready queue items, terminate loop.
    }

    if (!$subscriber = user_load($queue_item['uid'])) {
      $watchdog('subscriptions', t('Subscriber %uid not found.', array('%uid' => $queue_item['uid'])), NULL, WATCHDOG_WARNING);
      continue;
    }

    $saved_user     = $user;
    $saved_language = $language;
    drupal_save_session(FALSE);
    // Clear the term cache to avoid getting a different user's set of terms.
    entity_load('taxonomy_term', array(), array(), TRUE);
    $lang_code = $language->language;
    $user      = $subscriber;

    $digest_data                      = array('subs' => array('type' => 'digest'));
    $watchdog_variables['%user_name'] = $user->name;

    do {  // once and repeat while adding to a digest
      $watchall = variable_get('subscriptions_watchall', 0);
      if (!$user->status) {
        if ($watchall) {
          $watchdog('subscriptions', t('Subscription of blocked user %user_name ignored.', $watchdog_variables), NULL, WATCHDOG_DEBUG);
        }
      }
      elseif (!$user->access && !variable_get('subscriptions_mail_unaccessed_users', FALSE)) {
        if ($watchall) {
          $watchdog('subscriptions', t('Subscription of never-logged-in user %user_name ignored.', $watchdog_variables), NULL, WATCHDOG_DEBUG);
        }
      }
      else {
        $queue_item['mail'] = $user->mail;
        /** @var $load_function string */
        $load_function = $queue_item['load_function'];
        $load_args     = $queue_item['load_args'];
        if (!isset($loaded_objects[$user->uid][$load_function][$load_args]) && $load_function($queue_item)) {
          $object = $queue_item['object'];
          $access = module_invoke_all('subscriptions', 'access', $load_function, $load_args, $object);
          // Allow other modules to alter the data.
          drupal_alter('subscriptions_access', $access);

          // One FALSE vote is enough to deny. Also, we need a non-empty array.
          $allow = !empty($access) && array_search(FALSE, $access) === FALSE;
          if (!$allow && $watchall) {
            $watchdog('subscriptions', t("User %user_name was denied access to %load(!args).", $watchdog_variables + array('%load' => $load_function, '!args' => filter_xss(serialize($load_args)))), NULL, WATCHDOG_DEBUG);
            $watchall = FALSE;
          }
          $loaded_objects[$user->uid][$load_function][$load_args] = $allow ? $object : FALSE;
        }
        if (empty($loaded_objects[$user->uid][$load_function][$load_args])) {
          if ($watchall) {
            $watchdog('subscriptions', t('User %user_name was unable or not allowed to %load(!args).', $watchdog_variables + array('%load' => $load_function, '!args' => filter_xss(serialize($load_args)))), NULL, WATCHDOG_DEBUG);
          }
        }
        else {
          $object    = $loaded_objects[$user->uid][$load_function][$load_args];
          $module    = $queue_item['module'];
          $ori_field = $field = $queue_item['field'];
          $ori_value = $value = $queue_item['value'];
          if (!isset($fields[$lang_code][$module])) {
            $fields[$lang_code][$module] = module_invoke_all('subscriptions', 'fields', $module);
          }
          $data_function = $fields[$lang_code][$module][$field]['data_function'];
          $mailmod       = (empty($fields[$lang_code][$module][$field]['mail_module']) ? 'subscriptions_mail' : $fields[$lang_code][$module][$field]['mail_module']);
          $mailkey       = $fields[$lang_code][$module][$field]['mailkey'];
          if ($mailkey_altered = module_invoke_all('subscriptions', 'mailkey_alter', $mailkey, $object, $queue_item)) {
            $mailkey = $mailkey_altered[0];
          }
          $digest = $queue_item['digest'] > 0 || $queue_item['digest'] == -1 && _subscriptions_get_setting('digest', 0) > 0;
          //$show_node_info = (isset($object->type) ? variable_get('node_submitted_' . $object->type, TRUE) : TRUE);

          $data = array(
            'subs' => array(
              'type'             => $fields[$lang_code][$module][$field]['subs_type'],
              'unsubscribe_path' => "s/del/$module/$ori_field/$ori_value/" . $queue_item['author_uid'] . '/' . $queue_item['uid'] . '/' . md5(drupal_get_private_key() . $module . $ori_field . $ori_value . $queue_item['author_uid'] . $queue_item['uid']),
            ),
            'user' => user_load(!empty($object->revision_uid) ? $object->revision_uid : $object->uid),
          );
          $data_function($data, $object, $queue_item);
          drupal_alter('subscriptions_data', $data, $object, $queue_item);
          //mail_edit_format($values['subscriptions_comment_body'], $data + array('comment' => $comment), array('language' => $language));

          if ($digest) {
            $digest_data                                                         = subscriptions_mail_digest_add_item($digest_data, $mailmod, $mailkey, $data, $user);
            $digest_data['subs']['send_intervals'][$queue_item['send_interval']] = $queue_item['send_interval'];
          }
          else {
            (_subscriptions_mail_send($mailmod, $mailkey, $queue_item['name'], $queue_item['mail'], $from, $queue_item['uid'], array($queue_item['send_interval']), $data)
              ? ++$single_count
              : ++$single_failed);
          }
        }
      }
      db_delete('subscriptions_queue')
        ->condition('load_function', $queue_item['load_function'])
        ->condition('load_args', $queue_item['load_args'])
        ->condition('uid', $queue_item['uid'])
        ->execute();

      if (!empty($digest)) {
        // Get next ready queue item for this user.
        $result = db_query_range('SELECT * FROM {subscriptions_queue} WHERE uid = :uid AND last_sent + send_interval < :send_interval ORDER BY sqid', 0, 1, array(':uid' => $user->uid, ':send_interval' => time()));
        if (!($queue_item = $result->fetchAssoc())) {
          // No more ready queue items for this user, finish off this digest.
          (_subscriptions_mail_send($mailmod, SUBSCRIPTIONS_DIGEST_MAILKEY, $digest_data['subs']['name'], $digest_data['subs']['mail'], $from, $digest_data['subs']['uid'], $digest_data['subs']['send_intervals'], $digest_data)
            ? ++$digest_count
            : ++$digest_failed);
          $digest      = FALSE;
          $digest_data = array('subs' => array('type' => 'digest'));
        }
      }
    } while (!empty($digest));

    $user     = $saved_user;
    $language = $saved_language;
    drupal_save_session(TRUE);
  }

  if (module_exists('taxonomy')) {
    // Clear the term cache again for the next cron client.
    entity_load('taxonomy_term', array(), array(), TRUE);
  }

  if ($single_count + $digest_count + $single_failed + $digest_failed > 0) {
    $current_seconds = timer_read('page')/1000;
    $variables = $watchdog_variables + array(
      '!single_count'      => $single_count,
      '!digest_count'      => $digest_count,
      '!single_failed'     => $single_failed,
      '!digest_failed'     => $digest_failed,
      '!used_seconds'      => round($current_seconds - $lost_seconds),
      '!total_seconds'     => $total_seconds,
      '!remaining_items'   => db_query("SELECT COUNT(*) FROM {subscriptions_queue} WHERE last_sent + send_interval < :send_interval AND suspended = 0", array(':send_interval' => REQUEST_TIME))->fetchField(),
      '!suspended_items'   => db_query("SELECT COUNT(*) FROM {subscriptions_queue} WHERE last_sent + send_interval < :send_interval AND suspended <> 0", array(':send_interval' => REQUEST_TIME))->fetchField(),
      '!remaining_seconds' => round($total_seconds - $current_seconds),
      '%varname'           => 'subscriptions_mail_trash_silently',
      '!cron'              => 'cron',
    );
    if (variable_get('subscriptions_mail_trash_silently', 0)) {
      $message = t('@Subscriptions DISCARDED !single_count single and !digest_count digest notifications in !used_seconds of !total_seconds seconds, due to the %varname variable being set.', $variables);
    }
    elseif ($single_failed > 0 || $digest_failed > 0) {
      $message = t('@Subscriptions FAILED !single_failed single and !digest_failed digest notifications, sent !single_count single and !digest_count digest notifications in !used_seconds of !total_seconds seconds.', $variables);
    }
    else {
      $message = t('@Subscriptions sent !single_count single and !digest_count digest notifications in !used_seconds of !total_seconds seconds.', $variables);
    }
    $message .= ' ' . t('!remaining_items queue items remaining (plus !suspended_items suspended), !remaining_seconds seconds left for other !cron client modules.', $variables);
    $watchdog('cron', $message, NULL);

    _subscriptions_mail_check_baseurl(FALSE);
  }
}

/**
 * Formats an item and adds it to the digest data.
 *
 * @param array $digest_data
 * @param string $mailmod
 * @param string $mailkey
 * @param array $data
 * @param object $user
 *
 * @return array
 *   The updated $digest_data array.
 */
function subscriptions_mail_digest_add_item($digest_data, $mailmod, $mailkey, $data, $user) {
  $params = array(
    'data' => $data,
    'account' => $user,
    'object' => NULL,
    'context' => array(
      'mail_edit' => 'DIGEST',
    ),
  );

  // This code is adapted from drupal_mail() and simulates mailing the item.
  // We probably need to provide all the data in order to not surprise any
  // third-party module that implements hook_mail() or hook_mail_alter().
  $message = array(
    'id'       => $mailmod . '_' . $mailkey,
    'module'   => $mailmod,
    'key'      => $mailkey,
    'to'       => '',
    'from'     => '', //isset($from) ? $from : $default_from,
    'language' => user_preferred_language($user),
    'params'   => $params,
    'subject'  => '',
    'body'     => array()
  );
  $headers = array(
    'MIME-Version'              => '1.0',
    'Content-Type'              => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
    'Content-Transfer-Encoding' => '8Bit',
    'X-Mailer'                  => 'Drupal'
  );
  $headers['From'] = $headers['Sender'] = $headers['Return-Path'] = variable_get('site_mail', ini_get('sendmail_from'));
  $message['headers'] = $headers;
  if (function_exists($function = $mailmod . '_mail')) {
    $function($mailkey, $message, $params);
  }

  // Invoke hook_mail_alter() to allow all modules to alter the resulting e-mail.
  drupal_alter('mail', $message);

  // Save the formatted body and return the modified $data.
  $data['subs']['formatted_item'] = $message['body'][0];
  $item_data = $data;

  $digest_data['subs']['items'][] = $item_data;
  $digest_data['subs'] += array(
    'name' => $item_data['subs']['name'],
    'mail' => $item_data['subs']['mail'],
    'uid' => $item_data['subs']['uid'],
  );
  return $digest_data;
}

/**
 * Implements hook_mail().
 *
 * @param $key
 * @param $message
 * @param $params
 */
function subscriptions_mail_mail($key, &$message, $params) {
  global $base_url;

  $url = parse_url($base_url);
  $list_id = variable_get('site_name', '') . ' ' . t('Subscriptions') . ' <subscriptions.' . $url['host'] . '>';
  $message['headers']['List-Id'] = $list_id;
  //dpm($message, "subscriptions_mail_mail($key)");
}


/**
 * Sends the notification by mail.
 *
 * @param $module
 * @param $mailkey
 * @param $name
 * @param $to
 * @param $from
 * @param $uid
 * @param $send_intervals
 * @param $data
 *
 * @return bool|null
 */
function _subscriptions_mail_send($module, $mailkey, $name, $to, $from, $uid, $send_intervals, $data) {
  global $user;

  if (variable_get('subscriptions_mail_trash_silently', 0)) {
    // Block notification mail; useful for staging and development servers.
    return NULL;
  }

  $mail_success = drupal_mail($module, $mailkey, $to, user_preferred_language($user), array(
    'data' => $data,
    'account' => $user,
    'object' => NULL,
  ), $from, TRUE);

  $to = check_plain($to);
  $watchdog = 'watchdog';
  $watchdog_params = array(
    '%name'        => $name,
    '!address'     => "<a href='mailto:$to'>$to</a>",
    '!result'      => 'result',
    '%result'      => $mail_success['result'],
    '!drupal_mail' => l('drupal_mail', 'http://api.drupal.org/api/search/7/drupal_mail'),
  );
  if (variable_get('subscriptions_watchall', 0)) {
    $watchdog('subscriptions', t('Notification for %name (!address) passed on to !drupal_mail(), !result=[%result].', $watchdog_params), NULL, WATCHDOG_DEBUG);
  }

  if (!empty($mail_success['result'])) {
    if (variable_get('subscriptions_watchgood', 1)) {
      $watchdog('subscriptions', t('Notification sent to...'), NULL);
    }
    foreach ($send_intervals as $send_interval) {
      db_merge('subscriptions_last_sent')
        ->key(array(
          'uid'           => $uid,
          'send_interval' => $send_interval,
        ))
        ->fields(array(
          'last_sent'     => REQUEST_TIME,
        ))
        ->execute();
    }
    return TRUE;
  }
  $watchdog('subscriptions', t('Error e-mailing notification to %name (!address).', $watchdog_params), NULL, WATCHDOG_ERROR);
  return FALSE;
}

/**
 * Implements hook_mail_alter().
 *
 * Optionally change links to use HTTPS, but only for Subscriptions mails.
 *
 * @param $message
 */
function _subscriptions_mail_mail_alter(array &$message) {
  global $user;
  static $site_url = NULL;
  static $replacement;

  if (!isset($site_url)) {
    $site_url = url('', array('absolute' => TRUE));
    if (_subscriptions_get_setting('secure_links', $user) > 0) {
      if (strpos($site_url, 'http:') === 0) {
        $site_url = $replacement[$site_url] = 'https:' . substr($site_url, 5);
      }
    }
    else {
      if (strpos($site_url, 'https:') === 0) {
        $site_url = $replacement[$site_url] = 'http:' . substr($site_url, 6);
      }
    }
  }

  if (!empty($replacement)) {
    $msg = strtr($message['body'][0], $replacement);
    while (preg_match("#(?P<before>(.*)(<[aA] +)(href|HREF)=([\"']))/(?P<after>.*)$#sAD", $msg, $matches)) {
      $msg = $matches['before'] . $site_url . $matches['after'];
    }
    while (preg_match("#(?P<before>(.*)<(img|IMG) +(src|SRC)=([\"']))/(?P<after>.*)$#sAD", $msg, $matches)) {
      $msg = $matches['before'] . $site_url . $matches['after'];
    }
    $message['body'][0] = $msg;
  }

  $message['body'][0] = _subscriptions_mail_add_mailkey($message['body'][0], $message['id'], $message['language']->language);

  /* Comment this line for debugging...
  dpm($message, 'drupal_mail() is disabled in subscriptions_mail_mail_alter(); this would be sent');
  $message['to'] = '';
  /**/
}

/**
 * Helper function to add the mailkey if enabled.
 */
function _subscriptions_mail_add_mailkey($body, $mailkey, $language = NULL) {
  if (variable_get('subscriptions_showmailkeys', 0)) {
    $prefix = substr($body, 0, 2);
    $prefix = ( $prefix[1] == ' ' ? $prefix : '' );
    $body .= $prefix . $mailkey . (empty($language) ? '' : '/' . $language) . "\n";
  }
  return $body;
}

