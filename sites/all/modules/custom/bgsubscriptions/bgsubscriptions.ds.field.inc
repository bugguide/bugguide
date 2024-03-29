<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render representative images for a bgpage node.
 */
function bgsubscriptions_subscriptions($field) {
  if (!isset($field['entity'])) {
    return;
  }
  $node = $field['entity'];
  $arg2 = subscriptions_arg(2);
  if (subscriptions_ui_can_subscribe() &&
    ((!variable_get('subscriptions_form_link_only', 0) && (empty($arg2) || $arg2 == 'view')) ||
      (variable_get('subscriptions_form_link_only', 0) && $arg2 == 'subscribe'))) {
    $subscription_form = drupal_get_form('bgsubscriptions_ui_node_form', $node);
    return drupal_render($subscription_form);
  }
}

/**
 * Bg subscriptions (subscribe and unsubscribe) logic.
 *
 * Most of the code comes from subscriptions_ui_node_form since
 * subscriptions contrib module doesn't support single subscribe button.
 *
 * @param $form
 * @param $form_state
 * @param $node
 *   Must be a valid node object.
 * @param $expand
 *   Force the fieldset to expand if TRUE.
 *
 * @return array|null
 *
 * @ingroup form
 * @ingroup hooks
 *
 * @see sites/all/modules/subscriptions/subscriptions_ui.module
 * @see https://www.drupal.org/project/issues/subscriptions
 *
 */
function bgsubscriptions_ui_node_form($form, &$form_state, $node, $expand = NULL) {
  global $user;
  $account = $user;

  if (subscriptions_node_is_blocked($node->nid)) {
    return NULL;
  }

  /** @var $blocked_types array */
  $blocked_types = variable_get('subscriptions_blocked_content_types', array());
  if (in_array($node->type, $blocked_types)) {
    if (!user_access('subscribe to all content types', $account)) {
      return NULL;
    }
    $is_blocked = TRUE;
  }

  $show_node_info = variable_get('node_submitted_' . $node->type, 1);
  $node_options = module_invoke_all('subscriptions', 'node_options', $account, $node);

  // Allow other modules to alter the node options.
  drupal_alter('bgsubscriptions_node_options', $node_options);

  if (!$node_options || !user_access('subscribe to content', $account)) {
    return array();
  }
  uasort($node_options, '_subscriptions_cmp_by_weight');

  foreach (array(
     db_query("SELECT sid, module, field, value, author_uid, send_interval, send_updates, send_comments FROM {subscriptions} WHERE module = :module AND field = :field AND value = :value AND recipient_uid = :recipient_uid", array(
       ':module' => 'node',
       ':field' => 'nid',
       ':value' => $node->nid,
       ':recipient_uid' => $account->uid
     ), array('fetch' => PDO::FETCH_ASSOC)),
     db_query("SELECT sid, module, field, value, author_uid, send_interval, send_updates, send_comments FROM {subscriptions} WHERE module = :module AND field <> :field AND recipient_uid = :recipient_uid", array(
       ':module' => 'node',
       ':field' => 'nid',
       ':recipient_uid' => $account->uid
     ), array('fetch' => PDO::FETCH_ASSOC)),
   ) as $result) {
    foreach ($result as $s) {
      $subscriptions[$s['field']][$s['value']][$s['author_uid']] = $s;
    }
  }
  $index = 1; ///< If we start with zero, get some value sent as 0 => 0
  $default_send_intervals = array();
  $default_subscriptions = array();
  foreach ($node_options as $field => $field_options) {
    foreach ($field_options as $option) {
      if (!is_array($option) || isset($option['#access']) && !$option['#access']) {
        continue;
      }
      if ((!$show_node_info || !variable_get('subscriptions_show_by_author_options', 1)) && isset($option['params']['author_uid']) && $option['params']['author_uid'] >= 0) {
        continue;
      }
      if ($option['params']['module'] == 'node' && $option['params']['field'] == 'type' && !empty($is_blocked)) {
        $option['name'] .= '&nbsp;' . SUBSCRIPTIONS_UNAVAILABLE;
      }
      $options[$index] = $option['name'];
      $params[$index] = $param = $option['params'] + array('author_uid' => -1);
      if (isset($subscriptions[$param['field']][$param['value']][$param['author_uid']])) {
        $default_subscriptions[] = $index;
        $default_send_intervals[$index] = $subscriptions[$param['field']][$param['value']][$param['author_uid']]['send_interval'];
      }
      $index++;
    }
  }
  $form['params'] = array(
    '#type' => 'value',
    '#value' => $params
  );
  $subscriptions_data = (!empty($default_subscriptions[0]) && !empty($options[$default_subscriptions[0]])) ? array(1) : array();
  $form['subscription'] = array(
    '#type' => 'value',
    '#value' => $subscriptions_data ? TRUE : FALSE,
  );
  $form['subscriptions'] = array('#type' => 'value', '#value' => $subscriptions_data);
  // Code is_blocked comes from subscriptions_ui.module.
  $subscribe_title = t('Subscribe') . (!empty($is_blocked) ? '&nbsp;' . SUBSCRIPTIONS_UNAVAILABLE : '');
  $unsubscribe_title = t('Unsubscribe');
  $subscribe_html = '<div><hr><button type="submit" id="edit-submit" href="" class="form-submit button is-small"><span class="icon"><span class="fa fa-envelope" aria-hidden="true"></span></span><span>' . $subscribe_title . '</span>';
  $node_types = node_type_get_types();
  $unsubscribe_html = '<div><hr><button type="submit" id="edit-submit" href="" class="button is-small"><span class="icon"><span class="fa fa-ban" aria-hidden="true"></span></span><span>' . $unsubscribe_title . '</span></button></button><p class="help">You are currently receiving email notifications for this ' . $node_types[$node->type]->{'name'} .'.</p>';
  $closing_html_subscribe_unsubscribe = '</div>';
  $subscription_markup = empty($subscriptions_data)
    ? $subscribe_html
    : $unsubscribe_html;
  // Custom code to create a personalized button for subscribing/un-subscribing.
  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => array('element-invisible')),
    '#prefix' => $subscription_markup,
    '#suffix' => $closing_html_subscribe_unsubscribe,
    '#markup' => '', // This line is required to force the element to render.
    '#weight' => 10,
  );
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['send_intervals'] = array('#type' => 'value', '#value' => $default_send_intervals);
  return $form;
}

/**
 * Node subscriptions node subform submit handler.
 *
 * @param array $form
 * @param array $form_state
 *
 * @ingroup form
 */
function bgsubscriptions_ui_node_form_submit(array $form, array &$form_state) {
  $recipient_uid = $form_state['values']['account']->uid;
  $default_send_intervals = $form_state['values']['send_intervals'];
  $subscription = $form_state['values']['subscription'];
  $params = $form_state['values']['params'][1];
  $args = array($params['module'], $params['field'], $params['value'], $params['author_uid'], $recipient_uid);
  // We get the value as the previous state that's why we would like the
  // opposite which is subscribing.
  if (!$subscription) {
    if (!empty($default_send_intervals[1])) {
      $args[] = $default_send_intervals[1];
    }
    call_user_func_array('subscriptions_write_subscription', $args);
  }
  // If it is subscribed then let's unsubscribe.
  else {
    subscriptions_delete($args['4'], $args['0'], $args['1'], $args['2'], $args['3']);
  }
  $form_state['redirect'] = str_replace('/subscribe', '', current_path());
}
