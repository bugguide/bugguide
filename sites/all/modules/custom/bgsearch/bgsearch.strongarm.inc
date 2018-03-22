<?php
/**
 * @file
 * bgsearch.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bgsearch_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facetapi:block_cache:search_api@bugguide';
  $strongarm->value = -1;
  $export['facetapi:block_cache:search_api@bugguide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'user' => 'user',
    'apachesolr_search' => 0,
    'node' => 0,
  );
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'user';
  $export['search_default_module'] = $strongarm;

  return $export;
}
