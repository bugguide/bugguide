<?php
/**
 * @file
 * Display suite callbacks for bgimage module.
 */
/**
 * Callback to render photo number.
 */
function _bgimage_field_photo_number($field) {
  $node = $field['entity'];
  return 'Photo #' . $node->nid;
}

/**
 * Callback to render a copyright statement.
 */
function _bgimage_field_copyright($field) {
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
  if ($user_wrapper) {
    $user_name = $user_wrapper->field_user_full_name->value();
    if (empty($user_name)) {
      $user_name = $user_wrapper->name->value();
    }
  }
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
  $node = $field['entity'];
  $classification = '';

  // Find the immediate parent's scientific name.
  $parent_nid = bg_get_parent_nid($node);
  $parent_node = node_load($parent_nid);
  $bgpage_wrapper = entity_metadata_wrapper('node', $parent_node);
  $parent_classification = $bgpage_wrapper->field_scientific_name->value();

  // Find the grandparent's scientific name.
  $grandparent_nid = bg_get_parent_nid($parent_node);
  $bgpage_gp_wrapper = entity_metadata_wrapper('node', $grandparent_nid);
  $grandparent_classification = $bgpage_gp_wrapper->field_scientific_name->value();

  return '<h2>' . check_plain($node->title) . ' &ndash; ' . $grandparent_classification . ' ' . $parent_classification . '</h2>';
}

/**
 * Callback to render related images.
 */
function _bgimage_field_related_images($field) {
  $node = $field['entity'];

  // First, check if there are related images.
  $result = db_query('SELECT nid, series FROM {bgimage_series} WHERE nid = :nid', array(':nid' => $node->nid))->fetchAssoc();
  if (!count($result)) {
    return;
  }

  // Then, find out if the series is based on this nid or a different one.
  $nid = $result['nid'];
  if ($nid != $result['series']) {
    $nid = $result['series'];
  }

  // Next, extract the whole series of nids.
  $nids = db_query('SELECT nid FROM {bgimage_series} WHERE series = :nid', array(':nid' => $nid))->fetchCol();

  // Render as a list of image teasers.
  $output = '<div class="field-label">Images of this individual:</div>';
  $output .= '<div class="image-container">';
  $nodes = node_load_multiple($nids);
  foreach ($nodes as $related_node) {
    $node_wrapper = entity_metadata_wrapper('node', $related_node);
    $image_properties = array(
      'style_name' => 'thumbnail',
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
  return $output . '</div><div style="clear:both;">';
}
