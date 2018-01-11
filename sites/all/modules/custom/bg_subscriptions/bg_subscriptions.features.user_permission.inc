<?php
/**
 * @file
 * bg_subscriptions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bg_subscriptions_user_default_permissions() {
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
