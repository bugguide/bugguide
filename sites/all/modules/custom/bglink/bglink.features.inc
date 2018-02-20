<?php
/**
 * @file
 * bglink.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bglink_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function bglink_node_info() {
  $items = array(
    'bglink' => array(
      'name' => t('Link'),
      'base' => 'node_content',
      'description' => t('A BugGuide link.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
