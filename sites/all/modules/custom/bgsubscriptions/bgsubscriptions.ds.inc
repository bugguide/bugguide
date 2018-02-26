<?php
/**
 * @file
 * bgsubscriptions.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function bgsubscriptions_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'subscriptions';
  $ds_field->label = 'Subscriptions';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'subscriptions_ui|0',
    'block_render' => '1',
  );
  $export['subscriptions'] = $ds_field;

  return $export;
}
