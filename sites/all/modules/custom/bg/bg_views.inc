<?php

/**
 * Implements hook_views_data().
 */
function bg_views_data_alter(&$data) {
  // Make Drupal Views aware of our custom handler.
  $data['field_data_field_parent']['field_parent_value']['filter']['handler'] = 'views_handler_filter_parent';
}