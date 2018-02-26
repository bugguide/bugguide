<?php

/**
 * @file
 * Postmigration script for Bugguide. Runs on Drupal 7.
 *
 * The purpose of this script is to ensure that each bgimage has a unique
 * hash in the bgimage table (base column) and in field_data_field_bgimage_base.
 */


define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/file.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';
require_once DRUPAL_ROOT . '/sites/all/modules/custom/bgimage/bgimage.module';

if (!drupal_is_cli()) {
  echo "This code is restricted to the command line.";
  exit();
}

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// Walk through bgimage table.
$result = db_query("SELECT nid, base FROM bgimage ORDER BY nid LIMIT 2");
foreach ($result as $record) {
  // Generate a guaranteed-unique uuid.
  $uuid = bgimage_generate_uuid();
  
  // 1. Old filepath
  $old_filepath = image_obfuscate($result->base . $result->nid) . '.jpg';
  
  // 2. New filepath
  $obfuscate = image_obfuscate($uuid);
  
  // 3. If we have not already done so, move the file.
  $obfuscate = image_obfuscate($node->bgimage_uuid);
  $prefix = bgimage_get_prefix($obfuscate);
  $directory = 'public://raw/' . $prefix;
  // Ensure directory
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('image', 'Failed to create style directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }

  $uri = $directory . $obfuscate . '.jpg';
  if (!file_exists($uri)) {
    $fid = db_query("SELECT fid FROM {file_usage} WHERE id = :nid", array(':nid' => $result->nid))->fetchField();
    $file = file_load($fid);
    // Move file into new path, e.g.
    // files/raw/7H3/HEH/7H3HEHUZ6H3HMLUZ8LWZUHLRUHVZMLZR5LAZ8LUZ6HBH0L6Z4H6ZLLOHIHBHQL5Z8H.jpg
    // 4. Update the uri in file_managed
    file_move($file, $directory . $obfuscate . '.jpg'); 
    // but file_move() does not update the filename so we have to do that
    db_query("UPDATE {file_managed} SET filename = :filename WHERE fid = :fid", array(':filename' => $obfuscate . '.jpg', ':fid' => $fid));
  }
  
  // 5. Update the hash in bgimage
  db_query("UPDATE {bgimage} SET base = :uuid WHERE nid = :nid", array(':uuid' => $uuid, ':nid' => $result->nid));
  
  // 6. Update the hash in field_data_bgimage_base
  db_query("UPDATE {field_data_field_bgimage_base} SET field_bgimage_base_value = :uuid WHERE entity_id = :nid", array(':uuid' => $uuid, ':nid' => $result->nid));
  
  // 7. Update the has in field_revisions_bgimage_base
  db_query("UPDATE {field_revision_field_bgimage_base} SET field_bgimage_base_value = :uuid WHERE entity_id = :nid", array(':uuid' => $uuid, ':nid' => $result->nid));
  
  echo "$result->nid $result->base -> $uuid";
  echo "old: $old_filepath";
  echo "new: $directory $obfuscate .jpg";
}