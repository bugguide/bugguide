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

  // Exported permission: 'create bgpage content'.
  $permissions['create bgpage content'] = array(
    'name' => 'create bgpage content',
    'roles' => array(
      'contributing editor' => 'contributing editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any bgpage content'.
  $permissions['delete any bgpage content'] = array(
    'name' => 'delete any bgpage content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own bgpage content'.
  $permissions['delete own bgpage content'] = array(
    'name' => 'delete own bgpage content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any bgpage content'.
  $permissions['edit any bgpage content'] = array(
    'name' => 'edit any bgpage content',
    'roles' => array(
      'contributing editor' => 'contributing editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own bgpage content'.
  $permissions['edit own bgpage content'] = array(
    'name' => 'edit own bgpage content',
    'roles' => array(
      'contributing editor' => 'contributing editor',
    ),
    'module' => 'node',
  );

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
