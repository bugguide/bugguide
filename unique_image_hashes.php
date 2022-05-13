<?php

/**
 * @file
 * Postmigration script for Bugguide. Runs on Drupal 7.
 *
 * The purpose of this script is to ensure that each bgimage has a unique
 * hash in the bgimage table (base column) and in field_data_field_bgimage_base.
 */


// Run with drush php-script unique_image_hashes.php
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/file.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';
require_once DRUPAL_ROOT . '/sites/all/modules/custom/bgimage/bgimage.module';

if (!drupal_is_cli()) {
  echo "This code is restricted to the command line.";
  exit();
}

function hashlog($s) {
    echo $s . "\n";
    echo "";
}

function writequery($query) {
  $file = '/var/bugguide/queries.txt';
  // Write the contents to the file, 
  // using the FILE_APPEND flag to append the content to the end of the file
  // and the LOCK_EX flag to prevent anyone else writing to the file at the same time
  file_put_contents($file, $query . ';' . PHP_EOL, FILE_APPEND | LOCK_EX);
}

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
writequery("--beginning");
//hashlog("booted up");
// Walk through bgimage table.
$result = db_query("SELECT nid, base, newbase FROM bgimage WHERE newbase IS NOT NULL ORDER BY nid");
foreach ($result as $record) {
  //print_r($record);
  $uuid = $record->newbase;
  
  // 1. Old filepath
  $old_filepath = image_obfuscate($record->base . $record->nid) . '.jpg';
  //hashlog("old_filepath: $old_filepath");


  // 2. New filepath
  $obfuscate = image_obfuscate($uuid . $record->nid);
  //hashlog("new_filepath: $obfuscate");
  
  // 3. If we have not already done so, copy the file.
  $prefix = bgimage_get_prefix($obfuscate);
  $directory = 'public://raw/' . $prefix;
  //hashlog ("new directory: $directory");
  // Ensure directory
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('image', 'Failed to create style directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    //hashlog( "aaaugh, could not create style directory $directory");
    return FALSE;
  }

  $uri = $directory . $obfuscate . '.jpg';
  //hashlog( "uri: $uri");
  // File will exist if a previous migration already converted this file.
  $fid = db_query("SELECT fid FROM {file_usage} WHERE id = :nid", array(':nid' => $record->nid))->fetchField();
  $file = file_load($fid);
  //hashlog("Loaded file:");
  //print_r($file);
  // Save original uri; there is a file there.
  $raw_file_uri = $file->uri;
  if (!file_exists($uri)) {
    // Copy file into new path, e.g.,
    // files/raw/7H3/HEH/7H3HEHUZ6H3HMLUZ8LWZUHLRUHVZMLZR5LAZ8LUZ6HBH0L6Z4H6ZLLOHIHBHQL5Z8H.jpg
    
    // TODO: file_copy() is munging around with database entries, maybe we want to bypass. Yes.
    // If FILE_EXISTS_ERROR then it will create a new file entry?
    //file_copy($file, $directory . $obfuscate . '.jpg', FILE_EXISTS_ERROR); 
    file_unmanaged_copy($file->uri, $directory . $obfuscate . '.jpg', FILE_EXISTS_ERROR); 
    $file_existed = 0;
  }
  else {
    //hashlog("file already exists");
    $file_existed = 1;
  }
  // 4. Update the uri in file_managed
  // but file_copy() does not update the filename so we have to do that
  db_query("UPDATE {file_managed} SET filename = :filename, uri = :uri WHERE fid = :fid", array(':filename' => $obfuscate . '.jpg', ':uri' => $uri, ':fid' => $fid));
  writequery("UPDATE file_managed SET filename = '$obfuscate', uri = '$uri' WHERE fid = $fid");
  
  // TODO delete $raw_file_url which is the original image path.
  // Deferring this.
  
  // 5. Update the hash in bgimage
  db_query("UPDATE {bgimage} SET base = :uuid WHERE nid = :nid", array(':uuid' => $uuid, ':nid' => $record->nid));
  writequery("UPDATE bgimage SET base = '$uuid' WHERE nid = $record->nid");
  
  // 6. Update the hash in field_data_bgimage_base
  db_query("UPDATE {field_data_field_bgimage_base} SET field_bgimage_base_value = :uuid WHERE entity_id = :nid", array(':uuid' => $uuid, ':nid' => $record->nid));
  writequery("UPDATE field_data_field_bgimage_base SET field_bgimage_base_value = '$uuid' WHERE entity_id = $record->nid");
  
  // 7. Update the hash in field_revisions_bgimage_base
  db_query("UPDATE {field_revision_field_bgimage_base} SET field_bgimage_base_value = :uuid WHERE entity_id = :nid", array(':uuid' => $uuid, ':nid' => $record->nid));
  writequery("UPDATE field_revision_field_bgimage_base SET field_bgimage_base_value = '$uuid' WHERE entity_id = $record->nid");
  
  hashlog("$file_existed $record->nid $record->base $uuid $old_filepath $obfuscate.jpg");
  
  continue;
  hashlog("$record->nid $record->base -> $uuid");
  hashlog("old: $old_filepath");
  hashlog("new: $directory$obfuscate.jpg");
  hashlog("");
  hashlog("Doing a check. Loading nid $record->nid");
  // Clear node cache by calling with reset TRUE.
  // But we will get old base from cache_field. Zap it out.
  cache_clear_all('field:node:' . $record->nid, 'cache_field');
  $node = node_load($record->nid, NULL, TRUE);
  hashlog("Base should be: $uuid");
  hashlog("Base is: " . $node->{'field_bgimage_base'}[LANGUAGE_NONE][0]['value']);
  hashlog("Checking entry in files_managed:");
  $fidcheck = db_query("SELECT fid FROM {file_usage} WHERE id = :nid", array(':nid' => $record->nid))->fetchField();
  hashlog("fid is $fidcheck in files_usage associated with nid $record->nid");
  hashlog ("Checking entry in files_managed");
  $filecheck = db_query("SELECT filename FROM {file_managed} WHERE fid = :fid", array(':fid' => $fidcheck))->fetchField();
  hashlog("filename is $filecheck");
  $fileloadcheck = file_load($fidcheck);
  print_r($fileloadcheck);
  hashlog("-------");
  hashlog("");
}
