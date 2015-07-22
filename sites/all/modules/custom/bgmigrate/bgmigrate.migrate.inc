<?php

/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/*
 * You must implement hook_migrate_api(), setting the API level to 2, if you are
 * implementing any migration classes. As of Migrate 2.5, you should also
 * register your migration and handler classes explicitly here - the former
 * method of letting them get automatically registered on a cache clear will
 * break in certain environments (see http://drupal.org/node/1778952).
 */
function bgmigrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'bugguide' => array(
        'title' => t('BugGuide Migration'),
      ),
    ),
    'migrations' => array(
      'bgpagefields' => array(
        'class_name' => 'BGPageFieldMigration',
        'group_name' => 'bugguide',
      ),
      'bgreffields' => array(
        'class_name' => 'BGRefFieldMigration',
        'group_name' => 'bugguide',
      ),
    ),
  );
  return $api;
}
