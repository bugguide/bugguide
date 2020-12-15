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
 *
 * Find nodes of type bgpage in Lepidoptera without a Hodges number
 *
 * @return string
 *   HTML list of nodes of type bgpage in Lepidoptera without a Hodges number.
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
n.title NOT REGEXP '88'"); ///< Skip the butterfly called the '88 Butterfly'.

  foreach ($result as $bgpage) {
    $node = node_load($bgpage->nid);
    $output .= '<p>' . $bgpage->nid . ' ' . l($node->title, "node/$bgpage->nid/edit");
  }
  return $output;
}

/**
 * Menu callback to find nodes that contains content error.
 *
 * Find images where county field erroneously contains USA or Canada.
 * This is a form because originally we were working on a way to bulk
 * correct these errors. However, currently it just lists links to affected images.
 *
 * @return mixed $form
 */
function bg_fixup_locations_form() {

  $form['locations'] = array(
    '#prefix' => '<div id="locations">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => array(
      t('Link'),
      t('Location'),
      t('County'),
      t('Location Code'),
    ),
    '#rows' => array(),
  );

  // In order to do a case-sensitive search on a column which is using
  // the utf8_general_ci (ci = case insensitive) collation, coerce
  // collation to utf8_bin first. Then we can select Foo, USA while
  // avoiding false matches like Dusachen.
  $result = db_query("SELECT nid, location, location_code, county FROM {bgimage} WHERE (county COLLATE utf8_bin LIKE '%USA%') OR (UPPER(county) LIKE '%CANADA%') ORDER BY nid LIMIT 250 ");

  foreach ($result as $key => $record) {
    $form['locations']['#rows'][] = array(
      'link' => l($record->nid, 'node/' . $record->nid),
      'location' => $record->location,
      'county' => $record->county,
      'location_code' => $record->location_code,
    );
  }
  return $form;
}
