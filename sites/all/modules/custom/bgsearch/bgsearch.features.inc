<?php
/**
 * @file
 * bgsearch.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bgsearch_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function bgsearch_default_search_api_index() {
  $items = array();
  $items['bugguide'] = entity_import('search_api_index', '{
    "name" : "BugGuide",
    "machine_name" : "bugguide",
    "description" : null,
    "server" : "solr",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "book_reference", "bgpage", "bgimage", "bglink" ] },
      "index_directly" : 0,
      "cron_limit" : "800",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "comment_count" : { "type" : "integer" },
        "created" : { "type" : "date" },
        "field_bgimage_copyright_owner" : { "type" : "text" },
        "field_bgimage_county" : { "type" : "text" },
        "field_bgimage_date" : { "type" : "date" },
        "field_bgimage_id" : { "type" : "text" },
        "field_bgimage_life_stage" : { "type" : "list\\u003Cstring\\u003E" },
        "field_bgimage_location" : { "type" : "text" },
        "field_bgimage_location_code" : { "type" : "text" },
        "field_bgimage_sex" : { "type" : "list\\u003Cstring\\u003E" },
        "field_bgimage_size" : { "type" : "text" },
        "field_book_reference_author" : { "type" : "text" },
        "field_book_reference_isbn" : { "type" : "text" },
        "field_book_reference_publisher" : { "type" : "text" },
        "field_book_reference_show_image" : { "type" : "boolean" },
        "field_book_reference_weight" : { "type" : "integer" },
        "field_book_reference_year" : { "type" : "integer" },
        "field_common_name" : { "type" : "text" },
        "field_editors" : { "type" : "text" },
        "field_hodges_number" : { "type" : "text" },
        "field_location_codes" : { "type" : "text" },
        "field_parent" : { "type" : "text" },
        "field_representative_images" : { "type" : "text" },
        "field_scientific_name" : { "type" : "text" },
        "field_taxon" : { "type" : "integer" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "search_api_url" : { "type" : "uri" },
        "taxonomy_forums" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "vid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : [] }
        },
        "search_api_alter_add_url" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "field_parent" : true,
              "field_bgimage_copyright_owner" : true,
              "field_bgimage_county" : true,
              "field_bgimage_id" : true,
              "field_bgimage_location" : true,
              "field_bgimage_location_code" : true,
              "field_bgimage_size" : true,
              "field_common_name" : true,
              "field_editors" : true,
              "field_hodges_number" : true,
              "field_location_codes" : true,
              "field_representative_images" : true,
              "field_scientific_name" : true,
              "field_book_reference_author" : true,
              "field_book_reference_isbn" : true,
              "field_book_reference_publisher" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_parent" : true,
              "field_bgimage_copyright_owner" : true,
              "field_bgimage_county" : true,
              "field_bgimage_id" : true,
              "field_bgimage_location" : true,
              "field_bgimage_location_code" : true,
              "field_bgimage_size" : true,
              "field_common_name" : true,
              "field_editors" : true,
              "field_hodges_number" : true,
              "field_location_codes" : true,
              "field_representative_images" : true,
              "field_scientific_name" : true,
              "field_book_reference_author" : true,
              "field_book_reference_isbn" : true,
              "field_book_reference_publisher" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_parent" : true,
              "field_bgimage_copyright_owner" : true,
              "field_bgimage_county" : true,
              "field_bgimage_id" : true,
              "field_bgimage_location" : true,
              "field_bgimage_location_code" : true,
              "field_bgimage_size" : true,
              "field_common_name" : true,
              "field_editors" : true,
              "field_hodges_number" : true,
              "field_location_codes" : true,
              "field_representative_images" : true,
              "field_scientific_name" : true,
              "field_book_reference_author" : true,
              "field_book_reference_isbn" : true,
              "field_book_reference_publisher" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 1,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_parent" : true,
              "field_bgimage_copyright_owner" : true,
              "field_bgimage_county" : true,
              "field_bgimage_id" : true,
              "field_bgimage_location" : true,
              "field_bgimage_location_code" : true,
              "field_bgimage_size" : true,
              "field_common_name" : true,
              "field_editors" : true,
              "field_hodges_number" : true,
              "field_location_codes" : true,
              "field_representative_images" : true,
              "field_scientific_name" : true,
              "field_book_reference_author" : true,
              "field_book_reference_isbn" : true,
              "field_book_reference_publisher" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_porter_stemmer" : {
          "status" : 1,
          "weight" : "35",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_parent" : true,
              "field_bgimage_copyright_owner" : true,
              "field_bgimage_county" : true,
              "field_bgimage_id" : true,
              "field_bgimage_location" : true,
              "field_bgimage_location_code" : true,
              "field_bgimage_size" : true,
              "field_common_name" : true,
              "field_editors" : true,
              "field_hodges_number" : true,
              "field_location_codes" : true,
              "field_representative_images" : true,
              "field_scientific_name" : true,
              "field_book_reference_author" : true,
              "field_book_reference_isbn" : true,
              "field_book_reference_publisher" : true
            },
            "exceptions" : "texan=texa"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "40",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always",
            "highlight_partial" : 0
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_page().
 */
function bgsearch_default_search_api_page() {
  $items = array();
  $items['bugguide_search'] = entity_import('search_api_page', '{
    "index_id" : "bugguide",
    "path" : "search\\/global",
    "name" : "Content",
    "machine_name" : "bugguide_search",
    "description" : "",
    "options" : {
      "mode" : "terms",
      "fields" : [],
      "per_page" : "20",
      "result_page_search_form" : 1,
      "get_per_page" : 1,
      "view_mode" : "teaser",
      "empty_behavior" : "results"
    },
    "enabled" : "1"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function bgsearch_default_search_api_server() {
  $items = array();
  $items['solr'] = entity_import('search_api_server', '{
    "name" : "Solr",
    "machine_name" : "solr",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "bgsolr2.ent.iastate.edu",
      "port" : "8983",
      "path" : "solr\\/bugguide_search_api",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO",
      "log_query" : 1,
      "log_response" : 0,
      "commits_disabled" : 0
    },
    "enabled" : "1"
  }');
  return $items;
}
