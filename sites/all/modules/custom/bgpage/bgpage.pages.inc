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
    // If we're in reorder mode we'll display the children in a separate form.
    if ($mode != 'reorder') {
      $immediate_parent_filter = new SolrFilterSubQuery('AND');
      $immediate_parent_filter->addFilter('ss_bgpage_immediate_parent', $nid);
      $main_filter->addFilterSubQuery($immediate_parent_filter);
    }

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
    if ($mode == 'add' || $mode == 'reorder') {
      // Add the form that goes with the corresponding mode.
      $form_array = '';
      if ($mode == 'add') {
        $form_array = drupal_get_form('bgpage_quickadd_guide_page_form', $node);
      }
      else {
        // Get this node's children.
        $children_results = bgpage_fetch_children_by_weight($nid);
        $form_array = drupal_get_form('bgpage_reorder_guide_page_form', $node, $children_results);
      }
      $output .= drupal_render($form_array);
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
      // If the nid of the last result in the tree is the node we're on then
      // there are no children, so don't offer to reorder them.
      if ($classified_results[count($classified_results) - 1]->entity_id != $nid) {
        $links[] = l(
          t('Reorder Guide'),
          'node/' . $nid . '/tree/reorder',
          array(
            'title' => t('Reorder the children of this guide page'),
            'attributes' => array('class' => array('button', 'is-small')),
          )
        );
      }
    }
  }

  $output .= '<div class="taxonomy-tree-links"> ' . implode(' ', $links) . '</div>';

  return $output;
}

/**
 * Form for reordering children of a taxon from the taxonomic view.
 *
 * @param $node
 *   The node object of the node whose children are to be reordered.
 *
 * @param $children_results
 *   Array of solr query results for immediate children of $node.
 */
function bgpage_reorder_guide_page_form($form, $form_state, $node, $children_results) {
  $form['#attributes'] = array('class' => 'guide-edit-form');

  $form['reorder-instructions'] = array(
    '#markup' => '<p>Change numeric values and click Reorder to change the display order of the given children. No need to use only multiples of 10 (the system will internally change your values to multiples of 10).</p>',
    '#prefix' => '<div class="guide-reorder-directions">',
    '#suffix' => '</div>',
  );

  // Keep an array of child nids to make validation and submission processing
  // easier.
  $form['nids'] = array(
    '#type' => 'value',
    '#value' => array(),
  );

  $weight = 10;
  foreach($children_results as $result) {
    $form['nids']['#value'][] = $result->entity_id;
    $child_title = bgpage_tree_child($result);
    $form['reorder-' . $result->{'entity_id'}] = array(
      '#type' => 'textfield',
      '#default_value' => $weight,
      '#size' => 3,
      '#maxlength' => 3,
      '#field_suffix' => $child_title,
    );
    $weight += 10;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Reorder'),
  );

  return $form;
}

function bgpage_reorder_guide_page_form_validate($form, &$form_state) {
  $weights = array();
  foreach($form_state['values']['nids'] as $nid) {
    $weight = $form_state['values']['reorder-' . $nid];
    if (!is_numeric($weight)) {
      form_set_error('reorder-' . $nid, t('Please enter a numeric value.'));
      continue;
    }
    if (in_array($weight, $weights)) {
      form_set_error('reorder-' . $nid, t('No number can be repeated.'));
      continue;
    }
    $weights[] = $weight;
  }
}

function bgpage_reorder_guide_page_form_submit($form, &$form_state) {
  foreach ($form_state['values']['nids'] as $nid) {
    $weight = $form_state['values']['reorder-' . $nid];
    $old_weight = db_query('SELECT field_weight_value FROM {field_data_field_weight} WHERE entity_id = :nid', array(':nid' => $nid))->fetchField();
    if ($weight != $old_weight) {
      $node_wrapper = entity_metadata_wrapper('node', $nid);
      $node_wrapper->field_weight->set($weight);
      $node_wrapper->save();
    }
  }

  drupal_set_message(t('Ordering updated.'));
  $form_state['redirect'] = 'node/' . $form_state['build_info']['args'][0]->nid . '/tree';
}

/**
 * Form for adding a guide page from the taxonomic view.
 *
 * @param $node
 *   The node object of the node to add guide page below.
 */
function bgpage_quickadd_guide_page_form($form, $form_state, $node) {
  $form['#attributes'] = array('class' => 'guide-edit-form');

  $options = bgpage_get_allowed_children($node->field_taxon[LANGUAGE_NONE][0]['value']);

  $soon_to_be_parent = _bg_get_title_classification($node);
  $form['taxon'] = array(
    '#title' => t('Add taxon'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => count($options) - 1,
    '#prefix' => '<div><strong>You are about to add a new taxon under '. $soon_to_be_parent[1] . ':</strong></div>',
  );

  // We name these form field inputs after their node field names so that we can
  // share validation code with the full guide page form validation function.
  $form['field_scientific_name'] = array(
    '#title' => t('Scientific Name'),
    '#type' => 'textfield',
    '#description' => t("Leave blank when choosing 'No Taxon'."),
  );

  $form['field_common_name'] = array(
    '#title' => t('Preferred Common Name'),
    '#type' => 'textfield',
    '#description' => t('Try to find a unique common name. Otherwise leave this blank and the scientific name will be used.'),
  );

  $form['original_nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}

function bgpage_quickadd_guide_page_form_validate($form, &$form_state) {
  global $TAXON_IDS;
  $parent_node = node_load($form_state['values']['original_nid']);
  $parent = $parent_node->{'field_parent'}[LANGUAGE_NONE][0]['value'] . ',' . $form_state['values']['original_nid'];
  $taxon_name = $form['taxon']['#options'][$form_state['values']['taxon']];
  // For validation purposes we don't need to know the taxon id of a new No
  // Taxon node (that will be determined in the submit function) - for now any
  // index that's not a key of $TAXON_NAMES will do.
  $taxon = isset($TAXON_IDS[$taxon_name]) ? $TAXON_IDS[$taxon_name] : -1;

  _bgpage_shared_form_validate(
    $form_state['values']['field_scientific_name'],
    $form_state['values']['field_common_name'],
    $parent,
    $taxon,
    NULL,
  );
}

function bgpage_quickadd_guide_page_form_submit($form, &$form_state) {
  global $user, $TAXON_IDS;
  $parent_node = node_load($form_state['values']['original_nid']);
  $parent_wrapper = entity_metadata_wrapper('node', $parent_node);

  $new_node_values = array(
    'type' => 'bgpage',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 1, // Comments disabled
    'promoted' => 1
  );
  $new_node = entity_create('node', $new_node_values);
  $new_node_wrapper = entity_metadata_wrapper('node', $new_node);

  $parent = $parent_wrapper->field_parent->value() . ',' . $parent_node->nid;
  $new_node_wrapper->field_parent->set($parent);

  $taxon_name = $form['taxon']['#options'][$form_state['values']['taxon']];
  if ($taxon_name == t('No Taxon')) {
    $new_node_wrapper->field_taxon->set($parent_wrapper->field_taxon->value() + 1);
  }
  else {
    $new_node_wrapper->field_taxon->set($TAXON_IDS[$taxon_name]);
    $new_node_wrapper->field_scientific_name->set($form_state['values']['field_scientific_name']);
  }

  // The validation code sets a common name if one wasn't entered, so we'll
  // always have a common name.
  $new_node_wrapper->field_common_name->set($form_state['values']['field_common_name']);

  // The title is always the common name.
  $new_node_wrapper->title->set($new_node_wrapper->field_common_name->value());

  $new_node_wrapper->save();

  watchdog('bgpage', 'added %title', array('%title' => $new_node_wrapper->title->value()), WATCHDOG_NOTICE, 'node/' . $new_node_wrapper->nid->value());

  drupal_set_message(t('Guide page added.'));
  $form_state['redirect'] = 'node/' . $new_node_wrapper->nid->value();
}

/**
 * Given a taxon, return an array of allowed taxa
 * that may be placed here. E.g., you cannot place
 * a family into a genus.
 *
 * @param $taxon
 *   A taxon ID from global $TAXON_NAMES.
 * @return array
 *   Array of allowed taxon IDs.
 */
function bgpage_get_allowed_children($taxon) {
  global $TAXON_NAMES, $TAXON_IDS;
  $allowed = array();
  $allowed[] = 'No Taxon';
  foreach ($TAXON_NAMES as $taxon_id => $taxon_name)  {
    if ($taxon_id <= $taxon) {
      continue;
    }

    $allowed[] = $taxon_name;

    if (bgpage_is_taxon_required($taxon_name)) {
      break;
    }
  }

  return $allowed;
}

function bgpage_is_taxon_required($taxon) {
  switch ($taxon) {
    case 'Phylum':
    case 'Class':
    case 'Order':
    case 'Family':
    case 'Genus':
    case 'Species':
      return TRUE;
    default:
      return FALSE;
  }
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
