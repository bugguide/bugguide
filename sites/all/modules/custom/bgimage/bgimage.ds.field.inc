<?php
/**
 * @file
 * Display suite callbacks for bgimage module.
 */

/**
 * Callback to render photo number.
 */
function _bgimage_field_tag($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  return l('Add to clipboard', 'bgimage/tag/' . $node->nid, array('query' => array('destination' => current_path())));
}
/**
 * Callback to render photo number.
 */
function _bgimage_field_photo_number($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  return 'Photo #' . $node->nid;
}

/**
 * Callback to render a copyright statement.
 */
function _bgimage_field_copyright($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  $year = '';
  $user_name = '';

  // Extract the year when the photo was taken.
  $node_wrapper = entity_metadata_wrapper('node', $node->nid);
  $date_taken = $node_wrapper->field_bgimage_date->value();
  if (!empty($date_taken)) {
    $year = date('Y', $date_taken);
  }

  // Extract the user's name.
  $user_wrapper = entity_metadata_wrapper('user', $node->uid);
  $user_name = bguserfields_get_name($user_wrapper);
    return 'Copyright &copy; ' . $year . ' ' . l($user_name, 'user/' . $node->uid);
}

/**
 * Callback to render title and classification.
 *
 * The scientific name is built of the image's grandparent and parent.
 * For example, for image 334290, whose parents are
 * 3,878075,52,57,82,44054,29246,13329,44077,10981,334494, we extract
 * the scientific name of 334494 and 10981, which are schaefferalis
 * and Petrophila respectivelly. Finally, we render the name as
 * Petrophila schaefferalis.
 */
function _bgimage_field_title_classification($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  $parent_classification = '';
  $grandparent_classification = '';

  // Find the immediate parent's scientific name.
  $parent_nid = bg_get_parent_nid($node);
  $parent_node = node_load($parent_nid);
  if (!empty($parent_node)) {
    $bgpage_wrapper = entity_metadata_wrapper('node', $parent_node);
    $parent_classification = $bgpage_wrapper->field_scientific_name->value();
  }

  // Find the grandparent's scientific name.
  $grandparent_nid = bg_get_parent_nid($parent_node);
  $bgpage_gp_wrapper = entity_metadata_wrapper('node', $grandparent_nid);
  if (!empty($bgpage_gp_wrapper->id)) {
    $grandparent_classification = $bgpage_gp_wrapper->field_scientific_name->value();
  }

  return '<h2>' . check_plain($node->title) . ' &ndash; ' . $grandparent_classification . ' ' . $parent_classification . '</h2>';
}

/**
 * Callback to render related images.
 */
function _bgimage_field_related_images($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];

  $nids = bgimage_get_series($node->nid);
  if (!count($nids)) {
    return;
  }

  // Render as a list of image teasers.
  $output = '<div class="field-label">Images of this individual:</div>';

  // Render image thumbnails.
  $output .= '<div class="image-container">';
  $nodes = node_load_multiple($nids);
  foreach ($nodes as $related_node) {
    $node_wrapper = entity_metadata_wrapper('node', $related_node);
    if (isset($node_wrapper) && $node_wrapper->field_bgimage_image->value()) {
      $image_properties = array(
        'style_name' => 'bugguide_small',
        'path' => $node_wrapper->field_bgimage_image->file->value()->uri,
        'alt' => $node_wrapper->title->value(array('sanitize' => TRUE)),
        'title' => $node_wrapper->title->value(array('sanitize' => TRUE)),
        'attributes' => array('style' => 'margin: 10px;'),
      );
      // Add a border to the thumbnail of the current image.
      if ($related_node->nid == $node->nid) {
        $image_properties['attributes']['style'] .= 'border: 2px solid black;';
      }
      $image = theme('image_style', $image_properties);
      $output .= '<div style="float:left"><a href="' . url('node/' . $related_node->nid) . '" title="' . $node_wrapper->title->value(array('sanitize' => TRUE)) . '">' . $image . '</a></div>';
    }
  }
  $output .= '</div><div style="clear:both;">';
  $output .= l('Add all images to clipboard', 'bgimage/tag/' . $node->nid . '/all', array('query' => array('destination' => current_path())));
  return $output;
}

/**
 * Callback to render who placed an image.
 */
function _bgimage_field_placed_by($field) {
  if ($field['view_mode'] != 'homepage') {
    return;
  }

  $node = $field['entity'];

  $user_wrapper = entity_metadata_wrapper('user', $node->uid);
  $user_name = bguserfields_get_name($user_wrapper);
  $time_ago = format_interval((time() - $node->changed) , 2) . ' ago';
  $output = 'Placed by <a href="/user/' . $node->uid . '" title="View user profile.">' . $user_name . '</a> ' . $time_ago;

  $parent_nid = bg_get_parent_nid($node);
  if ($parent_nid) {
    $parent_node = node_load($parent_nid);
    $output .= ' in<br/><a href="/node/' . $parent_nid . '" title="' . check_plain($parent_node->title) . '">' . check_plain($parent_node->title) . '</a>';
  }

  return $output;
}
