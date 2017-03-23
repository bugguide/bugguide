<?php
/**
 * @file
 * bgsearch.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function bgsearch_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['apachesolr_search-sort'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'sort',
    'module' => 'apachesolr_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ladybug',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
      'suitcase_interim' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'suitcase_interim',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ladybug',
        'weight' => 0,
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
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-Za8lWIXN16R0Cq79viEEG9l05qvmOSND'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'Za8lWIXN16R0Cq79viEEG9l05qvmOSND',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ladybug',
        'weight' => 0,
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
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-efolWGlFiunUWqnQd2V3My7YlY1bcnu7'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'efolWGlFiunUWqnQd2V3My7YlY1bcnu7',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ladybug' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ladybug',
        'weight' => 0,
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
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
