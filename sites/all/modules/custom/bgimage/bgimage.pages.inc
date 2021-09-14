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
function bgimage_clip($node, $all = NULL) {
  global $user;

  if (!$all) {
    $nids = array($node->nid);
  }
  else {
    $nids = bgimage_get_series($node->nid);
  }


  if (!empty($_SESSION['clipboard_images'])) {
    $clipboard_nids = explode(',', $_SESSION['clipboard_images']);
    $nids = array_unique(array_merge($clipboard_nids, $nids));
  }

  $_SESSION['clipboard_images'] = implode(',', $nids);

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Removes all images from the clipboard.
 */
function bgimage_unclip_all() {
  $_SESSION['clipboard_images'] = NULL;

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Removes an image from the clipboard.
 */
function bgimage_unclip($node) {
  if ($_SESSION['clipboard_images']) {
    $clipped_images = explode(',', $_SESSION['clipboard_images']);
    if (in_array($node->nid, $clipped_images)) {
      unset($clipped_images[array_search($node->nid, $clipped_images)]);
      if (count($clipped_images) == 0) {
        // That was the only clipped image.
        $_SESSION['clipboard_images'] = NULL;
      }
      else {
        $_SESSION['clipboard_images'] = implode(',', $clipped_images);
      }
    }
  }

  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Menu callback. Move an image from the clipboard to this location.
 */
function bgimage_move_clipped($node, $quiet = false) {
  global $user;

  $clipboard_images = explode(',', $_SESSION['clipboard_images']);
  $node_wrapper = entity_metadata_wrapper('node', $node);
  if ($node_wrapper->field_parent->value() || $node_wrapper->nid->value() == BG_ROOT_NID) {
    // Compute the new parent for the images being moved - their direct parent
    // will be $node.
    $path = $node_wrapper->nid->value();
    if ($node_wrapper->field_parent->value()) {
      $path = $node_wrapper->field_parent->value() . "," . $path;
    }
    $bgimage_nodes = node_load_multiple($clipboard_images);
    foreach ($bgimage_nodes as $bgimage_node) {
      if (($user->uid == $bgimage_node->uid) || user_access('move all bgimages')) {
        $bgimage_wrapper = entity_metadata_wrapper('node', $bgimage_node);
        $parents = explode(',', $bgimage_wrapper->field_parent->value());
        $old_parent_nid = array_pop($parents);
        $old_parent_title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $old_parent_nid))->fetchField();

        // Update parent field for this image.
        $bgimage_wrapper->field_parent->set($path);
        $bgimage_wrapper->save();

        // If we're doing a quiet move then don't produce an autocomment. Moves
        // to Frass are never quiet.
        if ($quiet && $node_wrapper->nid->value() != BG_FRASS_NID) {
          continue;
        }

        // Log a message and leave a comment registering the movement.
        watchdog("bgimage", 'bgimage: moved image @title to path @path', array(
          '@title' => $bgimage_node->title,
          '@path' => $path,
        ), WATCHDOG_NOTICE, l(t("view post"), "node/$bgimage_node->nid"));

        $comment = (object) array(
          'nid' => $bgimage_node->nid,
          'cid' => 0,
          'pid' => 0,
          'uid' => $user->uid,
          'mail' => '',
          'is_anonymous' => 0,
          'homepage' => '',
          'status' => COMMENT_PUBLISHED,
          'subject' => $path == BG_FRASS_NID ? t('Frassed') : t('Moved'),
          'language' => LANGUAGE_NONE,
          'comment_body' => array(
            LANGUAGE_NONE => array(
              0 => array (
                'value' => 'Moved from ' . l($old_parent_title, "node/$old_parent_nid") . '.',
                'format' => 'f',
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
    $message = format_plural(count($clipboard_images), 'The image on the clipboard was successfully moved.', 'The images on the clipboard were successfully moved.');
    drupal_set_message($message);

    // Erase clipboard.
    $_SESSION['clipboard_images'] = NULL;
  }

  drupal_goto('node/' . $node->nid);
}

/**
 * Adds clipboard image(s) to an image series.
 *
 * The "link" link appears only if all images were submitted by the same user.
 */
function bgimage_link_clipped() {
  global $user;

  if (empty($_SESSION['clipboard_images'])) {
    drupal_goto('<front>');
  }
  $clipped_list = $_SESSION['clipboard_images'];
  $nids = explode(',', $clipped_list);

  // Discover whether the images are from the same user.
  $nodes = node_load_multiple($nids);
  $clipped_count = 0;
  $same_uid = TRUE;
  foreach ($nodes as $node) {
    $clipped_count++;
    if ($clipped_count == 1) {
      $uid = $node->uid;
    }
    else if ($uid != $node->uid) {
      $same_uid = FALSE;
    }
  }

  // Check and proceed to link them.
  if (($clipped_count > 1) && $same_uid && (($uid == $user->uid) || user_access('link all bgimages'))) {
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
    watchdog('bgimage', "linked '$clipped_list'", array(), WATCHDOG_NOTICE, l(t('view post'), "node/" . $node->nid));
    drupal_set_message(t('Images were linked together.'));
    $_SESSION['clipboard_images'] = NULL;
    // Redirect to the last image in the clipboard so the series can be seen.
    drupal_goto('node/' . $node->nid);
  }

  // Could not link images. Return to where we were.
  drupal_set_message(t('You must be the owner of all the images in the clipboard in order to link them.'), 'warning');
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}

/**
 * Unlinks the images in an image series.
 *
 * @param int $nid
 *   The nid of one of the images in the series to be unlinked.
 */
function bgimage_unlink_image_series($nid) {
  global $user;
  $nid = (int) $nid;

  $node = node_load($nid);
  if ($node && (($node->uid == $user->uid) || user_access("link all bgimages"))) {
    $dead_series_nid = db_query('SELECT series FROM {bgimage_series} WHERE nid = :nid', array(':nid' => $nid))->fetchCol();
    if ($dead_series_nid) {
      db_delete('bgimage_series')
        ->condition('series', $dead_series_nid)
        ->execute();
      watchdog('bgimage', "Unlinked series '$dead_series_nid[0]'", array(), WATCHDOG_NOTICE, l(t("view post"), 'node/' . $nid));
      drupal_set_message(t('Images were unlinked.'));
      drupal_goto('node/' . $nid);
    }
  }

  // Something wasn't right, most likely a permission error.
  drupal_set_message(t('You must be the owner of these images in order to unlink them.'), 'warning');
  drupal_goto('node/' . $nid);
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

/**
 * Display a pager of all of the images of this node and all of its
 * descendants, ordered by date submitted and formatted in teaser form.
 *
 * @param $nid
 *   The image listing will be restricted to this node and its descendants.
 */
function bgimage_recent($nid) {
  $nid = (int) $nid;
  if (!$nid) {
    drupal_goto('<front>');
  }

  $parent = node_load($nid);
  if (!$parent || $parent->type != 'bgpage') {
    watchdog('bgimage', "bgimage_recent() cannot load node nid '%nid'", array('%nid' => $nid), WATCHDOG_ERROR);
    drupal_goto('<front>');
  }

  // The title will be completed in bg_preprocess_page, where a markuped taxon
  // will be added.
  drupal_set_title(t('Recent Images Placed in '));

  $path = isset($parent->field_parent[LANGUAGE_NONE][0]['value']) ? $parent->field_parent[LANGUAGE_NONE][0]['value'] : '';
  $path = $path ? $path . ',' . $nid : $nid;

  $query = db_select('node', 'n')->extend('PagerDefault');
  $query->addField('n', 'nid');
  $query->join('field_data_field_parent', 'p', 'n.nid = p.entity_id');
  $query->condition('n.type', 'bgimage')
        ->condition('n.status', 1)
        ->condition('p.field_parent_value', $path . '%', 'LIKE')
        ->orderBy('n.created', 'DESC');

  // Behind the scenes PagerDefault has added a limit and offset to our query
  // (partly based on any 'page' query parameter in the current url) - get the
  // current batch of nids.
  $result = $query->execute();

  $output = '';
  $images_found = FALSE;
  foreach ($result as $record) {
    $node = node_load($record->nid);
    if (!$node) {
      continue;
    }
    $node_array = node_view($node, 'teaser');
    $output .= drupal_render($node_array);
    $images_found = TRUE;
  }

  if ($images_found) {
    // TODO: a feed for every taxon.
    // $feed_url = url('rss.xml', array('absolute' => TRUE));
    // drupal_add_feed($feed_url, variable_get('site_name', 'Drupal') .' '. t('RSS'));
    $output .= '<p>' . theme('pager') . '</p>';
  }
  else {
    $output .= '<br>There are currently no images to display here.';
  }

  return $output;
}
