<?php
/**
 * @file
 * Display suite callbacks for bguserfields module.
 */

/**
 * Callback to render a link to contributed images.
 */
function _bguserfields_field_contributed_images($field) {
  $user = $field['entity'];
  $total_images = db_query('select count(*) from {node} where type = :type and uid = :uid', array(
    ':type' => 'bgimage',
    ':uid' => $user->uid,
  ))->fetchField();

  if ($total_images == 0) {
    return;
  }

  return l($total_images . ' images submitted by this contributor', '/user/' . $user->uid . '/images');
}

/**
 * Callback to render a link to contributed comments.
 */
function _bguserfields_field_contributed_comments($field) {
  $user = $field['entity'];
  $total_comments = db_query('select count(*) from {comment} where uid = :uid', array(
    ':uid' => $user->uid,
  ))->fetchField();

  if ($total_comments == 0) {
    return;
  }

  return l($total_comments . ' comments submitted by this contributor', '/user/' . $user->uid . '/comments');
}
