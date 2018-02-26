<?php
/**
 * @file
 * bgsubscriptions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bgsubscriptions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'subscriptions_form_in_block';
  $strongarm->value = '1';
  $export['subscriptions_form_in_block'] = $strongarm;

  return $export;
}
