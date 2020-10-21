<?php

/**
 * @file
 * bg.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bg_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use editablefields'.
  $permissions['use editablefields'] = array(
    'name' => 'use editablefields',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'editablefields',
  );

  return $permissions;
}
