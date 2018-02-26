<?php
/**
 * @file
 * bgsubscriptions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgsubscriptions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
