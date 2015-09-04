<?php
/**
 * Page callbacks for bgpage module.
 */

/**
 * Generate the taxonomic tree from the root (Arthropoda) to the current taxon.
 *
 * @param $node
 *   The node being viewed.
 * @param $mode
 *   If true, show all the children from this point in the taxonomic tree on
 *   down.
 */
function bgpage_tree($node, $mode = 'collapsed') {
  // Prepare the query filter depending on whether we want the collapsed or
  // full taxonomy tree.
  $parent_filter = new SolrFilterSubQuery('AND');
  if ($mode == 'collapsed') {
    $parent_filter->addFilter('ss_bgpage_immediate_parent', $node->nid);
  }
  else {
    $parent_filter->addFilter('sm_bgpage_parents', $node->nid);
  }

  // Fetch the tree from Apache Solr.
  $classified_results = bgpage_fetch_classification($node->nid, $parent_filter);

  // Render the results.
  if (empty($classified_results)) {
    $output = '<p>No results found.</p>';
  }
  else {
    $output = bgpage_tree_build($classified_results);
    if ($mode == 'collapsed') {
      $output .= '<p>' . l('view all', 'node/' . $node->nid . '/tree/full') . '</p>';
    }
  }

  return $output;
}

/**
 * Browses images in immediate descendants of a bgpage node.
 */
function bgpage_browse($node) {
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $PER_PAGE = 5;
  $node->comment = 0;
  $path = $node->field_parent->value();
  $output = '';


  if (!$stage_filter_sql) {
    $result = pager_query("SELECT n.nid FROM {node} n, {bgpage} p WHERE p.nid = n.nid AND parent = '$path' AND status = '1' ORDER BY p.sequence, p.nid", $PER_PAGE);
  }
  else {
    //$result = pager_query("SELECT p.nid, count(*) FROM {node} n, {bgpage} p, {bgimage} i WHERE p.nid = n.nid AND p.parent = '$path' AND concat(i.parent,',') LIKE concat(p.parent,',',p.nid,',%') AND status = '1' AND representative = 1 AND $stage_filter GROUP BY p.nid ORDER BY p.sequence, p.nid", $PER_PAGE, 0, "SELECT count(distinct p.nid) FROM {node} n, {bgpage} p, {bgimage} i WHERE p.nid = n.nid AND p.parent = '$path' AND concat(i.parent,',') LIKE concat(p.parent,',',p.nid,',%') AND representative = 1 AND status = '1' AND $stage_filter");
    // now with parent_idx
    $result = pager_query("SELECT p.nid, COUNT(*) FROM {node} n, {bgpage} p, {bgimage} i WHERE p.nid = n.nid AND p.parent = '$path' AND i.parent_idx LIKE concat(p.parent,',',p.nid,',%') AND status = '1' AND representative = 1 $stage_filter_sql GROUP BY p.nid ORDER BY p.sequence, p.nid", $PER_PAGE, 0, "SELECT COUNT(distinct p.nid) FROM {node} n, {bgpage} p, {bgimage} i WHERE p.nid = n.nid AND p.parent = '$path' AND i.parent_idx LIKE concat(p.parent,',',p.nid,',%') AND representative = 1 AND status = '1' $stage_filter_sql");
  }

  while ($child = db_fetch_object($result)) {
    $count++;
    $child = node_load(array('nid' => $child->nid, 'type' => 'bgpage'));
    if (!$child) {
      watchdog('bgpage', "bgpage_browse() cannot load node nid '%nid'", array('%nid' => $nid), WATCHDOG_ERROR);
    }
    if ($child->status == 1) {
      $children[] = $child;
    }
  }

  if ($children) {
    $pager = theme('pager');
    $output .= $pager;
    foreach ($children as $child) {
      $child_links[] = l($child->title, "node/$child->nid/bgpage");
    }
    if (count($child_links) > 1) {
      $output .= "<div class=\"node-links\">" . implode(' | ', $child_links) . "</div>";
    }
    $output .= bgimage_stage_filter_selector($node);
    $output .= '<br />';

    foreach ($children as $child) {
      $child->comment = 0;
      $child->teaser = bgimage_representative_images($child, 0);

      // TODO: check_markup() is stripping the images out.
      // This ugly hack sets the node format to Full HTML.
      // We should Do It Right instead of doing this.
      $child->format = 2;
      $output .= node_view($child, 1);
    }
    if ($pager) {
      $output .= $pager;
    }
  } else {
    $output .= bgimage_representative_images($node, $main);
    $output .= "<br /><br />";
    $output .= bgimage_stage_filter_selector($node);
    $output .= "<br /><br /><p>There are no guide pages below this one.</p>";
  }
  return $output;
}
