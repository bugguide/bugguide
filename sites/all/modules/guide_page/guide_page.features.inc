<?php
/**
 * @file
 * guide_page.features.inc
 */

/**
 * Implements hook_node_info().
 */
function guide_page_node_info() {
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
