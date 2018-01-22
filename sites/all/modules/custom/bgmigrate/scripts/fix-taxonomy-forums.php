<?php

/**
 * Script to fix migration data for forum topics taxonomy field.
 *
 * Copies data and revisions from taxonomyextra to taxonomy_forums.
 *
 * @see bugguide_migration's migrateto7.
 */

// Load helper functions from field.install.
module_load_include('install', 'field', 'field');

// 1. Create field instance for the forum content type.
$field_name = 'taxonomy_forums';
$field = array(
  'id' => 1,
  'field_name' => $field_name,
  'module' => 'taxonomy',
  'type' => 'taxonomy_term_reference',
  'cardinality' => 1,
  'settings' => array(
    'required' => FALSE,
    'allowed_values' => array(
      array(
        'vocabulary' => 'forums',
        'parent' => 0,
      ),
    ),
  ),
);
$bundle = 'forum';
$instance = array(
  'field_id' => 1,
  'label' => 'Forum topic',
  'field_name' => $field_name,
  'bundle' => $bundle,
  'entity_type' => 'node',
  'settings' => array(),
  'description' => '',
  'required' => FALSE,
  'widget' => array(
    'type' => 'select',
    'module' => 'options',
    'settings' => array(),
  ),
  'display' => array(
    'default' => array(
      'type' => 'taxonomy_term_reference_link',
      'weight' => 10,
    ),
    'teaser' => array(
      'type' => 'taxonomy_term_reference_link',
      'weight' => 10,
    ),
  ),
);

_update_7000_field_create_instance($field, $instance);

// 2. Copy data from field_taxonomyextras into field_taxonomy_forums.
db_query('INSERT into {field_data_taxonomy_forums} (
    entity_type,
    bundle,
    deleted,
    entity_id,
    revision_id,
    language,
    delta,
    taxonomy_forums_tid
  )
  select entity_type,
    bundle,
    deleted,
    entity_id,
    revision_id,
    language,
    delta,
    taxonomyextra_tid from {field_data_taxonomyextra}
');

// 3. Copy data from field_revision_taxonomyextras into field_revision_taxonomy_forums.
db_query('INSERT into {field_revision_taxonomy_forums} (
    entity_type,
    bundle,
    deleted,
    entity_id,
    revision_id,
    language,
    delta,
    taxonomy_forums_tid
  )
  select entity_type,
    bundle,
    deleted,
    entity_id,
    revision_id,
    language,
    delta,
    taxonomyextra_tid from {field_revision_taxonomyextra}
');

// 4. Delete field taxonomyextra.
field_delete_field('taxonomyextra');
field_purge_batch(15000);
