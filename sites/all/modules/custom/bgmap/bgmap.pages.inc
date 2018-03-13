<?php

include_once 'bgmap.fips.inc';

function bgmap_json($node) {
  global $LOCATION_CODES;
  global $FIPS;

  // Debugging.
  $output = '';

  // Sanity check.
  if ($node->type != 'bgpage') {
    return t('Maps are only available for taxa.');
  }
    
  // Find children of this taxon.
  $result = db_query("SELECT bgi.nid, bgi.location_code, bgi.county, bis.series 
    FROM {bgimage} bgi 
    LEFT JOIN {bgimage_series} bis ON bgi.nid = bis.nid 
    WHERE bgi.parent_idx REGEXP :node",
    array(':node' => '^' . $node->field_parent[LANGUAGE_NONE][0]['value'] . ',' . $node->nid . ',')
    )->fetchAll();
  
  // Compile a list of states and counties for which occurrence records exist.
  $occurrences = array();
  
  foreach ($result as $image) {
    // If a specimen has more than one image, only count one occurrence.
    // Single-image specimens will have series as NULL.
    // First specimen of a series will have nid == series.
    if (($image->series !== NULL) && ($image->series != $image->nid)) {
      continue;
    }
    
    // Construct string for creating map.
    if (!isset($LOCATION_CODES[$image->location_code])) {
      // Invalid state.
      $output .= "<p>Invalid state $image->location_code</p>";
      continue;
    }
    $state = $LOCATION_CODES[$image->location_code]; // Iowa
  
    if (!isset($FIPS[$state])) {
      $output .= "<p>Did not find state '$state'</p>";
    }

    if (!isset($FIPS[$state][$image->county])) {
      // Invalid county.
      $output .= "<p>Invalid county $image->county when looking for FIPS[ $state ][ $image->county ]</p>";
      continue;
    }
    
    $county_fips = $FIPS[$state][$image->county];
    $output .= '<p>' . $image->nid . '-' . $image->series;
    if (!isset($occurrences[$county_fips])) {
      $occurrences[$county_fips] = array(
        'reportCount' => 1,
        'fmID' => 'us_' . $image->location_code . '_' . sprintf('%05d', $county_fips),
        'negative' => 0,
      );
    }
    else {
      $occurrences[$county_fips]['reportCount']++;
    }
  }
  
  // Format is:
  //  "1003": {"MyNumericData":1,"MyTextData":"us_AL_01003"}

  // Debugging
  // watchdog('bgmap', $output);
  //return $output;

  drupal_json_output($occurrences);
}
  
function bgmap_page($node) {
  return t('This page will have a map.');
}