<?php

/**
 * @file
 * bgusers.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function bgusers_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 0,
  );

  // Exported role: contributing editor.
  $roles['contributing editor'] = array(
    'name' => 'contributing editor',
    'weight' => 0,
  );

  // Exported role: expert.
  $roles['expert'] = array(
    'name' => 'expert',
    'weight' => 0,
  );

  // Exported role: spam zapper.
  $roles['spam zapper'] = array(
    'name' => 'spam zapper',
    'weight' => 0,
  );

  return $roles;
}
