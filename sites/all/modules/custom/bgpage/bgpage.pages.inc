<?php
/**
 * Page callbacks for bgpage module.
 */

/**
 * Generate the taxonomic tree from the root (Arthropoda) to the current taxon.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgpage_tree($nid) {
  $query = drupal_get_query_parameters();
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }
  $output = '';

  // First, create the filter that loads parent taxons plus the current one.
  $main_filter = new SolrFilterSubQuery('OR');
  $main_filter->addFilterSubQuery(_bgpage_create_solr_filter_for($node));

  // Next, decide whether we want to list immediate children or the full tree.
  if (!isset($query['expand'])) {
    $immediate_parent_filter = new SolrFilterSubQuery('AND');
    $immediate_parent_filter->addFilter('ss_bgpage_immediate_parent', $nid);
    $main_filter->addFilterSubQuery($immediate_parent_filter);

    // Add a link to expand the tree.
    $link = l(
      t('Expand Tree'), 
      'node/' . $node->nid . '/tree', 
      array( 
        'title' => t('Show everything below this guide page.'),
        'query' => array('expand' => NULL),
        'attributes' => array(
          'class' => array(
            'button', 
            'is-small',
            ),
          ),
        )
      );
    }
    else {
    $parent_filter = new SolrFilterSubQuery('AND');
    $parent_filter->addFilter('sm_bgpage_parents', $nid);
    $main_filter->addFilterSubQuery($parent_filter);

    // Add a link to collapse the tree.
    $link = l(
      t('Collapse Tree'), 
      'node/' . $node->nid . '/tree', 
      array( 
        'title' => t('Show the normal view.'),
        'attributes' => array(
          'class' => array(
            'button', 
            'is-small',
            ),
          ),
        )
      );
    }

  // Fetch the tree from Apache Solr.
  $classified_results = bgpage_fetch_classification($node->nid, $main_filter);

  // Render the results.
  if (empty($classified_results)) {
    $output = '<p>No results found.</p>';
  }
  else {
    $output = bgpage_tree_build($classified_results) .'<p>' . $link . '</p>';
  }

  return $output;
}

/**
 * Browses images in immediate descendants of a bgpage node.
 */
function bgpage_browse($nid) {
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }
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
  if (!$node) {
    return MENU_NOT_FOUND;
  }
  return node_view($node, 'images');
}

/**
 * Shows images for a bgpage node.
 *
 * Traverses the tree in a Breadth-first way showing bgrefs for each leaf.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgpage_bgref($nid) {
  return views_embed_view('all_books', 'by_bgpage', $nid);
}

/**
 * Shows links for a bgpage node.
 *
 * Traverses the tree in a Breadth-first way showing bglinks for each leaf.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgpage_bglink($nid) {
  return views_embed_view('links', 'by_bgpage', $nid);
}
