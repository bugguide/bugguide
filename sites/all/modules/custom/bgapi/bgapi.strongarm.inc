<?php
/**
 * @file
 * bgapi.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bgapi_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'restful_default_output_formatter';
  $strongarm->value = 'json_api';
  $export['restful_default_output_formatter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'restful_enable_users_resource';
  $strongarm->value = 0;
  $export['restful_enable_users_resource'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'restful_token_auth_expiration_period';
  $strongarm->value = 'P3650D';
  $export['restful_token_auth_expiration_period'] = $strongarm;

  return $export;
}
