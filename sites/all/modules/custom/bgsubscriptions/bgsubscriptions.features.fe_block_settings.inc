<?php
/**
 * @file
 * bgsubscriptions.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function bgsubscriptions_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['subscriptions_ui-0'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 0,
    'module' => 'subscriptions_ui',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bulma' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bulma',
        'weight' => 0,
      ),
      'bulmabug' => array(
        'region' => '',
        'status' => 0,
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
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
