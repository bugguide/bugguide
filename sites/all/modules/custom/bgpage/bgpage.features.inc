<?php
/**
 * @file
 * bgpage.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgpage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function bgpage_node_info() {
  $items = array(
    'bgpage' => array(
      'name' => t('Guide Page'),
      'base' => 'node_content',
      'description' => t('Guide page describing a taxonomic group.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
