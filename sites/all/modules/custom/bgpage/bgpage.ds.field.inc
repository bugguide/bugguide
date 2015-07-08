<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  $node = $field['entity'];
  $parent_nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);

  // Fetch titles.
  $titles = db_query('SELECT title FROM {node} WHERE nid IN (:nids)', array(':nids' => $parent_nids))->fetchCol();

  // Fetch taxons.
  $parent_nodes = bg_field_load_multiple('bgpage', 'field_taxon', $parent_nids);
  $taxons = array();
  foreach ($parent_nodes as $parent_node) {
    $taxons[] = $parent_node->field_taxon[LANGUAGE_NONE][0]['value'];
  }

  // Fetch scientific names.
  $parent_nodes = bg_field_load_multiple('bgpage', 'field_scientific_name', $parent_nids);
  $scientific_names = array();
  foreach ($parent_nodes as $parent_node) {
    $scientific_names[] = $parent_node->field_scientific_name[LANGUAGE_NONE][0]['value'];
  }

  // Build classification tree.
  $output = '<div class="field-label">Classification:</div>';
  $output .= '<span class="graytext">Kingdom</span> <strong>Animalia</strong> - Animals<br/>';
  return $output . bgpage_tree_build($node, array(), $parent_nids, $taxons, $titles, $scientific_names, array());
}
