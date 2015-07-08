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

  $nodes = bg_prepare_nodes($parent_nids, 'bgpage');
  // Fetch titles.
  $result = db_query('SELECT nid, title FROM {node} WHERE nid IN (:nids)', array(':nids' => $parent_nids));
  foreach ($result as $row) {
    $nodes[$row->nid]->title = $row->title;
  }
  // Fetch taxon and scientific name.
  $nodes = bg_field_load_multiple('field_parent', $nodes);
  $nodes = bg_field_load_multiple('field_taxon', $nodes);
  $nodes = bg_field_load_multiple('field_scientific_name', $nodes);

  // Append current node at the end.
  $nodes[] = $node;

  // Build classification tree.
  return bgpage_tree_build($nodes);
}
