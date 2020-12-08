<?php

/**
 * @file
 * The BG utilities are suitable for one-off administrative use.
 */

/**
 * Menu callback
 */
function bg_utilities() {
  $output .= '<h1>' . t('System Utilities') . '</h1>';
  $output .= '<p>' . t('These are utilities to help maintain the site.');
  $output .= '<p>' . t('<strong>Show Orphaned Nodes</strong> finds nodes whose parent path is broken or missing.');
  $output .= '<p>' . t('<strong>Show Stageless Leps</strong> finds Lepidoptera where neither adult nor immature was checked.');
  $output .= '<p>' . t('<strong>Show Leps Without Hodges #</strong> finds Lepidoptera where numbers appear in title but Hodges field is blank.');
  return $output;
}

/**
 * Menu callback.
 *
 * Show orphaned nodes; i.e., nodes whose parent has been deleted.
 */
function bg_orphans() {
  $output = '';

  // Create array of immediate parents for each bgpage node.
  $result = db_query("SELECT n.nid, p.field_parent_value FROM {field_data_field_parent} p JOIN {node} n ON p.revision_id = n.vid WHERE n.type = 'bgpage' AND p.deleted = 0");

  foreach ($result as $bgpage) {
    $parents = explode(',', $bgpage->field_parent_value);
    if (count($parents) > 0) {
      $bgpage->last_parent = $parents[count($parents) - 1];
    }
    $bgpages[$bgpage->nid] = $bgpage;
  }

  // Create an array of known parentless nodes.
  $result = db_query("SELECT n.type, n.nid, n.title FROM {node} n LEFT OUTER JOIN {field_data_field_parent} p ON (n.vid = p.revision_id) WHERE field_parent_value IS NULL AND n.type != 'bglink' AND n.type != 'page' AND n.type !='forum' AND n.type !='bgimage'");
  foreach ($result as $node) {
    $parentless_but_ok[$node->nid] = $node->title;
  }

  $result = db_query("SELECT n.nid, n.status, n.title, p.field_parent_value, p.bundle FROM {field_data_field_parent} p JOIN {node} n ON p.revision_id = n.vid WHERE p.deleted = 0 AND n.type != 'forum' AND n.type != 'page' AND n.type != 'bglink'");
  // TODO: remove bglink from above query exclusion when it gets parents.
  $counter = 1;
  foreach ($result as $node) {
    if ($counter % 10000 == 0) {
      watchdog('bg', 'Checked %count nodes', array('%count' => $counter));
    }
    unset($child);
    // Some nodes do not have parents.
    if (!$node->field_parent_value) {
      continue;
    }

    $parents = explode(',', $node->field_parent_value);
    $parents = array_reverse($parents);
    foreach ($parents as $nid) {
      $parent = isset($bgpages[$nid]) ? $bgpages[$nid] : NULL;
      if (!$parent && !isset($parentless_but_ok[$nid])) {
        $output .= "<ul><li>$node->bundle ";
        $output .= l($node->nid . ' ' . t($node->title), "node/$node->nid");
        $output .= " has missing parent ";
        $output .= " $nid" . ' ' . $node->title;
        $output .= "</li></ul>\n";
      }
      else {
        if (isset($child) && ($child->last_parent != $nid)) {
          $output .= "<ul><li>$node->bundle ";
          $output .= l($node->nid . ' ' . t($node->title), "node/$node->nid");
          $output .= " has path problem ";
          $output .= " $child->nid's parent $nid != $child->last_parent";
          $output .= "</li></ul>\n";
        }
        $child = $parent;
      }
    }
    $counter++;
  }
  $output .= '<p>';
  $output .= 'Checked ' . $counter . ' nodes.';
  $output .= '<p>';
  $output .= 'The following nodes are orphaned purposely: ';
  foreach ($parentless_but_ok as $nid => $title) {
    $output .= '<p>' . l($title, "node/$nid");
  }
  return $output;
}

/**
 * Menu callback. Form to fix Lepidoptera with neither adult nor
 * immature indicated.
 */
function bg_stageless_leps() {
  $form = array();
  $nids = array();
  $result = db_query("SELECT n.nid
FROM {node} n
JOIN {field_data_field_parent} p ON (n.vid = p.revision_id)
LEFT OUTER JOIN {field_data_field_bgimage_life_stage} s ON (n.vid = s.revision_id)
WHERE
n.status = 1 AND
n.type = 'bgimage' AND
(p.field_parent_value LIKE '%,57' OR p.field_parent_value LIKE '%,57,%') AND
field_bgimage_life_stage_value IS NULL
LIMIT 5");

  foreach ($result as $bgimage) {
    $node = node_load($bgimage->nid);
    $form[$bgimage->nid] = array(
      '#title' => $node->title,
      '#type' => 'checkboxes',
      '#options' => array(
        'adult' => t('adult'),
        'immature' => t('immature'),
      ),
      '#return_value' => 1,
      '#description' => bgimage_thumb_link($node) . '<hr>',
    );
    $nids[] = $bgimage->nid;
  }
  $form['nids'] = array(
    '#type' => 'value',
    '#value' => $nids,
  );
  if ($result) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );
  }

  return $form;
}

function bg_stageless_leps_submit($form, &$form_state) {
  $adults = array();
  $immatures = array();
  foreach ($form_state['values']['nids'] as $nid) {
    if ($form_state['values'][$nid]['adult']) {
      $adults[] = $nid;
    }
    if ($form_state['values'][$nid]['immature']) {
      $immatures[] = $nid;
    }
  }
  foreach ($adults as $nid) {
    $node = node_load($nid);
    $node->field_bgimage_life_stage[LANGUAGE_NONE][0]['value'] = 'adult';
    watchdog('bg', 'Setting life stage to adult for node %nid', array('%nid' => $nid));
    node_save($node);
  }
  foreach ($immatures as $nid) {
    $node = node_load($nid);
    $node->field_bgimage_life_stage[LANGUAGE_NONE][0]['value'] = 'immature';
    watchdog('bg', 'Setting life stage to immature for node %nid', array('%nid' => $nid));
    node_save($node);
  }

  drupal_set_message('Data has been updated.');
}

/**
 * Menu callback.
 * Find nodes of type bgpage in Lepidoptera without a Hodges number
 *
 * @return HTML
 */
function bg_blank_hodges() {
  $output = '<p>' . t('The following are Lepidoptera with Hodges numbers in the title but the submitter forgot to fill out Hodges number field.');

  $result = db_query("SELECT n.type, n.nid, h.field_hodges_number_value, p.field_parent_value, n.title
FROM {node} n
JOIN {field_data_field_parent} p ON (n.vid = p.revision_id)
JOIN {field_data_field_taxon} t ON (n.vid = t.revision_id)
LEFT OUTER JOIN {field_data_field_hodges_number} h ON (n.vid = h.revision_id)
WHERE
n.status = 1 AND
h.field_hodges_number_value IS NULL AND
n.type = 'bgpage' AND
(p.field_parent_value LIKE '%,57' OR p.field_parent_value LIKE '%,57,%') AND
t.field_taxon_value = 3400 AND
n.title REGEXP '[0-9][0-9]' AND
n.title NOT REGEXP '88'"); // Skip the butterfly called the '88 Butterfly'.

  foreach ($result as $bgpage) {
    $node = node_load($bgpage->nid);
    $output .= '<p>' . $bgpage->nid . ' ' . l($node->title, "node/$bgpage->nid/edit");
  }
  return $output;
}

/**
 * Menu callback.
 * Find images where county field erroneously contains USA or Canada.
 * Suggest corrected fields.
 *
 * @return $form
 */
function bg_fixup_locations_form() {
  global $LOCATION_CODES;

  $form['locations'] = array(
    '#prefix' => '<div id="locations">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => array(
      t('Fix'),
      t('Original Location'),
      t('Location'),
      t('Original County'),
      t('County'),
      t('Original Location Code'),
      t('Location Code'),
    ),
    '#rows' => array(),
  );

  // In order to do a case-sensitive search on a column which is using
  // the utf8_general_ci (ci = case insensitive) collation, coerce
  // collation to utf8_bin first. Then we can select Foo, USA while
  // avoiding false matches like Dusachen.
  $result = db_query("SELECT base, location, location_code, county FROM {bgimage} WHERE ((UPPER(county) COLLATE utf8_bin LIKE '%USA%') OR (UPPER(county) LIKE '%CANADA%')) ORDER BY RAND() LIMIT 10 ");

  foreach ($result as $key => $location) {
    // Original entry in location field.
    $original = $location->location;
    $original_location_code = $location->location_code;
    $location_code = $location->location_code;
    $original_county = $location->county;
    $county = $location->county;
    $location = $original;

    // Remove USA or Canada from end of location.
    if (bg_str_ends_with(strtoupper($location), ', USA')) {
      $location = substr($location, 0, strlen($location) - 5);
    }
    if (bg_str_ends_with(strtoupper($location), ' USA')) {
      $location = substr($location, 0, strlen($location) - 4);
    }

    if (bg_str_ends_with(strtoupper($location), ', CANADA')) {
      $location = substr($location, 0, strlen($location) - 8);
    }
    if (bg_str_ends_with(strtoupper($location), ' CANADA')) {
      $location = substr($location, 0, strlen($location) - 7);
    }

    // @see bg_globals.inc
    // e.g., $LOCATION_CODES['AL'] = 'Alabama';
    foreach ($LOCATION_CODES as $code => $name) {
      if (bg_str_ends_with(strtoupper($location), ', '. strtoupper($name))) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - strlen($name) - 2);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), ' ' . strtoupper($name))) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - strlen($name) - 1);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), ", $code.")) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - 5);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), " $code.")) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - 4);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), ", $code")) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - 4);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), ",$code")) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - 3);
        break;
      }

      if (bg_str_ends_with(strtoupper($location), " $code")) {
        $location_code = $code;
        $location = substr($location, 0, strlen($location) - 3);
        break;
      }

      if ((strtoupper($location) == strtoupper($name)) ||
          (strtoupper($location) == $code)) {
        $location_code = $code;
        $location = '';
        break;
      }
    }

    if (bg_str_ends_with(strtoupper($location), ' COUNTY')) {
      $lastComma = strrpos($location, ',');
      if ($lastComma) {
        $lastComma++;
      }

      $county = ltrim(substr($location, $lastComma, strlen($location) - 7 - $lastComma));

      if ($lastComma) {
        $location = trim(substr($location, 0, $lastComma - 1));
      }
      else {
        $location = '';
      }
    }

    if (bg_str_ends_with(strtoupper($location), ' CO.')) {
      $lastComma = strrpos($location, ',');
      if ($lastComma) {
        $lastComma++;
      }

      $county = ltrim(substr($location, $lastComma, strlen($location) - 4 - $lastComma));

      if ($lastComma) {
        $location = trim(substr($location, 0, $lastComma - 1));
      }
      else {
        $location = '';
      }
    }

    // Build the fields for this row in the table. We'll be adding
    // these to the form several times, so it's easier if they are
    // individual variables rather than in an array.

    $fix__form_field = array(
      '#type' => 'checkbox',
      '#default_value' => $location_code && ($county || $location) ? 1 : 0,
      '#options' => array(
        '0' => 0,
        '1' => 1,
      ),
    );

    $original_location__form_field = array(
      '#type' => 'value',
      '#value' => $original,
    );

    $location__form_field = array(
      '#type' => 'textfield',
      '#default_value' => $location,
      '#description' => t('Proposed Location'),
    );

    $original_county__form_field = array(
      '#type' => 'value',
      '#value' => $original_county,
    );

    $county__form_field = array(
      '#type' => 'textfield',
      '#default_value' => $county,
      '#description' => t('Proposed County'),
    );

    $original_location_code__form_field = array(
      '#type' => 'value',
      '#value' => $original_location_code,
      '#size' => 4,
    );

    $location_code__form_field = array(
      '#type' => 'textfield',
      '#default_value' => $location_code,
      '#size' => 4,
    );

    // Include the fields so they'll be rendered and named
    // correctly, but they'll be ignored here when rendering as
    // we're using #theme => table.
    //
    // Note that we're using references to the variables, not just
    // copying the values into the array.

    $form['locations'][] = array(
      'fix' => &$fix__form_field,
      'original_location' => &$original_location__form_field,
      'location' => &$location__form_field,
      'original_county' => &$original_county__form_field,
      'county' => &$county__form_field,
      'original_location_code' => &$original_location_code__form_field,
      'location_code' => &$location_code__form_field,
    );

    // Now add references to the fields to the rows that
    // `theme_table()` will use.
    // As we've used references, the table will use the very same
    // field arrays as the FAPI used above.

    $form['locations']['#rows'][] = array(
      array('data' => &$fix__form_field),
      array('data' => &$original),
      array('data' => &$location__form_field),
      array('data' => &$original_county),
      array('data' => &$county__form_field),
      array('data' => &$original_location_code),
      array('data' => &$location_code__form_field),
    );

    // Because we've used references we need to `unset()` our
    // variables. If we don't then every iteration of the loop will
    // just overwrite the variables we created the first time
    // through leaving us with a form with 3 copies of the same fields.

    unset($fix__form_field);
    unset($original_location__form_field);
    unset($location__form_field);
    unset($original_county__form_field);
    unset($county__form_field);
    unset($original_location_code__form_field);
    unset($location_code__form_field);

    unset($original);
    unset($original_county);
    unset($original_location_code);
  }

  $form['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}

/**
 * Callback submission for bg_fixup_locations_form().
 *
 * Get locations data and save them in bgimage table and content type.
 *
 * @param $form
 * @param $form_state
 */
function bg_fixup_locations_form_submit($form, &$form_state) {
  if (!isset($form_state['values']['locations'])) {
    return;
  }
  foreach ($form_state['values']['locations'] as $location) {
    db_query("UPDATE {bgimage}
      SET
      location = ':location',
      location_code = ':location_code',
      county = ':county'
      WHERE
      ((county COLLATE utf8_bin LIKE '%USA%') OR (UPPER(county) LIKE '%CANADA%'))
      AND location = ':original_location'
      AND location_code = ':original_location_code'
      AND county = ':original_county'
      ",
      array(
        ':location' => $location['location'],
        ':location_code' => $location['location_code'],
        ':county_code' => $location['county'],
        ':original_location' => $location['original_location'],
        ':original_location_code' => $location['original_location_code'],
        ':original_county' => $location['original_county'],
      )
    );

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'bgimage')
      ->fieldCondition('field_bgimage_location', 'value', $location['original_location'], '=')
      ->fieldCondition('field_bgimage_location_code', 'value', $location['original_location_code'], '=')
      ->fieldCondition('field_bgimage_county', 'value', $location['original_county'], '=')
      // Run the query as user 1.
      ->addMetaData('account', user_load(1));

    $result = $query->execute();
    if (isset($result['node'])) {
      $bgimage_items_nids = array_keys($result['node']);
      $bgimage_nodes = entity_load('node', $bgimage_items_nids);
      foreach ($bgimage_nodes as $bgimage_node) {
        // If county contains USA or CANADA then save the node with new
        // location data.
        if (isset($bgimage_node->field_bgimage_county[LANGUAGE_NONE][0]['value']) &&
          (strpos($bgimage_node->field_bgimage_county[LANGUAGE_NONE][0]['value'], 'USA') !== FALSE ||
            stripos($bgimage_node->field_bgimage_county[LANGUAGE_NONE][0]['value'], 'CANADA'))
          ) {
          $bgimage_node->field_bgimage_location[LANGUAGE_NONE][0]['value'] = $location['location'];
          $bgimage_node->field_bgimage_location_code[LANGUAGE_NONE][0]['value'] = $location['location_code'];
          $bgimage_node->field_bgimage_county[LANGUAGE_NONE][0]['value'] = $location['county'];
          node_save($bgimage_node);
        }
      }
    }
  }
}
