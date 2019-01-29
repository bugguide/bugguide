<?php

/**
 * @file
 * bgimage.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgimage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function bgimage_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function bgimage_node_info() {
  $items = array(
    'bgimage' => array(
      'name' => t('Image'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('We welcome your image, but first please be sure you are submitting to the most appropriate section of the guide. If more specific guide pages are needed, include the classification details in the remarks. Be sure to note how you arrived at the identification. We will create guide pages as needed and move the image.

There are no specific rules for image quality. Sharp, properly exposed, color balanced, and well composed images are preferred, but a photo lacking in those areas may be better than no photo at all. Feel free to submit your image, but please do not be upset if we remove it.

Your image must be in jpeg format. You may submit an image of any size, but 560 pixels on the longest side is preferred. Anything bigger than that will be automatically resized. For consistency, please do not include any borders or other decorations around your image. A copyright notice in the image is reasonable, but note that your copyright will automatically appear below the image. Please do not include any other text or markup in the image. We reserve the right to crop the image to emphasize the bug.'),
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
