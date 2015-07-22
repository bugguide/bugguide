<?php
/**
 * @file
 * bgref.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgref_ctools_plugin_api($module = NULL, $api = NULL) {
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
function bgref_node_info() {
  $items = array(
    'book_reference' => array(
      'name' => t('Book Reference'),
      'base' => 'node_content',
      'description' => t('Defines a book reference'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
