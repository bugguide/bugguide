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
    $query->addParam('fl', 'entity_id,label,sm_field_scientific_name');
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

    // Find the top rated images for each bgpage.
    foreach ($children_docs as $child_doc) {
      $child_doc->matches = _bgpage_search_representative_images_for($child_doc->entity_id);
      if (empty($child_doc->matches)) {
        $child_doc->matches = array();
      }
    }

    // Render results.
    foreach ($children_docs as $child_doc) {

      $name = $child_doc->label;
      if (!empty($child_doc->sm_field_scientific_name)) {
        $name .= ' - ' . $child_doc->sm_field_scientific_name[0];
      }
      $output .= '<div class="card mb-3"><div class="card-header"><h2 class="card-header-title"><a href="' . url('node/' . $child_doc->entity_id) . '" title="' . $child_doc->label . '">' . $name . ' <span class="icon"><span class="fa fa-angle-right" aria-hidden="true"></span></span></a></h2></div>';
      if (!empty($child_doc->matches)) {
        $output .= '<div class="card-content p-2 bg-image-list"><ul class="columns is-mobile is-multiline">';
        foreach ($child_doc->matches as $image_doc) {
          $output .= '<li class="column m-0">' . $image_doc->ss_bgimage_thumbnail . '</li>';
        }
        $output .= '</ul></div>';
      }
      else {
        $output .= '<div class="card-content"><p>No images found for this taxon.</p></div>';
      }
      $output .= '</div>';
    }

    // Print pager.
    $output .= '<p>' . theme('pager') . '</p>';
  }
  catch (Exception $e) {
    watchdog('bgpage', 'Could not connect to Solr to fetch data for !nid. Error was %error.', array(
      '!nid' => $node->nid,
      '%error' => $e->getMessage(),
    ), WATCHDOG_ERROR);
    $output = 'An unexpected error occurred while fetching images. Try again later or contact the administrator';
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
      // Group results by parent.
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

      $output .= '<div class="card mb-3"><div class="card-header"><div class="card-header-title has-text-weight-normal is-block">' . implode(' &raquo; ', $breadcrumbs) .'</div></div>';

      // Render a list of images for this group.
      $output .= '<div class="card-content p-2 bg-image-list"><ul class="columns is-mobile is-multiline">';
      foreach ($docs as $doc) {
        if (isset($doc->ss_bgimage_thumbnail)) {
          $output .= '<li class="column m-0">' . $doc->ss_bgimage_thumbnail . '</li>';
        } 
        else {
          // The image thumbnail has not been indexed by Solr. Fall back to MySQL.
          $output .= '<li class="column m-0">' . bgimage_thumb_link(node_load($doc->entity_id)) . '</li>';
        }
      }
      $output .= '</ul></div></div>';
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

/**
 * Callback to render representative images for a bgpage node.
 */
function bgpage_representative_images($field) {
  try {
    $node = $field['entity'];
    $limit_images_to_display = 8;
    $no_need_to_load_solr_documents = FALSE;
    $documents = array();
    $representative_images = array();
    if (!empty($node->field_representative_images[LANGUAGE_NONE][0]['value'])) {
      $field_representative_images_value = $node->field_representative_images[LANGUAGE_NONE][0]['value'];
      $representative_images__nids = explode(',', $field_representative_images_value);
      foreach ($representative_images__nids as $representative_images__nid) {
        $bgimage__node = node_load($representative_images__nid);
        // We do this to simulate this as apache solr fetching documents.
        // in order to merge them later.
        $document__representative_image = new stdClass();
        $document__representative_image->ss_bgimage_thumbnail =  bgimage_thumb_link($bgimage__node);
        $representative_images[] = $document__representative_image;
      }
      $limit_images_to_display = $limit_images_to_display - count($representative_images);
      // Remove representative images if we have more than our current limit to display.
      if (count($representative_images) > $limit_images_to_display) {
        // We get negative value so in array_splice it removes
        // the rest that exceeds the limits.
        $amount_to_remove = $limit_images_to_display - count($representative_images);
        array_splice($representative_images, $amount_to_remove);
        $no_need_to_load_solr_documents = TRUE;
        $documents = $representative_images;
      }
    }
    if (!$no_need_to_load_solr_documents) {
      $documents = _bgpage_search_representative_images_for($node->nid, $limit_images_to_display);
      // Loop representative images if so then they should be the first ones to be added.
      foreach (array_reverse($representative_images) as $representative_image) {
        array_unshift($documents, $representative_image);
      }
    }
    // Render a list of images.
    $output = '<div class="card mb-3"><div class="card-content p-2  bg-image-list"><ul class="columns is-mobile is-multiline">';
    foreach ($documents as $document) {
      if (isset($document->ss_bgimage_thumbnail)) {
        $output .= '<li class="column m-0">' . $document->ss_bgimage_thumbnail . '</li>';    
      }
      elseif (isset($document->entity_id)) {
        // The image thumbnail has not been indexed by Solr. Fall back to MySQL.
        $output .= '<li class="column m-0">' . bgimage_thumb_link(node_load($document->entity_id)) . '</li>';
      }
    }
    $output .= '</ul></div></div>';

    return $output;
  }
  catch (Exception $e) {
    watchdog('bgpage', 'Could not connect to Solr to fetch representative images for !nid. Error was %error.', array(
      '!nid' => $field['entity']->nid,
      '%error' => $e->getMessage(),
    ), WATCHDOG_ERROR);
  }
}

/**
 * Private callback to search for representative images.
 *
 * @param int $bgpage_nid
 *   A bgpage nid.
 * @param int $limit
 *   The limit to get images for. By default it is 8.
 *
 * @return array
 *   An array of Apache_Solr_Document objects.
 *
 * @throws \Exception
 *   When the Solr server cannot be reached or the query failed.
 */
function _bgpage_search_representative_images_for($bgpage_nid, $limit = 8) {
  // Filter images with this child nid as their parent.
  $filter_parent = new SolrFilterSubQuery('AND');
  $filter_parent->addFilter('sm_bgimage_parents', $bgpage_nid);

  $query = apachesolr_drupal_query('representative_images_' . $bgpage_nid, array());
  $query->addFilterSubQuery($filter_parent);
  $query->addParam('fl', 'entity_id,ss_bgimage_thumbnail');
  $query->addParam('rows', $limit);
  $query->addParam('sort', 'is_bgimage_rating_avg desc');
  $query->addParam('sort', 'is_bgimage_rating_count desc');

  // Query Solr and attach images to the child's document.
  list(, $response) = apachesolr_do_query($query);
  return $response->response->docs;
}
