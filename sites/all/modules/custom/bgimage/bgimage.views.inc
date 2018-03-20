<?php

/**
 * @file
 * Views definitions for bgimage module.
 */

/**
 * Implements hook_views_data_alter().
 */
function bgimage_views_data_alter(&$data) {
  // Add a custom filter for searching a taxon in the tree.
  $data['field_data_field_parent']['parent_ancestor'] = array(
    'group' => 'Content',
    'title' => t('Parent ancestor'),
    'title short' => t('Parent ancestor'),
    'help' => t('Filters content that contains the given taxon in the parent tree.'),
    'real field' => 'field_parent_value',
    'filter' => array(
      'handler' => 'bgimage_handler_filter_parent',
    ),
  );
}
