<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  // Extract parent nids.
  $nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);
  // Append current node at the end.
  $nids[] = $node->nid;

  // Build classification tree.
  $nids_filter = new SolrFilterSubQuery('OR');
  foreach ($nids as $nid) {
    $nids_filter->addFilter('entity_id', $nid);
  }
  $classified_results = bgpage_fetch_classification($node->nid, $nids_filter);
  return bgpage_tree_build($classified_results);
}

/**
 * Callback to render citations in a bgpage node.
 *
 * @see bg_node_view_alter().
 */
function _bgpage_citations($field) {
  return 'This is a placeholder to list citations.';
}
