<?php
/**
 * @file
 * bguserfields.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function bguserfields_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|default';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_user_full_name',
        1 => 'field_email',
        2 => 'field_user_default_county',
        3 => 'field_user_biography',
        4 => 'field_user_content_license',
        5 => 'field_user_content_license_add',
      ),
    ),
    'fields' => array(
      'field_user_full_name' => 'ds_content',
      'field_email' => 'ds_content',
      'field_user_default_county' => 'ds_content',
      'field_user_biography' => 'ds_content',
      'field_user_content_license' => 'ds_content',
      'field_user_content_license_add' => 'ds_content',
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
  $export['user|user|default'] = $ds_layout;

  return $export;
}
