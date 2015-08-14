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
    'title' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'changed_date' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
    'submitted_by' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
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
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgimage|default'] = $ds_fieldsetting;

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
        3 => 'title',
        4 => 'field_bgimage_location',
        5 => 'field_bgimage_date',
        6 => 'field_bgimage_size',
        7 => 'body',
        8 => 'bgimage_related',
        9 => 'submitted_by',
        10 => 'changed_date',
        11 => 'comments',
      ),
    ),
    'fields' => array(
      'bgimage_photo_number' => 'ds_content',
      'field_bgimage_image' => 'ds_content',
      'bgimage_copyright' => 'ds_content',
      'title' => 'ds_content',
      'field_bgimage_location' => 'ds_content',
      'field_bgimage_date' => 'ds_content',
      'field_bgimage_size' => 'ds_content',
      'body' => 'ds_content',
      'bgimage_related' => 'ds_content',
      'submitted_by' => 'ds_content',
      'changed_date' => 'ds_content',
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
