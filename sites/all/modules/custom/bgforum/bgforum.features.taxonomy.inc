<?php

/**
 * @file
 * bgforum.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function bgforum_taxonomy_default_vocabularies() {
  return array(
    'forums' => array(
      'name' => 'Forums',
      'machine_name' => 'forums',
      'description' => 'Forums',
      'hierarchy' => 1,
      'module' => 'forum',
      'weight' => 0,
    ),
  );
}
