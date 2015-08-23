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
                             inner join {bgpage_archive} bgpage on bgpage.nid = n.nid
                             where n.status = 1
                             and ' . $conditions . '
                             order by bgpage.sequence, bgpage.nid', $parameters)->fetchCol();

  // Add children to the list of nids.
  $nids = array_merge($nids, $children_nids);

  // Build an array of pseudo nodes to render the tree.
  $nodes = bg_prepare_nodes($nids, 'bgpage');

  // Fetch titles.
  $result = db_query('SELECT nid, title FROM {node} WHERE nid IN (:nids)', array(':nids' => $nids));
  foreach ($result as $row) {
    $nodes[$row->nid]->title = $row->title;
  }

  // Fetch taxon and scientific name.
  $nodes = bg_field_load_multiple('field_parent', $nodes);
  $nodes = bg_field_load_multiple('field_taxon', $nodes);
  $nodes = bg_field_load_multiple('field_scientific_name', $nodes);
  $nodes = bg_field_load_multiple('field_hodges_number', $nodes);

  // Sort array by parent field and title.
  uasort($nodes, function($node_a, $node_b) {
    $node_a_parent = bg_get_parent_nid($node_a);
    $node_b_parent = bg_get_parent_nid($node_b);
    if ($node_a_parent == NULL || $node_b_parent == NULL) {
      return strcmp($node_a_parent, $node_b_parent);
    }
    if ($node_a_parent == $node_b_parent) {
      return strcmp($node_a->title, $node_b->title);
    }
    $node_a_parents = explode(',', $node_a->field_parent[LANGUAGE_NONE][0]['value']);
    $node_b_parents = explode(',', $node_b->field_parent[LANGUAGE_NONE][0]['value']);
    foreach ($node_a_parents as $key => $nid) {
      if (!isset($node_b_parents[$key])) {
        return 1;
      }
      $parent_diff = $nid - $node_b_parents[$key];
      if ($parent_diff != 0) {
        return $parent_diff;
      }
    }
    return -1;
  });

  $output = bgpage_tree_build($nodes);

  if ($mode == 'collapsed') {
    $output .= '<p>' . l('view all', 'node/' . $node->nid . '/tree/full') . '</p>';
  }

  return $output;
}

/**
 * Builds a hierarchy tree for a set of related nodes.
 *
 * @param array $nodes
 *   An array of pseudo-nodes ordered hierarchycally. The term pseudo is
 *   used because they are not fully loaded nodes due to performance reasons.
 * @returns string
 *   The rendered HTML that represents the tree.
 */
function bgpage_tree_build($nodes) {
  global $TAXON_NAMES, $TAXON_IDS;
  $output = '<span class="graytext">Kingdom</span> <strong>Animalia</strong> - Animals<br/>';

  foreach ($nodes as $node) {
    // Calculate indentation for this item based on the number of parents.
    $node_wrapper = entity_metadata_wrapper('node', $node);
    $parents = $node_wrapper->field_parent->value();
    if (empty($parents)) {
      $indents = 0;
    }
    else {
      $indents = count(explode(',', $parents));
    }
    $indents = str_repeat('&nbsp;', ($indents + 2) * 2);

    // Render the element.
    $output .= $indents . bgpage_tree_child($node);
  }

  return $output;
}

/**
 * Renders a tree element.
 *
 * @param object node
 *   A pseudo node that contains title, field_parent, field_taxon and field_scientific_name.
 * @return string
 *   The rendered tree item.
 */
function bgpage_tree_child($node) {
  global $TAXON_NAMES, $TAXON_IDS;
  if (!empty($node->field_taxon) && isset($TAXON_NAMES[$node->field_taxon[LANGUAGE_NONE][0]['value']])) {
    $taxon_name = $TAXON_NAMES[$node->field_taxon[LANGUAGE_NONE][0]['value']];
    $taxon_id = $node->field_taxon[LANGUAGE_NONE][0]['value'];
  }
  else {
    $taxon_name = t('No Taxon');
    $taxon_id = NULL;
  }

  $scientific_name = check_plain($node->title);
  if (!empty($node->field_scientific_name)) {
    $scientific_name = $node->field_scientific_name[LANGUAGE_NONE][0]['value'];
  }

  $child_count = '';
  if (!empty($node->field_parent)) {
    $search_path = $node->field_parent[LANGUAGE_NONE][0]['value'] . ','. $node->nid;
    // TODO: add caching here.
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bgpage')
          ->fieldCondition('field_parent', 'value', $search_path, 'CONTAINS');
    $count = $query->count()->execute();
    $child_count = ' ('. $count .')';
  }

  $output = "<span class=\"bgpage-taxon-title\">$taxon_name </span>";
  $italics = $taxon_id >= $TAXON_IDS["Genus"];
  $output .= "<span class=\"bgpage-taxon-desc\">";
  if ($italics) {
    $output .= "<i>";
  }
  $output .= l("<strong>$scientific_name</strong>", "node/" . $node->nid . "/tree", array('html' => TRUE));
  if ($italics) {
    $output .= "</i>";
  }
  if ($node->title != $scientific_name) {
    $output .= " - " . check_plain($node->title);
  }
  if (!empty($node->field_hodges_number)) {
    $output .= " - Hodges#" . $node->field_hodges_number[LANGUAGE_NONE][0]['value'];
  }
  $output .= "$child_count</span><br />\n";

  return $output;
}

