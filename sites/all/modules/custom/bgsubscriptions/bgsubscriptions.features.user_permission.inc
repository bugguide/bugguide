<?php
/**
 * @file
 * bgsubscriptions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bgsubscriptions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'subscribe to content'.
  $permissions['subscribe to content'] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'subscriptions',
  );

  return $permissions;
}
