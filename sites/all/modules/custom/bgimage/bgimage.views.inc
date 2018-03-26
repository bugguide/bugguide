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

  // Add a custom field handler for rendering the immediate parent.
  $data['field_data_field_parent']['immediate_parent'] = array(
    'group' => 'Content',
    'title' => t('Immediate parent'),
    'title short' => t('Immediate parent'),
    'help' => t('Renders a link to the immediate parent.'),
    'real field' => 'field_parent_value',
    'field' => array(
      'handler' => 'bgimage_handler_immediate_parent',
    ),
  );

  // Add a custom filter for excluding images classified at the species level.
  $data['field_data_field_parent']['species_level'] = array(
    'group' => 'Content',
    'title' => t('Is not classified at species level'),
    'title short' => t('Species level'),
    'help' => t('Filters images whose immediate parent is at the species level.'),
    'real field' => 'field_parent_value',
    'filter' => array(
      'handler' => 'bgimage_handler_filter_species_level',
    ),
  );

  // Add a custom filter for hiding the Images column.
  $data['field_data_field_bgimage_image']['hide_images'] = array(
    'group' => 'Content',
    'title' => t('Hide images'),
    'title short' => t('Hide images'),
    'help' => t('Hides the images column.'),
    'real field' => 'field_bgimage_image_fid',
    'filter' => array(
      'handler' => 'bgimage_handler_filter_hide_images',
    ),
  );

  // Add a custom filter for filtering by month
  $data['field_data_field_bgimage_date']['month'] = array(
    'group' => 'Content',
    'title' => t('Month taken'),
    'title short' => t('Month taken'),
    'help' => t('Filters images taken in a given month.'),
    'real field' => 'field_bgimage_date_value',
    'filter' => array(
      'handler' => 'bgimage_handler_filter_month',
    ),
  );
}
