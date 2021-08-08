<?php

include_once 'bgmap.fips.inc';

// /node/203/bgmap/json is called by maps.eddmaps.org to retrieve data to
// populate the map.
function bgmap_json($node) {
  global $LOCATION_CODES;
  global $FIPS;

  // Debugging.
  //$output = '';

  // Sanity check.
  if ($node->type != 'bgpage') {
    // Maps are only available for taxa.
    drupal_json_output(array());
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
      //$output .= "<p>Invalid state $image->location_code</p>";
      continue;
    }
    $state = $LOCATION_CODES[$image->location_code]; // Iowa
  
    if (!isset($FIPS[$state])) {
      // We looked up Iowa from IA but Iowa is not defined in $FIPS['Iowa']
      // This should never happen.
      //$output .= "<p>Did not find state '$state'</p>";
      continue;
    }

    if (!isset($FIPS[$state][$image->county])) {
      // Invalid county.
      //$output .= "<p>Invalid county $image->county when looking for FIPS[ $state ][ $image->county ]</p>";
      continue;
    }
    
    $county_fips = $FIPS[$state][$image->county];
    //$output .= '<p>' . $image->nid . '-' . $image->series;
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

  drupal_add_http_header('Access-Control-Allow-Origin', "*");
  drupal_add_http_header('Access-Control-Allow-Methods', 'GET');
  drupal_json_output($occurrences);
}

function bgmap_state_json($node) {
  global $LOCATION_CODES;
  global $FIPS;
  global $FIPS_STATES;

  // Debugging.
  //$output = '';

  if ($node->type != 'bgpage') {
    // Maps are only available for taxa.
    drupal_json_output(array());
  }
    
  // Find children of this taxon.
  $result = db_query("SELECT bgi.nid, bgi.location_code, bis.series 
    FROM {bgimage} bgi 
    LEFT JOIN {bgimage_series} bis ON bgi.nid = bis.nid 
    WHERE bgi.parent_idx REGEXP :node",
    array(':node' => '^' . $node->field_parent[LANGUAGE_NONE][0]['value'] . ',' . $node->nid . ',')
    )->fetchAll();
  
  // Compile a list of states for which occurrence records exist.
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
      //$output .= "<p>Invalid state $image->location_code</p>";
      continue;
    }
      
    if (!isset($FIPS_STATES[$image->location_code])) {
      // We looked up IA but IA is not defined in $FIPS_STATES['IA']
      // This should never happen.
      //$output .= "<p>Did not find state '$image->location_code'</p>";
      continue;
    }
    
    //$output .= '<p>' . $image->nid . '-' . $image->series;
    $state_fips = $FIPS_STATES[$image->location_code];
    if (!isset($occurrences[$state_fips])) {
      $occurrences[$state_fips] = array(
        'reportCount' => 1,
      );
    }
    else {
      $occurrences[$state_fips]['reportCount']++;
    }
  }
  
  // Format is:
  //  "4": {"MyNumericData":1,"MyTextData":"us_AL_01003"}

  // Debugging
  //watchdog('bgmap', $output);

  drupal_add_http_header('Access-Control-Allow-Origin', "*");
  drupal_add_http_header('Access-Control-Allow-Methods', 'GET');
  drupal_json_output($occurrences);
}


function bgmap_page($nid) {
  if (in_array($nid, array(3,878075,52))) {
    return t('Maps are not available for taxa with more than a million records.');
  }
  
  $node = node_load($nid);
  if (!$node) {
    return MENU_NOT_FOUND;
  }
  drupal_add_js('https://calc.bugwoodcloud.org/static/js/iframe.js', 'external');
  $output = '<div id="iframecontainer"><iframe src="https://maps.eddmaps.org/bugguidestate/?node=' . $node->nid . '" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" height="500" width="960" scrolling="no" seamless></iframe></div>';
  $output .= '<div id="iframecontainer"><iframe src="https://maps.eddmaps.org/bugguide/?node=' . $node->nid . '" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" height="500" width="960" scrolling="no" seamless></iframe></div>';
  $output .= '<p>The state map may show different results than the county map because contributors do not always submit a county, or they may have misspelled the county name.</p>';
  if (user_is_logged_in()) {
    $output .= '<p>See <a href="/advanced-search?taxon=' . $nid . '">records that make up this map</a>.';
  }
  else {
    $output .= '<p>Log in to see a link to records that make up this map.</p>';
  } 

/*
// Uses location services.
$output = '<div id="iframecontainer">
     <iframe id="frame" src="https://calc.bugwoodcloud.org/calculator.cfm" frameborder="0" style="width:100%;height:100%;"></iframe>
</div>';
*/
  return $output;
}
