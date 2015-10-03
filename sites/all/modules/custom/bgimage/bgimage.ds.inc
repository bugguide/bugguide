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
    'comments' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
    'bgimage_tag' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_photo_number' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_copyright' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_related' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgimage_title_classification' => array(
      'weight' => '6',
      'label' => 'hidden',
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
    'title' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => '',
      ),
    ),
    'submitted_by' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
    'bgimage_field_taxonomy_path' => array(
      'weight' => '0',
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
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'bgimage_photo_number',
        1 => 'field_bgimage_image',
        2 => 'bgimage_copyright',
        3 => 'field_bgimage_representative',
        4 => 'field_bgimage_photo_quality',
        5 => 'bgimage_tag',
        6 => 'bgimage_title_classification',
        7 => 'field_bgimage_location',
        8 => 'field_bgimage_date',
        9 => 'field_bgimage_size',
        10 => 'body',
        11 => 'bgimage_related',
        12 => 'submitted_by',
        13 => 'comments',
      ),
    ),
    'fields' => array(
      'bgimage_photo_number' => 'ds_content',
      'field_bgimage_image' => 'ds_content',
      'bgimage_copyright' => 'ds_content',
      'field_bgimage_representative' => 'ds_content',
      'field_bgimage_photo_quality' => 'ds_content',
      'bgimage_tag' => 'ds_content',
      'bgimage_title_classification' => 'ds_content',
      'field_bgimage_location' => 'ds_content',
      'field_bgimage_date' => 'ds_content',
      'field_bgimage_size' => 'ds_content',
      'body' => 'ds_content',
      'bgimage_related' => 'ds_content',
      'submitted_by' => 'ds_content',
      'comments' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|bgimage|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|homepage';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'homepage';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_bgimage_image',
        1 => 'bgimage_field_placed_by',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'ds_content',
      'bgimage_field_placed_by' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|bgimage|homepage'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|recent';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'recent';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'bgimage_field_taxonomy_path',
      ),
      'left' => array(
        1 => 'field_bgimage_image',
      ),
      'right' => array(
        2 => 'title',
        3 => 'field_bgimage_location',
        4 => 'field_bgimage_date',
        5 => 'field_bgimage_size',
      ),
      'footer' => array(
        6 => 'submitted_by',
      ),
    ),
    'fields' => array(
      'bgimage_field_taxonomy_path' => 'header',
      'field_bgimage_image' => 'left',
      'title' => 'right',
      'field_bgimage_location' => 'right',
      'field_bgimage_date' => 'right',
      'field_bgimage_size' => 'right',
      'submitted_by' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|bgimage|recent'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgimage|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgimage';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_bgimage_image',
      ),
    ),
    'fields' => array(
      'field_bgimage_image' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
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
