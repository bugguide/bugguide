<?php
/**
 * @file
 * bgimage.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bgimage_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'clone own nodes'.
  $permissions['clone own nodes'] = array(
    'name' => 'clone own nodes',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'clone',
  );

  return $permissions;
}
