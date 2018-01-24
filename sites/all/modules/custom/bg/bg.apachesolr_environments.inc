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
    'apachesolr_search_changed_boost' => '0:0',
    'apachesolr_search_comment_boost' => '0:0',
    'apachesolr_search_date_boost' => '0:0',
    'apachesolr_search_facet_pages' => '',
    'apachesolr_search_promote_boost' => '0',
    'apachesolr_search_sticky_boost' => '0',
    'apachesolr_search_type_boosts' => array(
      'bgref' => '0',
      'book_reference' => '0',
      'forum' => '0',
      'bgpage' => '0',
      'bgimage' => '0',
      'bglink' => '0',
      'page' => '0',
    ),
    'apachesolr_soft_commit' => 0,
    'field_bias' => array(
      'bs_promote' => '0',
      'bs_status' => '0',
      'bs_sticky' => '0',
      'bs_translate' => '0',
      'bundle' => '0',
      'bundle_name' => '0',
      'content' => '1.0',
      'dm_field_bgimage_date' => '0',
      'ds_changed' => '0',
      'ds_created' => '0',
      'ds_last_comment_or_change' => '0',
      'ds_last_comment_timestamp' => '0',
      'entity_id' => '0',
      'entity_type' => '0',
      'hash' => '0',
      'id' => '0',
      'is_bgimage_immediate_parent' => '0',
      'is_bgimage_rating_avg' => '0',
      'is_bgimage_rating_count' => '0',
      'is_comment_count' => '0',
      'is_tnid' => '0',
      'is_uid' => '0',
      'label' => '5.0',
      'path' => '0',
      'site' => '0',
      'sm_bgimage_breadcrumbs' => '0',
      'sm_bgimage_parents' => '0',
      'sm_field_bgimage_base' => '0',
      'sm_field_bgimage_county' => '0',
      'sm_field_bgimage_id' => '0',
      'sm_field_bgimage_life_stage' => '0',
      'sm_field_bgimage_location' => '0',
      'sm_field_bgimage_location_code' => '0',
      'sm_field_parent' => '0',
      'sort_bgimage_classification' => '0',
      'sort_bgimage_immediate_parent_title' => '0',
      'sort_bgimage_thumbnail' => '0',
      'sort_label' => '0',
      'sort_language' => '0',
      'sort_name' => '0',
      'sort_name_formatted' => '0',
      'spell' => '0',
      'ss_bgimage_classification' => '0',
      'ss_bgimage_immediate_parent_title' => '0',
      'ss_bgimage_thumbnail' => '0',
      'ss_language' => '0',
      'ss_name' => '0',
      'ss_name_formatted' => '0',
      'tags_a' => '0',
      'tags_h1' => '5.0',
      'tags_h2_h3' => '3.0',
      'tags_h4_h5_h6' => '2.0',
      'tags_inline' => '1.0',
      'taxonomy_names' => '2.0',
      'timestamp' => '0',
      'tos_content_extra' => '0.1',
      'tos_name' => '3.0',
      'tos_name_formatted' => '0',
      'ts_comments' => '0.5',
      'ts_field_bgimage_id' => '1.0',
      'url' => '0',
    ),
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
