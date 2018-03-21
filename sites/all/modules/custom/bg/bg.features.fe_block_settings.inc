<?php
/**
 * @file
 * bg.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function bg_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['bgimage-tagged_images'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'tagged_images',
    'module' => 'bgimage',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'ladybug',
        'weight' => -13,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
      'suitcase_interim' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'suitcase_interim',
        'weight' => -13,
      ),
      'bulmabug' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'bulmabug',
        'weight' => -13,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['bg-bg_visual_guide'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'bg_visual_guide',
    'module' => 'bg',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'bulma' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bulma',
        'weight' => 0,
      ),
      'bulmabug' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bulmabug',
        'weight' => -16,
      ),
      'shiny' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shiny',
        'weight' => 0,
      ),
    ),
    'title' => 'Visual Guide',
    'visibility' => 1,
  );

  return $export;
}
