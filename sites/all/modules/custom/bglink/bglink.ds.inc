<?php

/**
 * @file
 * bglink.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bglink_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bglink|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bglink';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'bgsubscription' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgpage_citations' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bglink|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bglink_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bglink|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bglink';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'body',
        1 => 'field_parent',
        2 => 'field_bglink_link',
        3 => 'field_tags',
        4 => 'bgpage_citations',
        5 => 'bgsubscription',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
      'field_parent' => 'ds_content',
      'field_bglink_link' => 'ds_content',
      'field_tags' => 'ds_content',
      'bgpage_citations' => 'ds_content',
      'bgsubscription' => 'ds_content',
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
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|bglink|default'] = $ds_layout;

  return $export;
}
