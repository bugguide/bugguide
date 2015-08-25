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
  // Prepare the query filter depending on whether we want the collapsed or
  // full taxonomy tree.
  $parent_filter = new SolrFilterSubQuery('AND');
  if ($mode == 'collapsed') {
    $parent_filter->addFilter('ss_bgpage_immediate_parent', $nid);
  }
  else {
    $parent_filter->addFilter('sm_bgpage_parents', $nid);
  }

  // Fetch the tree from Apache Solr.
  $classified_results = bgpage_fetch_classification($nid, $parent_filter);

  // Render the results.
  if (empty($classified_results)) {
    $output = '<p>No results found.</p>';
  }
  else {
    $output = bgpage_tree_build($classified_results);
    if ($mode == 'collapsed') {
      $output .= '<p>' . l('view all', 'node/' . $nid . '/tree/full') . '</p>';
    }
  }

  return $output;
}
