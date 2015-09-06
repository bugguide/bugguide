<?php
/**
 * @file
 * bg.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function bg_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'solr';
  $environment->name = 'localhost server';
  $environment->url = 'http://localhost:8983/solr';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_direct_commit' => 0,
    'apachesolr_read_only' => '0',
    'apachesolr_soft_commit' => 0,
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'bgimage',
      1 => 'bgpage',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
