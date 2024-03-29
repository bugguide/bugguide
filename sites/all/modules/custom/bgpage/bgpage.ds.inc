<?php

/**
 * @file
 * bgpage.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bgpage_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgpage|browse';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgpage';
  $ds_fieldsetting->view_mode = 'browse';
  $ds_fieldsetting->settings = array(
    'bgpage_browse' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgpage|browse'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgpage|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgpage';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'bgsubscriptions_subscriptions' => array(
      'weight' => '20',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bgpage_classification' => array(
      'weight' => '1',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'bgpage_citations' => array(
      'weight' => '19',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'bgpage_representative_images' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgpage|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|bgpage|images';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'bgpage';
  $ds_fieldsetting->view_mode = 'images';
  $ds_fieldsetting->settings = array(
    'bgpage_images' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|bgpage|images'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|page|homepage';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'page';
  $ds_fieldsetting->view_mode = 'homepage';
  $ds_fieldsetting->settings = array(
    'recent_images' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|page|homepage'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bgpage_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgpage|browse';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgpage';
  $ds_layout->view_mode = 'browse';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'bgpage_browse',
      ),
    ),
    'fields' => array(
      'bgpage_browse' => 'ds_content',
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
  $export['node|bgpage|browse'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgpage|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgpage';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'bgpage_representative_images',
        1 => 'bgpage_classification',
        2 => 'field_hodges_number',
        3 => 'field_other_common_names',
        4 => 'field_synonyms',
        5 => 'field_etymology',
        6 => 'field_counts',
        7 => 'field_size',
        8 => 'field_id',
        9 => 'field_range',
        10 => 'field_habitat',
        11 => 'field_season',
        12 => 'field_food',
        13 => 'field_life_cycle',
        14 => 'field_remarks',
        15 => 'field_see_also',
        16 => 'field_print_references',
        17 => 'field_internet_references',
        18 => 'field_tags',
        19 => 'bgpage_citations',
        20 => 'bgsubscriptions_subscriptions',
      ),
    ),
    'fields' => array(
      'bgpage_representative_images' => 'ds_content',
      'bgpage_classification' => 'ds_content',
      'field_hodges_number' => 'ds_content',
      'field_other_common_names' => 'ds_content',
      'field_synonyms' => 'ds_content',
      'field_etymology' => 'ds_content',
      'field_counts' => 'ds_content',
      'field_size' => 'ds_content',
      'field_id' => 'ds_content',
      'field_range' => 'ds_content',
      'field_habitat' => 'ds_content',
      'field_season' => 'ds_content',
      'field_food' => 'ds_content',
      'field_life_cycle' => 'ds_content',
      'field_remarks' => 'ds_content',
      'field_see_also' => 'ds_content',
      'field_print_references' => 'ds_content',
      'field_internet_references' => 'ds_content',
      'field_tags' => 'ds_content',
      'bgpage_citations' => 'ds_content',
      'bgsubscriptions_subscriptions' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'class="content"',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'hide_page_title' => '0',
    'page_option_title' => '',
  );
  $export['node|bgpage|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|bgpage|images';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'bgpage';
  $ds_layout->view_mode = 'images';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'bgpage_images',
      ),
    ),
    'fields' => array(
      'bgpage_images' => 'ds_content',
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
  $export['node|bgpage|images'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|page|homepage';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'page';
  $ds_layout->view_mode = 'homepage';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
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
    'hide_page_title' => '1',
    'page_option_title' => '',
  );
  $export['node|page|homepage'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function bgpage_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'browse';
  $ds_view_mode->label = 'Browse';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['browse'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'images';
  $ds_view_mode->label = 'images';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['images'] = $ds_view_mode;

  return $export;
}
