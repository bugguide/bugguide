<?php

/**
 * @file
 * bgimage.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bgimage_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgimage|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgimage';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'divider_1' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'divider_2' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'divider_3' => array(
      'weight' => '16',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'location_combined' => array(
      'weight' => '7',
      'label' => 'above',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '21',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '17',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
    'bgimage_clip' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_photo_number' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_copyright' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_related' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_title_classification' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgsubscriptions_subscriptions' => array(
      'weight' => '20',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgpage_citations' => array(
      'weight' => '7',
      'label' => 'above',
      'format' => 'default',
    ),
  );
  $export['node|bgimage|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgimage|homepage';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgimage';
  $ds_fieldsetting->view_mode = 'homepage';
  $ds_fieldsetting->settings = array(
    'bgimage_field_placed_by' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgimage|homepage'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgimage|recent';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgimage';
  $ds_fieldsetting->view_mode = 'recent';
  $ds_fieldsetting->settings = array(
    'location_combined' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => '',
      ),
    ),
    'submitted_by' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
    'bgimage_field_taxonomy_path' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgimage|recent'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function bgimage_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'divider_1';
  $ds_field->label = 'Divider 1';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<hr>',
      'format' => 'u',
    ),
    'use_token' => 0,
  );
  $export['divider_1'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'divider_2';
  $ds_field->label = 'Divider 2';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<hr>',
      'format' => 'u',
    ),
    'use_token' => 0,
  );
  $export['divider_2'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'divider_3';
  $ds_field->label = 'Divider 3';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<hr>',
      'format' => 'u',
    ),
    'use_token' => 0,
  );
  $export['divider_3'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'recent_images';
  $ds_field->label = 'Recent images';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|recent_images-block',
    'block_render' => '1',
  );
  $export['recent_images'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bgimage_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'megapanels';
  $ds_layout->settings = array(
    'regions' => array(
      'top_grow_first' => array(
        0 => 'field_bgimage_image',
        1 => 'bgimage_photo_number',
        2 => 'bgimage_copyright',
        3 => 'bgimage_clip',
        4 => 'bgimage_related',
        5 => 'bgimage_title_classification',
        6 => 'body',
        7 => 'bgpage_citations',
      ),
      'top_1' => array(
        8 => 'location_combined',
        9 => 'field_bgimage_date',
        10 => 'divider_1',
        11 => 'field_bgimage_life_stage',
        12 => 'field_bgimage_sex',
        13 => 'field_bgimage_size',
        14 => 'divider_2',
        15 => 'field_bgimage_representative',
        16 => 'field_bgimage_photo_quality',
        17 => 'divider_3',
        18 => 'submitted_by',
      ),
      'bottom_full' => array(
        19 => 'field_tags',
        20 => 'bgsubscriptions_subscriptions',
        21 => 'comments',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'top_grow_first',
      'bgimage_photo_number' => 'top_grow_first',
      'bgimage_copyright' => 'top_grow_first',
      'bgimage_clip' => 'top_grow_first',
      'bgimage_related' => 'top_grow_first',
      'bgimage_title_classification' => 'top_grow_first',
      'body' => 'top_grow_first',
      'bgpage_citations' => 'top_grow_first',
      'location_combined' => 'top_1',
      'field_bgimage_date' => 'top_1',
      'divider_1' => 'top_1',
      'field_bgimage_life_stage' => 'top_1',
      'field_bgimage_sex' => 'top_1',
      'field_bgimage_size' => 'top_1',
      'divider_2' => 'top_1',
      'field_bgimage_representative' => 'top_1',
      'field_bgimage_photo_quality' => 'top_1',
      'divider_3' => 'top_1',
      'submitted_by' => 'top_1',
      'field_tags' => 'bottom_full',
      'bgsubscriptions_subscriptions' => 'bottom_full',
      'comments' => 'bottom_full',
    ),
    'classes' => array(),
    'wrappers' => array(
      'top_full' => 'div',
      'top_grow_first' => 'div',
      'top_1' => 'div',
      'top_2' => 'div',
      'top_3' => 'div',
      'top_4' => 'div',
      'top_grow_last' => 'div',
      'middle_grow_first' => 'div',
      'middle_1' => 'div',
      'middle_2' => 'div',
      'middle_3' => 'div',
      'middle_4' => 'div',
      'middle_grow_last' => 'div',
      'bottom_grow_first' => 'div',
      'bottom_1' => 'div',
      'bottom_2' => 'div',
      'bottom_3' => 'div',
      'bottom_4' => 'div',
      'bottom_grow_last' => 'div',
      'bottom_full' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '1',
    'page_option_title' => '',
  );
  $export['node|bgimage|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|homepage';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'homepage';
  $ds_layout->layout = 'card';
  $ds_layout->settings = array(
    'regions' => array(
      'image' => array(
        0 => 'field_bgimage_image',
      ),
      'body' => array(
        1 => 'bgimage_field_placed_by',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'image',
      'bgimage_field_placed_by' => 'body',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'image' => 'div',
      'body' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|bgimage|homepage'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|recent';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'recent';
  $ds_layout->layout = 'horizontalcard';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_bgimage_image',
      ),
      'body' => array(
        1 => 'title',
        2 => 'location_combined',
        3 => 'submitted_by',
        4 => 'bgimage_field_taxonomy_path',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'left',
      'title' => 'body',
      'location_combined' => 'body',
      'submitted_by' => 'body',
      'bgimage_field_taxonomy_path' => 'body',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'body' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|bgimage|recent'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'horizontalcard';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_bgimage_image',
      ),
      'body' => array(
        1 => 'title',
        2 => 'location_combined',
        3 => 'divider_1',
        4 => 'submitted_by',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'left',
      'title' => 'body',
      'location_combined' => 'body',
      'divider_1' => 'body',
      'submitted_by' => 'body',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'body' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|bgimage|teaser'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function bgimage_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'recent';
  $ds_view_mode->label = 'Recent';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['recent'] = $ds_view_mode;

  return $export;
}
