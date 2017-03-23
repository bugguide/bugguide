<?php
/**
 * @file
 * bgsearch.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgsearch_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}
