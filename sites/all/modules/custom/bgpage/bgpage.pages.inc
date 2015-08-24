<?php
/**
 * Page callbacks for bgpage module.
 */

/**
 * Generate the taxonomic tree from the root (Arthropoda) to the current taxon.
 *
 * @param $nid
 *   The node ID of the node being viewed.
 * @param $mode
 *   If true, show all the children from this point in the taxonomic tree on
 *   down.
 */
function bgpage_tree($nid, $mode = 'collapsed') {
  global $TAXON_NAMES, $TAXON_IDS;
  $nids = array();
  $node = node_load($nid);
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $output = '';

  // Build the array of nids to list.
  $nids = explode(',', $node_wrapper->field_parent->value());

  // Then, then node itself;
  $nids[] = $node->nid;

  // Next, the immediate or all the children.
  if ($mode == 'collapsed') {
    $conditions = ' fdfp.field_parent_value like :end ';
    $parameters = array(':end' => '%,' . $node->nid);
  }
  else {
    $conditions = ' (fdfp.field_parent_value like :end
                     or fdfp.field_parent_value like :middle
                     or fdfp.field_parent_value like :start) ';
    $parameters = array(
      ':end' => '%,' . $node->nid,
      ':middle' => '%,' . $node->nid . ',%',
      ':start' => $node->nid . ',%',
    );
  }

  // Extract children nids.
  $children_nids = db_query('SELECT entity_id
                             FROM {field_data_field_parent} fdfp
                             inner join {node} n on n.nid = fdfp.entity_id
                             where n.status = 1
                             and ' . $conditions, $parameters)->fetchCol();
  // Add children to the list of nids.
  $nids = array_merge($nids, $children_nids);

  $classified_results = bgpage_fetch_classification($nids);
  $output = bgpage_tree_build($classified_results);

  if ($mode == 'collapsed') {
    $output .= '<p>' . l('view all', 'node/' . $nid . '/tree/full') . '</p>';
  }

  return $output;
}
