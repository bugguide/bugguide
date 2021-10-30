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
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }

  $mode = arg(3) ? arg(3) : 'normal';
  $query = drupal_get_query_parameters();

  $links = array();
  $output = '';

  // First, create the filter that loads parent taxons plus the current one.
  $main_filter = new SolrFilterSubQuery('OR');
  $main_filter->addFilterSubQuery(_bgpage_create_solr_filter_for($node));

  // Next, decide whether we want to list immediate children or the full tree.
  if (!isset($query['expand'])) {
    $immediate_parent_filter = new SolrFilterSubQuery('AND');
    $immediate_parent_filter->addFilter('ss_bgpage_immediate_parent', $nid);
    $main_filter->addFilterSubQuery($immediate_parent_filter);

    // Only offer to expand the tree in normal view mode.
    if ($mode == 'normal') {
      // Add a link to expand the tree.
      $links[] = l(
        t('Expand Tree'),
        'node/' . $nid . '/tree',
        array(
          'title' => t('Show everything below this guide page.'),
          'query' => array('expand' => NULL),
          'attributes' => array('class' => array('button', 'is-small')),
        )
      );
    }
  }
  else {
    $parent_filter = new SolrFilterSubQuery('AND');
    $parent_filter->addFilter('sm_bgpage_parents', $nid);
    $main_filter->addFilterSubQuery($parent_filter);

    // Add a link to collapse the tree.
    $links[] = l(
      t('Collapse Tree'),
      'node/' . $nid . '/tree',
      array(
        'title' => t('Show the normal view.'),
        'attributes' => array('class' => array('button', 'is-small')),
      )
    );
  }

  // Fetch the tree from Apache Solr.
  $classified_results = bgpage_fetch_classification($node->nid, $main_filter);

  if (empty($classified_results)) {
    return '<p>No results found.</p>';
  }

  $output = bgpage_tree_build($classified_results);

  global $TAXON_IDS;
  $node_taxon = $node->field_taxon[LANGUAGE_NONE][0]['value'];
  if (user_access('create bgpage content') && $node_taxon < $TAXON_IDS['Subspecies']) {
    if ($mode == 'add') {
      // Add form for adding new guide page.
      //$output .= drupal_get_form('bgpage_quickadd_guide_page_form', $node);
      $links[] = l(
        t('Normal View'),
        '/node/' . $nid . '/tree',
        array(
          'attributes' => array('class' => array('button', 'is-small')),
        )
      );
    }
    else {
      $links[] = l(
        t('Add Guide'),
        'node/' . $nid . '/tree/add',
        array(
          'title' => t('Add a guide page below this one'),
          'attributes' => array('class' => array('button', 'is-small')),
        )
      );
    }
  }

  $output .= '<div class="taxonomy-tree-links"> ' . implode(' ', $links) . '</div>';

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
 * Shows book references for a bgpage node.
 *
 * Traverses the tree in a Breadth-first way showing bgrefs for each leaf.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgpage_bgref($nid) {
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }
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
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }
  return views_embed_view('links', 'by_bgpage', $nid);
}
