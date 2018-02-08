<?php
/**
 * Page callbacks for bgpage module.
 */

/**
 * Generate the taxonomic tree from the root (Arthropoda) to the current taxon.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 * @param $mode
 *   If true, show all the children from this point in the taxonomic tree on
 *   down.
 */
function bgpage_tree($nid, $mode = 'collapsed') {
  $node = node_load($nid);

  $nids_filter = _bgpage_tree_filter($node);

  // Fetch the tree from Apache Solr.
  $classified_results = bgpage_fetch_classification($node->nid, $nids_filter);

  // Render the results.
  if (empty($classified_results)) {
    $output = '<p>No results found.</p>';
  }
  else {
    $output = bgpage_tree_build($classified_results);
  }

  return $output;
}

/**
 * Browses images in immediate descendants of a bgpage node.
 */
function bgpage_browse($nid) {
  $node = node_load($nid);
  return node_view($node, 'browse');
}

/**
 * Shows images for a bgpage node.
 *
 * Traverses the tree in a Breadth-first way showing images for each leaf.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgpage_images($nid) {
  $node = node_load($nid);
  return node_view($node, 'images');
}
