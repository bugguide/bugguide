<?php

/**
 * @file
 * bgimage.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bgimage_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_bgimage';
  $strongarm->value = 0;
  $export['comment_anonymous_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_bgimage';
  $strongarm->value = '2';
  $export['comment_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_bgimage';
  $strongarm->value = 1;
  $export['comment_default_mode_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_bgimage';
  $strongarm->value = '50';
  $export['comment_default_per_page_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_bgimage';
  $strongarm->value = 1;
  $export['comment_form_location_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_bgimage';
  $strongarm->value = '1';
  $export['comment_preview_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_bgimage';
  $strongarm->value = 1;
  $export['comment_subject_field_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__bgimage';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'homepage' => array(
        'custom_settings' => TRUE,
      ),
      'browse' => array(
        'custom_settings' => FALSE,
      ),
      'images' => array(
        'custom_settings' => FALSE,
      ),
      'recent' => array(
        'custom_settings' => TRUE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'subscriptions' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(
        'subscriptions_ui' => array(
          'default' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
          'homepage' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
          'recent' => array(
            'weight' => '40',
            'visible' => FALSE,
          ),
          'teaser' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fivestar_tags';
  $strongarm->value = 'r,p';
  $export['fivestar_tags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_bgimage';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_bgimage';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bgimage';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_bgimage';
  $strongarm->value = '1';
  $export['node_preview_bgimage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_bgimage';
  $strongarm->value = 1;
  $export['node_submitted_bgimage'] = $strongarm;

  return $export;
}
