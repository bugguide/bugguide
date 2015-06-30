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
  $output = '<h1>' . t('Orphan Report') . '</h1>';
  $result = db_query("SELECT n.nid, t.parent FROM {node} n, {bgpage} t WHERE t.nid = n.nid AND n.type = 'bgpage' AND n.status = '1'");
  while ($bgpage = db_fetch_object($result)) {
    $parents = explode(',', $bgpage->parent);
    if (count($parents) > 0) {
      $bgpage->last_parent = $parents[count($parents) - 1];
    }
    $bgpages[$bgpage->nid] = $bgpage;
  }

  $child_tables[] = 'bgpage';
  $child_tables[] = 'bgimage';
  $child_tables[] = 'content_type_bglink';
  $child_tables[] = 'bgref';
  foreach ($child_tables as $table) {
    if ($table == 'content_type_bglink') {
      // CCK field.
      $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node} n, {$table} t WHERE t.nid = n.nid AND n.type = 'bglink' AND n.status = '1'"));      
    }
    else {
      $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node} n, {$table} t WHERE t.nid = n.nid AND n.type = '$table' AND n.status = '1'"));
    }
    $output .= '<p>' . t('Examined !count from !table', array('!count' => $count, '!table' => $table));
    $result = db_query("SELECT n.nid, n.title, t.parent FROM {node} n, {$table} t WHERE t.nid = n.nid AND n.type = '$table' AND n.status = '1'");

    while ($node = db_fetch_object($result)) {
      unset($child);
      if (!$node->parent) {
        continue;
      }
      $parents = explode(',', $node->parent);
      $parents = array_reverse($parents);
      foreach ($parents as $nid) {
        $parent = $bgpages[$nid];
        if (!$parent) {
          $output .= "<ul><li>$table ";
          $output .= l($node->nid, "node/$node->nid");
          $output .= " has missing parent ";
          $output .= " $nid" . ' ' . $node->title;
          $output .= "</li></ul>\n";
        }
        else {
          if ($child && ($child->last_parent != $nid)) {
            $output .= "<ul><li>$table ";
            $output .= l($node->nid, "node/view/$node->nid");
            $output .= " has path problem ";
            $output .= " $child->nid's parent $nid != $child->last_parent";
            $output .= "</li></ul>\n";
          }
          $child = $parent;
        }
      }
    }
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
  $result = db_query("SELECT n.nid FROM {node} n, {bgimage} t WHERE t.nid = n.nid AND n.type = 'bgimage' AND n.status = '1' AND t.parent_idx like '%,57,%' AND t.adult != 1 AND t.immature != 1 LIMIT 25");
  while ($bgimage = db_fetch_object($result)) {
    $bgimage = node_load(array(
      'nid' => $bgimage->nid,
      'type' => 'bgimage')
      );
    $form[$bgimage->nid] = array(
      '#title' => $bgimage->title,
      '#type' => 'checkboxes',
      '#options' => array(
        'adult' => t('adult'),
        'immature' => t('immature'),
      ),
      '#return_value' => 1,
      '#description' => bgimage_get_thumb_link($bgimage) . '<hr>',
      
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
  if ($adults) {
    db_query('UPDATE {bgimage} SET adult = 1 WHERE nid IN (%s)', implode(',', $adults));
  }
  if ($immatures) {
    db_query('UPDATE {bgimage} SET immature = 1 WHERE nid IN (%s)', implode(',', $immatures));    
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
  $output = '<h1>' . t('Lepidoptera Without Hodges Number') . '</h1>';
  $result = db_query("SELECT n.nid FROM {node} n, {bgpage} t WHERE t.nid = n.nid AND n.type = 'bgpage' AND n.status = '1' AND (t.parent like '%,57' OR t.parent like '%,57,%') and (n.title regexp '[0-9][0-9]' OR t.names REGEXP '[0-9][0-9]') AND taxon = 3400 AND hodges_number IS NULL LIMIT 25");

  while ($bgpage = db_fetch_object($result)) {
    $bgpage = node_load(array('nid' => $bgpage->nid, 'type' => 'bgpage'));
    $output .= '<p>' . l($bgpage->nid, "node/$bgpage->nid/edit");
    $output .= " $bgpage->title_node";
    $output .= "<br />";
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
  
  // In order to do a case-sensitive search on a column which is using
  // the utf8_general_ci (ci = case insensitive) collation, coerce
  // collation to utf8_bin first. Then we can select Foo, USA while
  // avoiding false matches like Dusachen.
  $result = db_query("SELECT base, location, location_code, county, COUNT(*) AS count FROM {bgimage} WHERE ((county COLLATE utf8_bin LIKE '%USA%') OR (UPPER(county) LIKE '%CANADA%')) GROUP BY location ORDER BY RAND() LIMIT 10");
  $ids = array();
  while ($location = db_fetch_object($result)) {

    // Unique identifier.
    $base = $location->base;
    $ids[] = $base;
    // Number of records like this.
    $count = $location->count;
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
    
    $form['#tree'] = TRUE;
    $form['#theme'] = 'bg_fixup_locations_table';
    $form[$base] = array();
    $form[$base]['fix'] = array(
      '#type' => 'checkbox',
      '#default_value' => $location_code && ($county || $location) ? 1 : 0,
      '#options' => array(
        '0' => 0,
        '1' => 1,
      ),
    );
    $form[$base]['original_location'] = array(
      '#type' => 'value',
      '#value' => $original,
    );
    $form[$base]['location'] = array(
      '#type' => 'textfield',
      '#default_value' => $location,
    );
    $form[$base]['original_county'] = array(
      '#type' => 'value',
      '#value' => $original_county,
    );
    $form[$base]['county'] = array(
      '#type' => 'textfield',
      '#default_value' => $county,
    );
    $form[$base]['original_location_code'] = array(
      '#type' => 'value',
      '#value' => $original_location_code,
      '#size' => 4,
    );
    $form[$base]['location_code'] = array(
      '#type' => 'textfield',
      '#default_value' => $location_code,
      '#size' => 4,
    );
    $form[$base]['count'] = array(
      '#type' => 'value',
      '#value' => $count,
    );
  }
  
  $form['ids'] = array(
    '#type' => 'value',
    '#value' => $ids,
  );
  $form['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}

function bg_fixup_locations_form_submit($form, &$form_state) {
  foreach ($form_state['values']['ids'] as $base) {
    if ($form_state['values'][$base]['fix']) { 
      db_query("UPDATE {bgimage} 
        SET 
        location = '%s',
        location_code = '%s',
        county = '%s'
        WHERE
        ((county COLLATE utf8_bin LIKE '%USA%') OR (UPPER(county) LIKE '%CANADA%'))
        AND location = '%s'
        AND location_code = '%s'
        AND county = '%s'
        ", $form_state['values'][$base]['location'], $form_state['values'][$base]['location_code'], $form_state['values'][$base]['county'], $form_state['values'][$base]['original_location'], $form_state['values'][$base]['original_location_code'], $form_state['values'][$base]['original_county']   
      );
    }
  }
}

/**
 * Theme function for the location fixup form.
 */
function theme_bg_fixup_locations_table($form) {
  $headers = array(
    t('Fix'),
    t('Count'),
    t('Original Location'),
    t('Location'),
    t('Original County'),
    t('County'),
    t('Original Location Code'),
    t('Location Code'),
  );
  $rows = array();

  foreach ($form['ids']['#value'] as $base) {
    $rows[] = array(
      drupal_render($form[$base]['fix']),
      $form[$base]['count']['#value'],
      $form[$base]['original_location']['#value'],
      drupal_render($form[$base]['location']),
      $form[$base]['original_county']['#value'],
      drupal_render($form[$base]['county']),
      $form[$base]['original_location_code']['#value'],
      drupal_render($form[$base]['location_code']),
    );
  }
  
  $output = theme_table($headers, $rows);
  $output .= drupal_render($form);
  return $output;
}
