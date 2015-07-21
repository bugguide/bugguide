<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  $node = $field['entity'];
  $parent_nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);

  $nodes = bg_prepare_nodes($parent_nids, 'bgpage');
  // Fetch titles.
  $result = db_query('SELECT nid, title FROM {node} WHERE nid IN (:nids)', array(':nids' => $parent_nids));
  foreach ($result as $row) {
    $nodes[$row->nid]->title = $row->title;
  }
  // Fetch taxon and scientific name.
  $nodes = bg_field_load_multiple('field_parent', $nodes);
  $nodes = bg_field_load_multiple('field_taxon', $nodes);
  $nodes = bg_field_load_multiple('field_scientific_name', $nodes);

  // Append current node at the end.
  $nodes[] = $node;

  // Build classification tree.
  return bgpage_tree_build($nodes);
}

/**
 * Callback to render citations in a bgpage node.
 */
function _bgpage_citations($field) {
  $node = $field['entity'];
  if (empty($node->field_citations[LANGUAGE_NONE])) {
    return t('There are no citations.');
  }

  $wrapper = entity_metadata_wrapper('node', $node);
  if (!$wrapper->field_citations->count()) {
    return t('There are no citations.');
  }

  $list_items = '<ol>';
  foreach ($wrapper->field_citations->getIterator() as $delta => $item_wrapper) {
    $bgref_node = node_load($item_wrapper->value());
    if (!empty($bgref_node)) {
      $list_items .= '<li>' . l($bgref_node->title, 'node/' . $bgref_node->nid);
      // Append book details if they are available.
      $book_details = array();
      if (isset($bgref_node->custom_fields['author'])) {
        $book_details[] = check_plain($bgref_node->custom_fields['author']);
      }
      if (isset($bgref_node->custom_fields['year'])) {
        $book_details[] = check_plain($bgref_node->custom_fields['year']);
      }
      if (isset($bgref_node->custom_fields['publisher'])) {
        $book_details[] = check_plain($bgref_node->custom_fields['publisher']);
      }
      if (count($book_details)) {
        $list_items .= '</br>' . implode('. ', $book_details) . '.';
      }
      $list_items .= '</li>';
    }
  }
  $list_items .= '</ol>';
  return $list_items;
}
