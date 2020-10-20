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

  // Exported permission: 'create bgimages'.
  $permissions['create bgimages'] = array(
    'name' => 'create bgimages',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributing editor' => 'contributing editor',
      'expert' => 'expert',
      'spam zapper' => 'spam zapper',
    ),
    'module' => 'bgimage',
  );

  // Exported permission: 'edit any bgimage content'.
  $permissions['edit any bgimage content'] = array(
    'name' => 'edit any bgimage content',
    'roles' => array(
      'contributing editor' => 'contributing editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'link all bgimages'.
  $permissions['link all bgimages'] = array(
    'name' => 'link all bgimages',
    'roles' => array(
      'administrator' => 'administrator',
      'contributing editor' => 'contributing editor',
      'spam zapper' => 'spam zapper',
    ),
    'module' => 'bgimage',
  );

  // Exported permission: 'move all bgimages'.
  $permissions['move all bgimages'] = array(
    'name' => 'move all bgimages',
    'roles' => array(
      'administrator' => 'administrator',
      'contributing editor' => 'contributing editor',
      'spam zapper' => 'spam zapper',
    ),
    'module' => 'bgimage',
  );

  // Exported permission: 'use editablefields'.
  $permissions['use editablefields'] = array(
    'name' => 'use editablefields',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'editablefields',
  );

  // Exported permission: 'use image clipboard'.
  $permissions['use image clipboard'] = array(
    'name' => 'use image clipboard',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'bgimage',
  );

  // Exported permission: 'view fullsize bgimages'.
  $permissions['view fullsize bgimages'] = array(
    'name' => 'view fullsize bgimages',
    'roles' => array(
      'administrator' => 'administrator',
      'contributing editor' => 'contributing editor',
      'expert' => 'expert',
      'spam zapper' => 'spam zapper',
    ),
    'module' => 'bgimage',
  );

  return $permissions;
}
