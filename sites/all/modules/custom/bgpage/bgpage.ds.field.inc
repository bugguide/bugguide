<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  if (!in_array($field['view_mode'], array('full', 'browse', 'images'))) {
    return;
  }

  $node = $field['entity'];

  $classification_filter = _bgpage_create_solr_filter_for($node);
  $classified_results = bgpage_fetch_classification($node->nid, $classification_filter);
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


/**
 * Callback to render images from immediate children.
 *
 * @param array $field
 *   A Display Suite field.
 *
 * @return string
 *   HTML output containing the listing.
 */
function _bgpage_browse($field) {
  if ($field['view_mode'] != 'browse') {
    return;
  }

  $output = '';
  $node = $field['entity'];
  $results_per_page = 5;

  try {
    // Fetch immediate children for this bgpage node.
    $immediate_children = new SolrFilterSubQuery('AND');
    $immediate_children->addFilter('ss_bgpage_immediate_parent', $node->nid);
    $query = apachesolr_drupal_query('browse_images', array());

    // Configure query.
    $query->addFilterSubQuery($immediate_children);
    $query->addParam('fl', 'entity_id,label');
    $sort_field = 'sort_label';
    $sort_direction = 'asc';
    $query->setAvailableSort($sort_field, array(
      'title' => t('Label'),
      'default' => $sort_direction,
    ));
    $query->setSolrsort($sort_field, $sort_direction);
    // Set paging and results per page.
    $query->page = pager_find_page();
    $query->addParam('rows', $results_per_page);

    // Run query.
    list(, $response) = apachesolr_do_query($query);
    $children_docs  = $response->response->docs;
    pager_default_initialize($response->response->numFound, $results_per_page);

    // If this bgpage node has no children, then create an array with a dummy
    // document containing the current bgpage.
    if (empty($children_docs)) {
      $document = new ApacheSolrDocument();
      $document->entity_id = $node->nid;
      $document->label = check_plain($node->title);
      $children_docs[] = $document;
    }

    // Find the top rated 5 images for each bgpage.
    foreach ($children_docs as $child_doc) {
      // Filter images with this child nid as their parent.
      $filter_parent = new SolrFilterSubQuery('AND');
      $filter_parent->addFilter('sm_bgimage_parents', $child_doc->entity_id);

      $query = apachesolr_drupal_query('browse_images_' . $child_doc->entity_id, array());
      $query->addFilterSubQuery($filter_parent);
      $query->addParam('fl', 'ss_bgimage_thumbnail');
      $query->addParam('rows', 5);
      $query->addParam('sort', 'is_bgimage_rating_avg desc');
      $query->addParam('sort', 'is_bgimage_rating_count desc');

      // Query Solr and attach images to the child's document.
      list(, $response) = apachesolr_do_query($query);
      $child_doc->matches = array();
      $child_doc->matches = $response->response->docs;
    }

    // Render results.
    foreach ($children_docs as $child_doc) {
      $output .= '<h3><a href="' . url('node/' . $child_doc->entity_id) . '" title="' . $child_doc->label . '">' . $child_doc->label . '</a></h3>';
      if (!empty($child_doc->matches)) {
        $output .= '<ul>';
        foreach ($child_doc->matches as $image_doc) {
          $output .= '<li class="horizontal">' . $image_doc->ss_bgimage_thumbnail . '</li>';
        }
        $output .= '</ul>';
      }
      else {
        $output .= '<p>No images found for this taxon.</p>';
      }
    }

    // Print pager.
    $output .= '<p>' . theme('pager') . '</p>';
  }
  catch (Exception $e) {
    watchdog('bgpage', 'Could not connect to Solr to fetch data for !nid. Error was %error.', array(
      '!nid' => $node->nid,
      '%error' => $e->getMessage(),
    ), WATCHDOG_ERROR);
    $output = 'An unexpected error ocurred while fetching images. Try again later or contact the administrator';
  }

  return $output;
}

/**
 * Callback to render all images for a bgpage node.
 */
function _bgpage_images($field) {
  if ($field['view_mode'] != 'images') {
    return;
  }

  $output = '';
  $results_per_page = 25;
  $node = $field['entity'];
  $node_wrapper = entity_metadata_wrapper('node', $node);

  // Fetch images who have this node as an ancestor.
  $filter = new SolrFilterSubQuery('AND');
  $filter->addFilter('sm_bgimage_parents', $node->nid);
  try {
    $query = apachesolr_drupal_query('images', array());
    // Configure query.
    $query->addFilterSubQuery($filter);
    $query->addParam('fl', 'entity_id,label,ss_bgimage_thumbnail,ss_bgimage_classification,is_bgimage_immediate_parent,sm_bgimage_parents,sm_bgimage_breadcrumbs');
    // Sort by classification (full list of parents including bgimage nid at the end),
    // and then by rating.
    $query->addParam('sort', 'ss_bgimage_classification desc');
    $query->addParam('sort', 'is_bgimage_rating_avg desc');
    $query->addParam('sort', 'is_bgimage_rating_count desc');
    // Set paging and results per page.
    $query->page = pager_find_page();
    $query->addParam('rows', $results_per_page);

    // Run query and render results if matches are found.
    list($final_query, $response) = apachesolr_do_query($query);
    if ($response->code == '200' && $response->response->numFound > 0) {
      // Group resuls by parent.
      $docs_by_parent = array();
      foreach ($response->response->docs as $doc) {
        $docs_by_parent[$doc->is_bgimage_immediate_parent][] = $doc;
      }
    }
    else {
      watchdog('bgpage', 'No images found for nid !nid', array('!nid' => $node->nid));
    }
  }
  catch (Exception $e) {
    watchdog('bgpage', 'Could not connect to Solr to fetch data for !nid. Error was %error.', array(
      '!nid' => $node->nid,
      '%error' => $e->getMessage(),
    ), WATCHDOG_ERROR);
  }

  // Render results.
  if (isset($docs_by_parent)) {
    foreach ($docs_by_parent as $parent_nid => $docs) {
      // Build a breadcrumb list for this taxon.
      $breadcrumbs = $docs[0]->sm_bgimage_breadcrumbs;
      $node_parents = $node_wrapper->field_parent->value();
      if (!empty($node_parents)) {
        $node_parent_nids = explode(',', $node_parents);
        array_splice($breadcrumbs, 0, count($node_parent_nids) +1 );
      }
      $output .= implode(' &raquo; ', $breadcrumbs);

      // Render a list of images for this group.
      $output .= '<ul>';
      foreach ($docs as $doc) {
        $thumbnail = isset($doc->ss_bgimage_thumbnail) ? $doc->ss_bgimage_thumbnail : '<!-- missing thumbnail for ' . $doc->entity_id . ' -->';
        $output .= '<li class="horizontal">' . $thumbnail . '</li>';
      }
      $output .= '</ul>';
    }

    // Print pager.
    pager_default_initialize($response->response->numFound, $results_per_page);
    $output .= '<p>' . theme('pager') . '</p>';
  }
  else {
    $output = 'No images found for this classification.';
  }
  return $output;
}
