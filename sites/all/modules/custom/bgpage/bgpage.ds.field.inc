<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  if (!in_array($field['view_mode'], array('full', 'browse'))) {
    return;
  }

  $node = $field['entity'];

  // Extract parent nids.
  if (!empty($node->field_parent[LANGUAGE_NONE])) {
    $nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);
  }
  else {
    $nids = array();
  }

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


/**
 * Callback to render images from immediate children.
 */
function _bgpage_browse($field) {
  if ($field['view_mode'] != 'browse') {
    return;
  }

  $output = '';
  $node = $field['entity'];

  // Fetch immediate children nids.
  $filter = new SolrFilterSubQuery('AND');
  $filter->addFilter('ss_bgpage_immediate_parent', $node->nid);
  try {
    $query = apachesolr_drupal_query('browse_children', array());
    // Configure query.
    $query->addFilterSubQuery($filter);
    $query->addParam('fl', 'entity_id');
    $query->addParam('rows', 10000000);
    $sort_field = 'sort_bgpage_classification';
    $sort_direction = 'asc';
    $query->setAvailableSort($sort_field, $sort_direction);
    $query->setSolrsort($sort_field, $sort_direction);

    // Run query and render results if matches are found.
    $children_nids = array();
    list($final_query, $response) = apachesolr_do_query($query, pager_find_page());
    if ($response->code == '200' && $response->response->numFound > 0) {
      foreach ($response->response->docs as $doc) {
        $children_nids[] = $doc->entity_id;
      }
    }
    else {
      watchdog('bgpage', 'No results found for nid !nid', array('!nid' => $nid));
    }

    // Fetch best rated images for each child.
    if (count($children_nids)) {
      $filter_parent = new SolrFilterSubQuery('OR');
      foreach ($children_nids as $child_nid) {
        $filter_parent->addFilter('sm_bgpage_parents', $child_nid);
      }
      $filter_bundle = new SolrFilterSubQuery('AND');
      $filter_bundle->addFilter('bundle', 'bgimage');
      $main_filter = new SolrFilterSubQuery('AND');
      $main_filter->addFilterSubQuery($filter_bundle);
      $main_filter->addFilterSubQuery($filter_parent);

      $query = apachesolr_drupal_query('browse_images', array());
      // Configure query.
      $query->addFilterSubQuery($main_filter);
      $query->addParam('fl', 'ss_bgimage_thumbnail');
      $query->addParam('rows', 10);
      $query->addParam('sort', 'is_bgimage_rating_avg desc');
      $query->addParam('sort', 'is_bgimage_rating_count desc');

      // Run query and render results if matches are found.
      $children_nids = array();
      list($final_query, $response) = apachesolr_do_query($query, pager_find_page());

      if ($response->code == '200' && $response->response->numFound > 0) {
        $output .= '<ul>';
        foreach ($response->response->docs as $doc) {
          $output .= '<li>' . $doc->ss_bgimage_thumbnail . '</li>';
        }
        $output .= '</ul>';
      }
      else {
        watchdog('bgpage', 'No results found for nid !nid', array('!nid' => $node->nid));
      }
    }
  }
  catch (Exception $e) {
    watchdog('bgpage', 'Could not connect to Solr to fetch data for !nid. Error was %error.', array(
      '!nid' => $nid,
      '%error' => $e->getMessage(),
    ), WATCHDOG_ERROR);
  }

  if (empty($output)) {
    $output = 'No results found';
  }
  return $output;
}
