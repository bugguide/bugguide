<?php

/**
 * @file
 * bgimage.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function bgimage_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-featured_image-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'featured_image-block',
    'module' => 'views',
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
        'region' => 'featured',
        'status' => 1,
        'theme' => 'bulmabug',
        'weight' => 0,
      ),
      'shiny' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shiny',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-recent_images-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'recent_images-block',
    'module' => 'views',
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
        'weight' => 0,
      ),
      'shiny' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shiny',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  return $export;
}
