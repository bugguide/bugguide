<?php
/**
 * @file
 * Display suite callbacks for bgimage module.
 */

/**
 * Callback to add an image to the clipboard.
 */
function _bgimage_field_clip($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }
  
  if (!user_access('use image clipboard')) {
    return;
  }

  $node = $field['entity'];
  return l(
    'Add to clipboard', 
    'bgimage/clip/' . $node->nid,
    array(
      'attributes' => array(
        'class' => 'button is-small',
        'role' => 'button',
        ),
      'query' => array(
        'destination' => current_path()
        )
    )
  );
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
  if (!in_array($field['view_mode'], array('full', 'recent'))) {
    return;
  }

  $node = $field['entity'];

  // Extract the year when the photo was taken.
  $year = '';
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $date_taken = $node_wrapper->field_bgimage_date->value();
  if (!empty($date_taken)) {
    $year = date('Y', $date_taken);
  }

  // Check if a copyright owner was specified.
  $copyright_owner = $node_wrapper->field_bgimage_copyright_owner->value();
  if (!$copyright_owner) {
    $user_wrapper = entity_metadata_wrapper('user', $node->uid);
    $user_name = bguserfields_get_name($user_wrapper);
    // Return as a link to the user.
    $copyright_owner = l($user_name, 'user/' . $node->uid);
  }

  return 'Copyright &copy; ' . $year . ' ' . $copyright_owner;
}

/**
 * Callback to render title and classification.
 *
 * If the taxon level of the $field's node is at least Genus (even if it's a No
 * Taxon node), then we display the scientific name of the node: genus, species,
 * and/or subspecies, depending on the taxon level of the node; otherwise only
 * the node title is displayed.
 */
function _bgimage_field_title_classification($field) {
  global $TAXON_NAMES;
  global $TAXON_IDS;
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  $parent_nid = bg_get_parent_nid($node);
  if (!$parent_nid) {
    return '<h2>' . check_plain($node->title) . '</h2>';
  }

  $parent = node_load($parent_nid);
  if (!empty($parent->field_taxon) && isset($parent->field_taxon[LANGUAGE_NONE][0]['value'])) {
    $taxon_id = $parent->field_taxon[LANGUAGE_NONE][0]['value'];
  }
  else {
    return '<h2>' . check_plain($node->title) . '</h2>';
  }

  // If the current taxon id is genus or higher, include the genus in the title;
  // if it's species or higher, include genus and species;
  // if it's subspecies or higher, include genus species and subspecies;
  // otherwise don't include the taxon in the title.
  $scientific_name = '';
  if ($taxon_id >= $TAXON_IDS['Genus']) {
    $parent_nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'bgpage')
      ->propertyCondition('nid', $parent_nids, 'IN')
      ->fieldOrderBy('field_taxon', 'value', 'DESC');
    $result = $query->execute();
    if (isset($result['node'])) {
      $parent_nids = array_keys($result['node']);
      foreach ($parent_nids as $parent_nid) {
        $parent_node = node_load($parent_nid);
        if (!empty($parent_node->field_taxon) &&
            isset($parent_node->field_taxon[LANGUAGE_NONE][0]['value'])) {
          // The spacing on the taxa assumes that if one taxon is used, all
          // higher taxa will be used as well.
          if ($parent_node->field_taxon[LANGUAGE_NONE][0]['value'] == $TAXON_IDS['Subspecies']) {
            $scientific_name = ' ' . $parent_node->field_scientific_name[LANGUAGE_NONE][0]['value'];
            continue;
          }
          if ($parent_node->field_taxon[LANGUAGE_NONE][0]['value'] == $TAXON_IDS['Species']) {
            $scientific_name = ' ' . $parent_node->field_scientific_name[LANGUAGE_NONE][0]['value'] . $scientific_name;
            continue;
          }
          if ($parent_node->field_taxon[LANGUAGE_NONE][0]['value'] == $TAXON_IDS['Genus']) {
            $scientific_name = $parent_node->field_scientific_name[LANGUAGE_NONE][0]['value'] . $scientific_name;
            break;
          }
        }
      }
    }
  }

  if ($scientific_name) {
    if ($node->title == $scientific_name) {
      return '<h2><i>' . $scientific_name . '</i></h2>';
    }
    else {
      return '<h2>' . check_plain($node->title) . ' &ndash; <i>' . $scientific_name . '</i></h2>';
    }
  }
  else {
    return '<h2>' . check_plain($node->title) . '</h2>';
  }
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
  if (!$nids) {
    return;
  }

  $output = '<div class="bgimage-related-actions">';
  if (user_access('use image clipboard')) {
    $output .= l(
      t('Add all images to clipboard'),
      'bgimage/clip/' . $node->nid . '/all',
      array(
        'attributes' => array(
          'class' => 'button is-small mr-1',
          'role' => 'button',
        ),
        'query' => array(
          'destination' => current_path()
        )
      )
    );
  }

  global $user;
  if ($node->uid == $user->uid || user_access('link all bgimages')) {
    $output .= l(
      t('Unlink images'),
      'bgimage/unlink/' . $node->nid,
      array(
        'attributes' => array(
          'class' => 'button is-small bgimage-related-action-unlink',
          'role' => 'button',
          'title' => t('Unlink all the images below'),
        ),
      )
    );
  }
  $output .= '</div>';

  $output .= '<div class="field-label">Images of this individual:</div>';
  
  // Render image thumbnails.
  $output .= '<div class="bgimage-related-container">';
  $nodes = node_load_multiple($nids);
  foreach ($nodes as $related_node) {
    $node_wrapper = entity_metadata_wrapper('node', $related_node);
    if (isset($node_wrapper) && $node_wrapper->field_bgimage_image->value()) {
      $image_properties = array(
        'style_name' => 'bg_small',
        'path' => $node_wrapper->field_bgimage_image->file->value()->uri,
        'alt' => $node_wrapper->title->value(array('sanitize' => TRUE)),
        'title' => $node_wrapper->title->value(array('sanitize' => TRUE)),
        'attributes' => array('class' => 'bgimage-related-thumb'),
      );
      // Add a border to the thumbnail of the current image.
      if ($related_node->nid == $node->nid) {
        $image_properties['attributes']['class'] .= ' bgimage-related-thumb-current';
      }
      $image = theme('image_style', $image_properties);
      $output .= '<div class="bgimage-related"><a href="' . url('node/' . $related_node->nid) . '" title="' . $node_wrapper->title->value(array('sanitize' => TRUE)) . '">' . $image . '</a></div>';
    }
  }

  $output .= '</div>';
  
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

/**
 * Callback to render the taxonomy path of a bgimage node.
 */
function _bgimage_field_taxonomy_path($field) {
  if ($field['view_mode'] != 'recent') {
    return;
  }

  $node = $field['entity'];

  // Extract parent links of this image.
  $parent_node_nid = bg_get_parent_nid($node);
  if (empty($parent_node_nid)) {
    return;
  }
  $parent_node = node_load($parent_node_nid);
  $breadcrumbs = bg_create_taxonomic_breadcrumb($parent_node);
  array_shift($breadcrumbs);
  if (empty($breadcrumbs)) {
    return;
  }

  // Render links.
  return implode(' &raquo; ', $breadcrumbs);
}

/**
 * Callback to render a combination of the location fields.
 */
function _bgimage_field_location_combined($field) {
  if (!in_array($field['view_mode'], array('full', 'recent', 'teaser'))) {
    return;
  }

  $node = $field['entity'];
  $node_wrapper = entity_metadata_wrapper('node', $node);

  $location = $node_wrapper->field_bgimage_location->value();
  $county = $node_wrapper->field_bgimage_county->value();
  $location_code = $node_wrapper->field_bgimage_location_code->value();

  // Don't display 'Unknown' as the state/province.
  $state_province = '';
  if ($location_code != 'ZZ') {
    $location_code_info = field_info_field('field_bgimage_location_code');
    $state_province = $location_code_info['settings']['allowed_values'][$location_code];
  }

  $combined_location = implode(", ", array_filter(array($location, $county, $state_province)));
  if (!$combined_location) {
    // Recent doesn't include a 'Location:' label, so add more context in that case.
    $combined_location = $field['view_mode'] == 'recent' ? t('Location unknown') : t('Unknown');
  }

  return $combined_location;
}
