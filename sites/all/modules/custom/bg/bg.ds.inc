<?php

/**
 * @file
 * bg.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function bg_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'bgsubscription';
  $ds_field->label = 'BGSubscription';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'bgsubscriptions|bgsubscriptions_block',
    'block_render' => '1',
    'block_visibility' => 0,
  );
  $export['bgsubscription'] = $ds_field;

  return $export;
}
