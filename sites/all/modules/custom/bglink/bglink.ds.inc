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
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'links' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '5',
      'label' => 'above',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'author_linked',
    ),
    'post_date' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'ds_post_date_bg_short_F_j_Y',
    ),
    'changed_date' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
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
        1 => 'links',
        2 => 'title',
        3 => 'field_bglink_link',
        4 => 'author',
        5 => 'post_date',
        6 => 'changed_date',
        7 => 'field_tags',
        8 => 'comments',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
      'links' => 'ds_content',
      'title' => 'ds_content',
      'field_bglink_link' => 'ds_content',
      'author' => 'ds_content',
      'post_date' => 'ds_content',
      'changed_date' => 'ds_content',
      'field_tags' => 'ds_content',
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
  $export['node|bglink|default'] = $ds_layout;

  return $export;
}
