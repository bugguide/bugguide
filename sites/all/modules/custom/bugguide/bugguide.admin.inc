<?php

/**
 * @file
 * The BugGuide utilities are suitable for one-off administrative use.
 */

/**
 * Menu callback
 */
function bugguide_utilities() {
  $output .= '<h1>' . t('BugGuide Utilities') . '</h1>';
  $output .= '<p>' . t('These are utilities to help maintain the site.');
  $output .= '<p>' . t('<strong>Show Orphaned Nodes</strong> finds nodes whose parent path is broken or missing.');
  $output .= '<p>' . t('<strong>Show Stageless Leps</strong> finds Lepidoptera where neither adult nor immature was checked.');
  $output .= '<p>' . t('<strong>Show Leps Without Hodges #</strong> finds Lepidoptera where numbers appear in title but Hodges field is blank.');
  return $output;
}


/**
 * Menu callback. Form to fix Lepidoptera with neither adult nor
 * immature indicated.
 */
function bugguide_stageless_leps() {
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

function bugguide_stageless_leps_submit($form, &$form_state) {
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
function bugguide_blank_hodges() {  
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
