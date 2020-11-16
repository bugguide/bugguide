<?php

/**
 * @file
 * bgforum.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bgforum_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|forum|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'forum';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'comments' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgpage_citations' => array(
      'weight' => '1',
      'label' => 'above',
      'format' => 'default',
    ),
  );
  $export['node|forum|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bgforum_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|forum|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'forum';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'body',
        1 => 'bgpage_citations',
        2 => 'taxonomy_forums',
        3 => 'subscriptions_ui',
        4 => 'comments',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
      'bgpage_citations' => 'ds_content',
      'taxonomy_forums' => 'ds_content',
      'subscriptions_ui' => 'ds_content',
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
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|forum|default'] = $ds_layout;

  return $export;
}
