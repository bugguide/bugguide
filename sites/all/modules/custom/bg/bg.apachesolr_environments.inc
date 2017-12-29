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
  $environment->name = 'db1 solr server';
  $environment->url = 'http://db1.ent.iastate.edu:8983/solr/bugguide';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_direct_commit' => 0,
    'apachesolr_read_only' => '0',
    'apachesolr_search_facet_pages' => '',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'bgimage',
      1 => 'bgpage',
      2 => 'forum',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
