<?php
/**
 * @file
 * bgpage.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bgpage_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view raw parents'.
  $permissions['view raw parents'] = array(
    'name' => 'view raw parents',
    'roles' => array(),
    'module' => 'bgpage',
  );

  // Exported permission: 'view taxon ID field'.
  $permissions['view taxon ID field'] = array(
    'name' => 'view taxon ID field',
    'roles' => array(),
    'module' => 'bgpage',
  );

  // Exported permission: 'view who edited bgpage'.
  $permissions['view who edited bgpage'] = array(
    'name' => 'view who edited bgpage',
    'roles' => array(),
    'module' => 'bgpage',
  );

  return $permissions;
}
