<?php

include_once 'bgmap.fips.inc';

function bgmap_page($node) {
  global $LOCATION_CODES;
  global $FIPS;

  $output = '';

  // Sanity check.
  if ($node->type != 'bgpage') {
    return t('Maps are only available for taxa.');
  }
    
  // Find children of this taxon.
  $result = db_query("SELECT nid, location_code, county FROM bgimage WHERE parent_idx REGEXP :node", 
    array(':node' => '^' . $node->field_parent[LANGUAGE_NONE][0]['value'] . ',' . $node->nid . ',')
    )->fetchAll();
  
  // Compile a list of states and counties for which occurrence records exist.
  $occurrences = array();
  
  foreach ($result as $image) {
    
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
    
    $occurrences[] = $FIPS[$state][$image->county];
    //  "1003": {"MyNumericData":1,"MyTextData":"us_AL_01003"}
    $output .= '"' . $FIPS[$state][$image->county] . '": {}' . "\r";
  }
  
  return $output;
}
  

