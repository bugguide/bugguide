<?php
/**
 * @file
 * bg.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bg_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr" && $api == "apachesolr_environments") {
    return array("version" => "1");
  }
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function bg_image_default_styles() {
  $styles = array();

  // Exported image style: bg_large.
  $styles['bg_large'] = array(
    'label' => 'BG large',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1024,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: bg_small.
  $styles['bg_small'] = array(
    'label' => 'BG small',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 125,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
