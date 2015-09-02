<?php

/**
 * Page callbacks for bgimage module.
 */

/**
 * Puts an image into the clipboard.
 */
function bgimage_tag($node) {
  global $user;
  if ($_SESSION['tagged_images']) {
    $tagged_images = explode(',', $_SESSION['tagged_images']);
    if (!in_array($node->nid, $tagged_images)) {
      // Add new image to clipboard.
      $tagged_images[] = $node->nid;
    }
  }
  else {
    // This is the first image the user has tagged.
    $tagged_images[] = $node->nid;
  }
  $_SESSION['tagged_images'] = implode(',', $tagged_images);

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
function bgimage_move_tagged() {
  $path = $_GET['p'];
  $tagged_images = explode(',', $_SESSION['tagged_images']);
  $autocomment = array();
  if ($path) {
    $path = bugguide_get_current_path($path);
    foreach ($tagged_images as $tagged_image) {
      $bgimage = node_load(array('nid' => $tagged_image, 'type' => 'bgimage'));
      if ($bgimage && bgimage_access('move', $bgimage)) {
        $parents = explode(',', $bgimage->parent);
        $old_parent = array_pop($parents);
        $data = db_fetch_object(db_query('SELECT title FROM {node} WHERE nid = %d', $old_parent));
        $link_to_old_parent = l($data->title, "node/$old_parent");
        db_query("UPDATE {node} SET changed = %d WHERE nid = %d", time(), $bgimage->nid);
        // Update parent_idx, the index of parents.
        db_query("UPDATE {bgimage} SET parent = '%s', parent_idx = '%s' WHERE nid = %d", $path, $path . ',', $bgimage->nid);

        watchdog("bgimage", "bgimage: moved '$bgimage->title' ($path)", l(t("view post"), "node/view/$bgimage->nid"));
        // Node 9410 is Frass.
        $autocomment[$tagged_image] = array();
        $autocomment[$tagged_image]['subject'] = $path == BG_FRASS_NID ? t('Frassed') : t('Moved');
        $autocomment[$tagged_image]['comment'] = "Moved from $link_to_old_parent.";
        $autocomment[$tagged_image]['pid'] = 0;
        $autocomment[$tagged_image]['nid'] = $bgimage->nid;
      }
    }

    // Erase clipboard.
    $_SESSION['tagged_images'] = NULL;

    // Post autocomment (posting of comment generates email automatically).
    if ($autocomment) {
      foreach ($autocomment as $fake_edit) {
        $target = $fake_edit['nid'];
        watchdog('bgimage', "post autocomment (nid = $target)", array(), WATCHDOG_NOTICE, l(t('view post'), "node/view/$target"));
        comment_post($fake_edit);
      }
    }
  }
  drupal_goto(referer_uri());
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
    $_SESSION['tagged_images'] = NULL;
    // Redirect to the last image in the clipboard so the series can be seen.
    drupal_goto('node/' . $node->nid);
  }

  // Could not link images. Return to where we were.
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}
