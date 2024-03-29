<?php

/**
 * @file
 * bgref.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bgref_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|book_reference|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'book_reference';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'comments' => array(
      'weight' => '9',
      'label' => 'above',
      'format' => 'default',
    ),
    'changed_date' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
    'submitted_by' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
    'bgpage_citations' => array(
      'weight' => '5',
      'label' => 'above',
      'format' => 'default',
    ),
  );
  $export['node|book_reference|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bgref_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|book_reference|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'book_reference';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_book_reference_author',
        1 => 'field_book_reference_publisher',
        2 => 'field_book_reference_year',
        3 => 'field_book_reference_isbn',
        4 => 'body',
        5 => 'bgpage_citations',
        6 => 'submitted_by',
        7 => 'field_tags',
        8 => 'changed_date',
        9 => 'comments',
      ),
    ),
    'fields' => array(
      'field_book_reference_author' => 'ds_content',
      'field_book_reference_publisher' => 'ds_content',
      'field_book_reference_year' => 'ds_content',
      'field_book_reference_isbn' => 'ds_content',
      'body' => 'ds_content',
      'bgpage_citations' => 'ds_content',
      'submitted_by' => 'ds_content',
      'field_tags' => 'ds_content',
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
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|book_reference|default'] = $ds_layout;

  return $export;
}
