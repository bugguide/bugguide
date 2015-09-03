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

  $export['bg-bg_guide'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'bg_guide',
    'module' => 'bg',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'ladybug',
        'weight' => -12,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['bgimage-tagged_images'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'tagged_images',
    'module' => 'bgimage',
    'node_types' => array(),
    'pages' => '',
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
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
