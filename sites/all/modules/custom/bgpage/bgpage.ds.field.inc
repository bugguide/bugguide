<?php
/**
 * @file
 * Display suite callbacks.
 */

/**
 * Callback to render a guide page's classification tree.
 */
function _bgpage_classification($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

  $node = $field['entity'];
  // Extract parent nids.
  $nids = explode(',', $node->field_parent[LANGUAGE_NONE][0]['value']);
  // Append current node at the end.
  $nids[] = $node->nid;

  // Build classification tree.
  $classified_results = bgpage_fetch_classification($nids);
  return bgpage_tree_build($classified_results);
}

/**
 * Callback to render citations in a bgpage node.
 */
function _bgpage_citations($field) {
  if ($field['view_mode'] != 'full') {
    return;
  }

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
