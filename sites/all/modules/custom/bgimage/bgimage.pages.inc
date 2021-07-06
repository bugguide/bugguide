<?php

/**
 * Page callbacks for bgimage module.
 */

/**
 * Puts an image into the clipboard.
 *
 * @param object $node
 *   The bgimage node that the user is viewing.
 * @param string $all
 *   Optional parameter to specify if we should add this image or
 *   all the images in the series to the Clipboard.
 */
function bgimage_tag($node, $all = NULL) {
  global $user;

  if (!$all) {
    $nids = array($node->nid);
  }
  else {
    $nids = bgimage_get_series($node->nid);
  }

  if (!empty($_SESSION['tagged_images'])) {
    $tagged_nids = explode(',', $_SESSION['tagged_images']);
    $nids = array_unique(array_merge($tagged_nids, $nids));
  }

  $_SESSION['tagged_images'] = implode(',', $nids);

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Removes all images from the clipboard.
 */
function bgimage_untag_all() {
  $_SESSION['tagged_images'] = NULL;

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Removes and image from the clipboard.
 */
function bgimage_untag($node) {
  if ($_SESSION['tagged_images']) {
    $tagged_images = explode(',', $_SESSION['tagged_images']);
    if (in_array($node->nid, $tagged_images)) {
      unset($tagged_images[array_search($node->nid, $tagged_images)]);
      if (count($tagged_images) == 0) {
        // That was the only tagged image.
        $_SESSION['tagged_images'] = NULL;
      }
      else {
        $_SESSION['tagged_images'] = implode(',', $tagged_images);
      }
    }
  }

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Menu callback. Move an image from the clipboard to this location.
 */
function bgimage_move_tagged($node) {
  global $user;

  $tagged_images = explode(',', $_SESSION['tagged_images']);
  $node_wrapper = entity_metadata_wrapper('node', $node);
  if ($node_wrapper->field_parent->value() || $node_wrapper->nid->value() == BG_ROOT_NID) {
    // Compute the new parent for the images being moved - their direct parent
    // will be $node.
    $path = $node_wrapper->nid->value();
    if ($node_wrapper->field_parent->value()) {
      $path = $node_wrapper->field_parent->value() . "," . $path;
    }
    $bgimage_nodes = node_load_multiple($tagged_images);
    foreach ($bgimage_nodes as $bgimage_node) {
      if (($user->uid == $bgimage_node->uid) || user_access('move all bgimages')) {
        $bgimage_wrapper = entity_metadata_wrapper('node', $bgimage_node);
        $parents = explode(',', $bgimage_wrapper->field_parent->value());
        $old_parent_nid = array_pop($parents);
        $old_parent_title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $old_parent_nid))->fetchField();

        // Update parent field for this image.
        $bgimage_wrapper->field_parent->set($path);
        $bgimage_wrapper->save();

        // Log a message and leave a comment registering the movement.
        watchdog("bgimage", 'bgimage: moved image @title to path @path', array(
          '@title' => $bgimage_node->title,
          '@path' => $path,
        ), WATCHDOG_NOTICE, l(t("view post"), "node/$bgimage_node->nid"));

        $comment = (object) array(
          'nid' => $bgimage_node->nid,
          'cid' => 0,
          'pid' => 0,
          'uid' => 1,
          'mail' => '',
          'is_anonymous' => 0,
          'homepage' => '',
          'status' => COMMENT_PUBLISHED,
          'subject' => $path == BG_FRASS_NID ? t('Frassed') : t('Moved'),
          'language' => LANGUAGE_NONE,
          'comment_body' => array(
            LANGUAGE_NONE => array(
              0 => array (
                'value' => 'Moved from ' . l($old_parent_title, "node/$old_parent_nid"),
                'format' => 1,
              ),
            ),
          ),
        );
        comment_submit($comment);
        comment_save($comment);
      }
      else {
        drupal_set_message(t('You do not have permission to move image <a href="!url">@title</a>', array(
          '!url' => 'node/' . $bgimage_node->nid,
          '@title' => $bgimage_node->title,
        )));
      }
    }

    // Notify the user.
    $message = format_plural(count($tagged_images), 'The image on the clipboard was successfully moved.', 'The images on the clipboard were successfully moved.');
    drupal_set_message($message);

    // Erase clipboard.
    $_SESSION['tagged_images'] = NULL;
  }

  drupal_goto('node/' . $node->nid);
}

/**
 * Adds tagged image(s) to an image series.
 *
 * The "link" link appears only if all images were submitted by the same user.
 */
function bgimage_link_tagged() {
  global $user;

  if (empty($_SESSION['tagged_images'])) {
    drupal_goto('<front>');
  }
  $tagged_list = $_SESSION['tagged_images'];
  $nids = explode(',', $tagged_list);

  // Discover whether the images are from the same user.
  $nodes = node_load_multiple($nids);
  $tagged_count = 0;
  $same_uid = TRUE;
  foreach ($nodes as $node) {
    $tagged_count++;
    if ($tagged_count == 1) {
      $uid = $node->uid;
    }
    else if ($uid != $node->uid) {
      $same_uid = FALSE;
    }
  }

  // Check and proceed to link them.
  if (($tagged_count > 1) && $same_uid && (($uid == $user->uid) || user_access('link all bgimages'))) {
    $weight = 0;
    foreach ($nodes as $node) {
      $dead_series_nid = db_query('SELECT series FROM {bgimage_series} WHERE nid = :nid', array(':nid' => $node->nid))->fetchCol();
      if ($dead_series_nid) {
        db_delete('bgimage_series')
          ->condition('series', $dead_series_nid)
          ->execute();
      }
      if (!isset($series)) {
        $series = $node->nid;
      }
      db_insert('bgimage_series')
        ->fields(array(
          'nid' => $node->nid,
          'series' => $series,
          'weight' => $weight,
        ))
        ->execute();
      $weight++;
    }
    watchdog('bgimage', "linked '$tagged_list'", array(), WATCHDOG_NOTICE, l(t('view post'), "node/" . $node->nid));
    drupal_set_message(t('Images were linked together.'));
    $_SESSION['tagged_images'] = NULL;
    // Redirect to the last image in the clipboard so the series can be seen.
    drupal_goto('node/' . $node->nid);
  }

  // Could not link images. Return to where we were.
  drupal_set_message(t('You must be the owner of all the images in the clipboard in order to link them.', 'warning'));
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Redirects to a form to add an image for a bgpage.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgimage_add_image($nid) {
  drupal_goto('node/add/bgimage/' . $nid);
}
