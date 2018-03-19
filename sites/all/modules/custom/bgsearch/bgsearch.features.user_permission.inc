<?php
/**
 * @file
 * bgsearch.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bgsearch_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access bugguide_search search_api_page'.
  $permissions['access bugguide_search search_api_page'] = array(
    'name' => 'access bugguide_search search_api_page',
    'roles' => array(
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'search_api_page',
  );

  return $permissions;
}
