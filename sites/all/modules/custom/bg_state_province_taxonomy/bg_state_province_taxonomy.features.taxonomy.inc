<?php
/**
 * @file
 * bg_state_province_taxonomy.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function bg_state_province_taxonomy_taxonomy_default_vocabularies() {
  return array(
    'state_province' => array(
      'name' => 'State/Province',
      'machine_name' => 'state_province',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
