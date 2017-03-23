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
      'suitcase_interim' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'suitcase_interim',
        'weight' => -13,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
