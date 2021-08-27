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

  $link_title = format_plural($total_images, '1 image submitted by this contributor', '@count images submitted by this contributor');
  return l($link_title, '/user/' . $user->uid . '/images');
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

  $link_title = format_plural($total_comments, '1 comment submitted by this contributor', '@count comments submitted by this contributor');
  return l($link_title, '/user/' . $user->uid . '/comments');
}
