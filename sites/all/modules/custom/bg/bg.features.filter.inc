<?php
/**
 * @file
 * bg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function bg_filter_default_formats() {
  $formats = array();

  // Exported format: BBCode.
  $formats['xbbcode'] = array(
    'format' => 'xbbcode',
    'name' => 'BBCode',
    'cache' => 1,
    'status' => 1,
    'weight' => -6,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'xbbcode' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'autoclose' => FALSE,
          'override' => FALSE,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
