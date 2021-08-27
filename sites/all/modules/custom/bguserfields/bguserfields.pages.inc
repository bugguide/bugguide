<?php

/**
 * Page callbacks for the bguserfields module.
 */

/**
 * "Zaps" a spam user.
 *
 * @param string $uid
 *   The uid of the user to zap.
 */
function zap_user($uid) {
  if (!isset($uid) || !is_numeric($uid)) {
    return;
  }

  $uid = (int) $uid;
  if ($uid <= 1) {
    return;
  }

  // Remove any user session, but try to get their IP address first.
  $ip = db_query('SELECT hostname FROM {sessions} WHERE uid = :uid', array(':uid' => $uid))->fetchField();
  $ip = $ip ? $ip : '';
  db_delete('sessions')->condition('uid', $uid)->execute();

  // Rename user's email address, reset user's password.
  $mail = db_query('SELECT mail FROM {users} WHERE uid = :uid', array(':uid' => $uid))->fetchField();
  $mail = str_replace('@', 'bababa@', $mail);
  require_once DRUPAL_ROOT . '/includes/password.inc';
  $pass = user_hash_password(user_password());
  $data = 'N;';
  // Set 'status' to 0 so that the user's profile page is not visible.
  db_update('users')
    ->fields(array(
      'pass' => $pass,
      'mail' => $mail,
      'signature' => '',
      'data' => $data,
      'status' => 0,
    ))
    ->condition('uid', $uid)
    ->execute();

  // Generate email content for the administrator and spam zapper as we work
  // through setting the spammer's content to hidden in the database.
  $body = $ip . '\r\n\r\n';
  // We'll generate commands that can undo what we've done.
  $undo = '\r\nUndo the above with the following drush and SQL commands\r\n\r\n';

  // Unpublish any node by the spammer. (Going through node_load/node_save lets
  // core take care of updating all the right tables, which with revisioning -
  // even when it's turned off - can be a little tricky in this case.)
  $nids = db_query('SELECT nid FROM {node} WHERE uid = :uid', array(':uid' => $uid))->fetchCol();
  $nodes = node_load_multiple($nids);
  if (count($nodes) > 0) {
    $undo .= 'Copy the following node commands into a file and use "drush php:script".\r\n';
    $undo .= '<?php\r\n';
    foreach($nodes as $node) {
      $body .= 'https://bugguide.net/node/' . $node->nid . '\r\n';
      $node->status = 0;
      node_save($node);
      $undo .= '  $node = node_load(' . $node->nid . ');\r\n';
      $undo .= '  $node->status = 1;\r\n';
      $undo .= '  node_save($node);\r\n';
      $undo .= '  drush_print("Updated node ' . $node->nid . '");\r\n';
    }
  }

  // Unpublish any comments by the spammer.
  $result = db_query("SELECT cid, nid FROM {comment} WHERE uid = :uid", array(':uid' => $uid));
  while ($data = $result->fetchAssoc()) {
    $body .= 'http://bugguide.test/node/' . $data['nid'] . '#comment-' . $data['cid'] . '\r\n';
    $undo .= 'UPDATE comment SET status = 1 WHERE cid = ' . $data['cid'] . ';\r\n';
  }
  db_update('comment')
    ->fields(array('status' => 0))
    ->condition('uid', $uid)
    ->execute();

  $body_with_undo = $body . $undo;

  watchdog('user', 'zapped user ' . $uid . ' as a spammer');

  global $user;
  $admin_mail = db_query("SELECT mail FROM {users} WHERE uid = 1")->fetchField();
  $zapper_mail = $user->mail;
  $subject = 'Spam by user ' . $uid . ' zapped by ' . $user->name;
  $from = variable_get('site_mail', ini_get('sendmail_from'));
  $headers = array(
    'From' => $from,
    'Reply-to' => $from,
    'X-Mailer' => 'BugGuide.net',
    'Return-path' => $from,
    'Errors-to' => 'jvandyk@iastate.edu',
  );
  bguserfields_send_mail($from, $admin_mail, $subject, $body_with_undo, $headers);
  bguserfields_send_mail($from, $zapper_mail, $subject, $body, $headers);

  drupal_goto('user/'. $uid);
}
