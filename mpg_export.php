<?php


error_reporting(E_ERROR);

// BISON export script, modified to dump only species, not records of species.
// Exports BugGuide data for a given tree node on down in tab-delimited format.
//
// John VanDyk

// START CONFIGURATION

// logging
$debug_logging = FALSE;
// Which node is the top of the tree? (Arthropods is node 3).
// Retrieve only records that are children of this node in the tree.

// Can be set in environment variable e.g., TREETOP=3
$treetop = getenv('TREETOP', TRUE);
// If we want hodges numbers too, set HODGES env: HODGES=1
global $hodges;
$hodges = getenv('HODGES', TRUE) == 1;

if (!isset($treetop)) {
  $treetop = '3';
}

// Limit. This is the number of nodes we will retrieve.
// For debugging, use LIMIT 3
// Otherwise, use a blank string.
$limit = '';
//$limit = 'LIMIT 3';

// END CONFIGURATION

function bison_log($message) {
  global $debug_logging;
  if ($debug_logging) echo $message . "\n";
}

bison_log("Beginning");
bison_log($treetop);
bison_log($hodges);

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/sites/all/modules/custom/bg/bg_globals.inc';
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';

if (!drupal_is_cli()) {
  echo "BISON export is restricted to the command line.";
  exit();
}

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

$US_STATES = array('AL', 'AK', 'AS', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'DC', 'FM', 'FL', 'GA', 'GU', 'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MH', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ', 'NM', 'NY', 'NC', 'ND', 'MP', 'OH', 'OK', 'OR', 'PW', 'PA', 'PR', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VT', 'VI', 'VA', 'WA', 'WV', 'WI', 'WY');

$CANADA_CODES = array();
$CANADA_CODES[] = 'AB';
$CANADA_CODES[] = 'BC';
$CANADA_CODES[] = 'MB';
$CANADA_CODES[] = 'NB';
$CANADA_CODES[] = 'NL';
$CANADA_CODES[] = 'NT';
$CANADA_CODES[] = 'NS';
$CANADA_CODES[] = 'NU';
$CANADA_CODES[] = 'ON';
$CANADA_CODES[] = 'PE';
$CANADA_CODES[] = 'QC';
$CANADA_CODES[] = 'SK';
$CANADA_CODES[] = 'YT';

$LOCATION_CODES['AL'] = 'Alabama';
$LOCATION_CODES['AK'] = 'Alaska';
$LOCATION_CODES['AB'] = 'Alberta';
$LOCATION_CODES['AZ'] = 'Arizona';
$LOCATION_CODES['AR'] = 'Arkansas';
$LOCATION_CODES['BC'] = 'British Columbia';
$LOCATION_CODES['CA'] = 'California';
$LOCATION_CODES['CO'] = 'Colorado';
$LOCATION_CODES['CT'] = 'Connecticut';
$LOCATION_CODES['DE'] = 'Delaware';
$LOCATION_CODES['DC'] = 'District of Columbia';
$LOCATION_CODES['FL'] = 'Florida';
$LOCATION_CODES['GA'] = 'Georgia';
$LOCATION_CODES['HI'] = 'Hawaii';
$LOCATION_CODES['ID'] = 'Idaho';
$LOCATION_CODES['IL'] = 'Illinois';
$LOCATION_CODES['IN'] = 'Indiana';
$LOCATION_CODES['IA'] = 'Iowa';
$LOCATION_CODES['KS'] = 'Kansas';
$LOCATION_CODES['KY'] = 'Kentucky';
$LOCATION_CODES['LA'] = 'Louisiana';
$LOCATION_CODES['ME'] = 'Maine';
$LOCATION_CODES['MB'] = 'Manitoba';
$LOCATION_CODES['MD'] = 'Maryland';
$LOCATION_CODES['MA'] = 'Massachusetts';
$LOCATION_CODES['MI'] = 'Michigan';
$LOCATION_CODES['MN'] = 'Minnesota';
$LOCATION_CODES['MS'] = 'Mississippi';
$LOCATION_CODES['MO'] = 'Missouri';
$LOCATION_CODES['MT'] = 'Montana';
$LOCATION_CODES['NE'] = 'Nebraska';
$LOCATION_CODES['NV'] = 'Nevada';
$LOCATION_CODES['NB'] = 'New Brunswick';
$LOCATION_CODES['NH'] = 'New Hampshire';
$LOCATION_CODES['NJ'] = 'New Jersey';
$LOCATION_CODES['NM'] = 'New Mexico';
$LOCATION_CODES['NY'] = 'New York';
$LOCATION_CODES['NL'] = 'Newfoundland/Labrador';
$LOCATION_CODES['NC'] = 'North Carolina';
$LOCATION_CODES['ND'] = 'North Dakota';
$LOCATION_CODES['NT'] = 'Northwest Territories';
$LOCATION_CODES['NS'] = 'Nova Scotia';
$LOCATION_CODES['NU'] = 'Nunavut';
$LOCATION_CODES['OH'] = 'Ohio';
$LOCATION_CODES['OK'] = 'Oklahoma';
$LOCATION_CODES['ON'] = 'Ontario';
$LOCATION_CODES['OR'] = 'Oregon';
$LOCATION_CODES['PA'] = 'Pennsylvania';
$LOCATION_CODES['PE'] = 'Prince Edward Island';
$LOCATION_CODES['QC'] = 'Quebec';
$LOCATION_CODES['RI'] = 'Rhode Island';
$LOCATION_CODES['SK'] = 'Saskatchewan';
$LOCATION_CODES['SC'] = 'South Carolina';
$LOCATION_CODES['SD'] = 'South Dakota';
$LOCATION_CODES['TN'] = 'Tennessee';
$LOCATION_CODES['TX'] = 'Texas';
$LOCATION_CODES['UT'] = 'Utah';
$LOCATION_CODES['VT'] = 'Vermont';
$LOCATION_CODES['VA'] = 'Virginia';
$LOCATION_CODES['WA'] = 'Washington';
$LOCATION_CODES['WV'] = 'West Virginia';
$LOCATION_CODES['WI'] = 'Wisconsin';
$LOCATION_CODES['WY'] = 'Wyoming';
$LOCATION_CODES['YT'] = 'Yukon Territory';

bison_log("Finding parent string for treetop");
$treetop_node = node_load($treetop, array(), TRUE);
// Append treetop nid to get the parent string for the requested treetop.
// E.g., if Dragonflies (node 191) are the treetop, $treetop_parent will be
// 3,878075,52,77,191
// No comma needed if we are at node 3 because it is the top of the tree.
$comma = $treetop == '3' ? '' : ',';
$treetop_parent = $treetop_node->{'field_parent'}[LANGUAGE_NONE][0]['value'] . $comma . $treetop;
bison_log("Treetop parent is $treetop_parent");

bison_log("Selecting all species pages beneath treetop parent");
$species_count = db_query("SELECT COUNT(revision_id) AS ct FROM field_data_field_taxon WHERE field_taxon_value = 3400 AND bundle = 'bgpage'")->fetchObject();
bison_log("$species_count->ct found");

bison_log("Loading records into memory");
$query = "
 SELECT n.title, tx.entity_id, tx.revision_id, p.field_parent_value, sn.field_scientific_name_value, hn.field_hodges_number_value
  FROM field_data_field_taxon tx
  JOIN field_data_field_parent p ON tx.revision_id = p.revision_id
  JOIN node n ON tx.revision_id = n.vid
  LEFT JOIN field_data_field_scientific_name sn ON sn.revision_id = p.revision_id
  LEFT JOIN field_data_field_hodges_number hn ON hn.revision_id = p.revision_id
  WHERE tx.field_taxon_value = 3400 AND tx.bundle = 'bgpage' AND p.field_parent_value REGEXP '$treetop_parent(\,|$)'
  $limit
";
bison_log($query);
$result = db_query($query);

// Build an array of all species records. The finished array will look like:
//  Array
//  (
//    [25] => Array
//        (
//            [revision_id] => 25
//            [entity_id] => 25
//            [parent] => 3,369633,20,22,11843,24
//            [immediate_parent] => 24
//            [specific_epithet] => coleoptrata
//            [common_name] => House Centipede
//            [genus_name] => Scutigera
//            [children] => Array
//                (
//                )
//
//        )
//

foreach ($result as $record) {  
  if ($debug_logging) print_r($record);
  $specific_epithet = $record->field_scientific_name_value;
  if (stripos($specific_epithet, 'species') !== FALSE) {
    bison_log($specific_epithet . " -> sp.");
    $specific_epithet = 'sp.';
  }
  $r[$record->revision_id] = array(
    'revision_id' => $record->revision_id,
    'entity_id' => $record->entity_id,
    'parent' => $record->field_parent_value,
    //'immediate_parent' => end(explode(',', $record->field_parent_value)),
    'specific_epithet' => $specific_epithet,
    'common_name' => $record->title,
    //'children' => array(),
  );
  if ($hodges) {
    $r[$record->revision_id]['hodges_number'] = $record->field_hodges_number_value;
  }
}

function bison_export_is_genus($nid) {
  $cache = &drupal_static(__FUNCTION__);
  if (!isset($cache)) {
    bison_log("prefilling cache");
    $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE tx.field_taxon_value = 3300");
    foreach ($result as $record) {
      $cache[$record->nid] = $record->field_scientific_name_value;
    }  
  }
  
  if (isset($cache[$nid])) {
    $obj = new stdClass();
    $obj->field_taxon_value = 3300;
    $obj->field_scientific_name_value = $cache[$nid];
    return $obj;
  }
  
  $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE n.nid = :nid", 
  array(':nid' => $nid) 
  )->fetchObject();
  //bison_log("WARNING: cache miss on $result->nid $result->title $result->field_scientific_name_value");
  return $result;
}

function bison_export_is_family($nid) {
  $cache = &drupal_static(__FUNCTION__);
  if (!isset($cache)) {
    bison_log("prefilling cache");
    $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE tx.field_taxon_value = 2700");
    foreach ($result as $record) {
      $cache[$record->nid] = $record->field_scientific_name_value;
      bison_log('cached ' . $record->nid . ' -> ' . $record->field_scientific_name_value);
    }  
  }
  bison_log('searching family cache for nid ' . $nid);
  
  if (isset($cache[$nid])) {
    bison_log('cache hit on nid ' . $nid . ' -> ' . $cache[$nid]);
    $obj = new stdClass();
    $obj->field_taxon_value = 2700;
    $obj->field_scientific_name_value = $cache[$nid];
    return $obj;
  }
  
  $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE n.nid = :nid", 
  array(':nid' => $nid) 
  )->fetchObject();
  //bison_log("WARNING: cache miss on $result->nid $result->title $result->field_scientific_name_value");
  return $result;
}

function bison_export_is_order($nid) {
  $cache = &drupal_static(__FUNCTION__);
  if (!isset($cache)) {
    bison_log("prefilling cache");
    $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE tx.field_taxon_value = 2300");
    foreach ($result as $record) {
      $cache[$record->nid] = $record->field_scientific_name_value;
      bison_log('cached ' . $record->nid . ' -> ' . $record->field_scientific_name_value);
    }  
  }
  bison_log('searching order cache for nid ' . $nid);
  
  if (isset($cache[$nid])) {
    bison_log('cache hit on nid ' . $nid . ' -> ' . $cache[$nid]);
    $obj = new stdClass();
    $obj->field_taxon_value = 2300;
    $obj->field_scientific_name_value = $cache[$nid];
    return $obj;
  }
  
  $result = db_query("
    SELECT n.title, n.nid, n.vid, tx.field_taxon_value, sn.field_scientific_name_value
    FROM node n
    JOIN field_data_field_taxon tx ON n.vid = tx.revision_id
    LEFT JOIN field_data_field_scientific_name sn ON n.vid = sn.revision_id
    WHERE n.nid = :nid", 
  array(':nid' => $nid) 
  )->fetchObject();
  //bison_log("WARNING: cache miss on $result->nid $result->title $result->field_scientific_name_value");
  return $result;
}

bison_log("Finding generic names");
// Find name of immediate parent. Continue up the tree til we find a parent
// that is a genus.
$counter = 1;
foreach ($r as $taxon) {
  if ($counter % 100 == 0) {
    bison_log("$counter records");
  }
  $found_genus = FALSE;
  $parents = array_reverse(explode(',', $taxon['parent']));
  foreach ($parents as $nid) {
    // echo "Checking if nid $nid is a genus...";
    $result = bison_export_is_genus($nid);
    //echo $result->field_taxon_value . "...";
    if ($result->field_taxon_value == 3300) {
      $found_genus = TRUE;
      break;
    }
  }
  if (!$found_genus) {
    bison_log("WARNING: did not find genus name for revision_id " . $taxon['revision_id']);
  }
  $r[$taxon['revision_id']]['genus_name'] = $result->field_scientific_name_value;
  # if taxon number is 3300 we are ok, otherwise need to go up the tree til we find a 3300
  //echo $taxon['revision_id'] . " $result->field_taxon_value for $result->nid $result->field_scientific_name_value \n";
  $counter++;
}

bison_log("Finding family names");
// Find name of immediate parent. Continue up the tree til we find a parent
// that is a family.
$counter = 1;
foreach ($r as $taxon) {
  if ($counter % 100 == 0) {
    bison_log("$counter records");
  }
  $found_family = FALSE;
  $parents = array_reverse(explode(',', $taxon['parent']));
  foreach ($parents as $nid) {
    // echo "Checking if nid $nid is a family...";
    $result = bison_export_is_family($nid);
    //echo $result->field_taxon_value . "...";
    if ($result->field_taxon_value == 2700) {
      $found_family = TRUE;
      break;
    }
  }
  if (!$found_family) {
    bison_log("WARNING: did not find family name for revision_id " . $taxon['revision_id']);
  }
  bison_log('found family ' . $result->field_scientific_name_value);
  $r[$taxon['revision_id']]['family_name'] = $result->field_scientific_name_value;
  # if taxon number is 2700 we are ok, otherwise need to go up the tree til we find a 2700
  // echo $taxon['revision_id'] . " $result->field_taxon_value for $result->nid $result->field_scientific_name_value \n";
  $counter++;
}


bison_log("Finding order names");
// Find name of immediate parent. Continue up the tree til we find a parent
// that is a family.
$counter = 1;
foreach ($r as $taxon) {
  if ($counter % 100 == 0) {
    bison_log("$counter records");
  }
  $found_order = FALSE;
  $parents = array_reverse(explode(',', $taxon['parent']));
  foreach ($parents as $nid) {
    // echo "Checking if nid $nid is a order...";
    $result = bison_export_is_order($nid);
    //echo $result->field_taxon_value . "...";
    if ($result->field_taxon_value == 2300) {
      $found_order = TRUE;
      break;
    }
  }
  if (!$found_order) {
    bison_log("WARNING: did not find order name for revision_id " . $taxon['revision_id']);
  }
  bison_log('found order ' . $result->field_scientific_name_value);
  $r[$taxon['revision_id']]['order_name'] = $result->field_scientific_name_value;
  # if taxon number is 2300 we are ok, otherwise need to go up the tree til we find a 2300
  //echo $taxon['revision_id'] . " $result->field_taxon_value for $result->nid $result->field_scientific_name_value \n";
  $counter++;
}


// We now have a complete array including generic names.
// We can proceed through each taxon and find records beneath each.

// Echo string to output, appending tab.
function dump($s, $last = FALSE) {
  // Translate specific entities
  $s = str_ireplace('&#039;', "'", $s);
  $s = str_ireplace('&quot;', '"', $s);
  
  // Remove tabs, multiple spaces, line breaks.
  $clean_s = preg_replace('/\s+/S', ' ', $s);
  $separator = $last ? "\n" : "\t";
  echo $clean_s . $separator;
}

// Headers
function dump_headers() {
  global $hodges;
  if ($hodges) {
    echo "Hodges\t";
  }
  echo "Genus\t";
  echo "Species\t";
  echo "Family\t";
  echo "Order\t";
  echo "BugGuideID\t";
  echo "URL\t";
  echo  "Common Name";
  echo "\n";
}

function dump_record($taxon) {
  global $hodges;
  if ($hodges) {
    dump($taxon['hodges_number']);  
  }
  dump($taxon['genus_name']);
  dump($taxon['specific_epithet']);
  dump($taxon['family_name']);
  dump($taxon['order_name']);
  dump($taxon['entity_id']);
  dump('https://bugguide.net/node/view/' . $taxon['entity_id']);
  dump($taxon['common_name'], TRUE);
}

dump_headers();

bison_log("Finding records");
$counter = 1;
// Step through all of the genera and find records beneath each.
foreach ($r as $t) {
  // Progress indicator
  if ($counter % 100 == 0) {
    bison_log("$counter records");
  }
  
  // To be memory-efficient, we'll reuse an array variable, otherwise we'll run
  // out of memory.
  //bison_log("Finding children for:");
  //print_r($t);
  $taxon = $t;

/*
  // Find child images of this species.
  $parent = $taxon['parent'] . ',' . $taxon['entity_id'];
  // Regex for parent 1,2,3 matches 1,2,3 and 1,2,3,4 and 1,2,3,5
  bison_log("Querying for $parent");
  $result = db_query("SELECT entity_id FROM field_data_field_parent WHERE field_parent_value REGEXP '$parent(\,|$)'");
  
  // Load each image and mine for data.
  foreach ($result as $image) {
    // Only export one image from a series of images of the same individual.
    $series = db_query('SELECT nid, series FROM {bgimage_series} WHERE nid = :nid', array(':nid' => $image->entity_id))->fetchAssoc();
    if ($series) {
      // This image is part of an image series.
      // Is the series based on this image? If so, the series number and nid
      // will be the same. If they are not the same, the image is part of a
      // series but it is not the base of the series.
      if ($series['series'] != $image->entity_id) {
        //bison_log("Excluding because not base of series (" . $series['series'] . " is): $image->entity_id");
        continue;
      }
    }
  
    $node = node_load($image->entity_id, array(), TRUE);
    // Exclude non-US records.
    if (in_array($node->{'field_bgimage_location_code'}[LANGUAGE_NONE][0]['value'], $US_STATES)) {
      //bison_log("Excluding non-US record https://bugguide.net/node/view/" . $node->nid);
      $taxon['children'][$image->entity_id]['iso_country_code'] = 'US';
    }
    elseif (in_array($node->{'field_bgimage_location_code'}[LANGUAGE_NONE][0]['value'], $CANADA_CODES)) {
      $taxon['children'][$image->entity_id]['iso_country_code'] = 'CA';      
    }
    else {
      // Wut, not in US or Canada or no location code.
      continue;
    }
    
    $field_bgimage_date = trim($node->{'field_bgimage_date'}[LANGUAGE_NONE][0]['value']);
    if ($field_bgimage_date != '' && $field_bgimage_date != '1969-12-31 06:00:00') {
      // 2012-06-10 05:00:00
      $taxon['children'][$image->entity_id]['verbatimEventDate'] = $node->{'field_bgimage_date'}[LANGUAGE_NONE][0]['value'];
      // 2012-06-10
      $taxon['children'][$image->entity_id]['occurrence_date'] = substr(date(DATE_ISO8601, strtotime($node->{'field_bgimage_date'}[LANGUAGE_NONE][0]['value'])), 0, 10);
      $taxon['children'][$image->entity_id]['year'] = date('Y', strtotime($node->{'field_bgimage_date'}[LANGUAGE_NONE][0]['value']));
    }
    else {
      // Rather than ending up with 1969-12-31 dates for "no date" we use blank.
      $taxon['children'][$image->entity_id]['verbatimEventDate'] = '';
      $taxon['children'][$image->entity_id]['occurrence_date'] = '';      
      $taxon['children'][$image->entity_id]['year'] = '';
    }
    $taxon['children'][$image->entity_id]['occurrence_url'] = 'https://bugguide.net/node/view/' . $node->nid;
    $taxon['children'][$image->entity_id]['catalog_number'] = $node->nid;
    // Use full name if set, otherwise username.
    $u = user_load($node->uid, TRUE);
    $collector = $u->{'field_user_full_name'}[LANGUAGE_NONE][0]['value'];
    if (!$collector) {
      $collector = $u->name;
    }
    $taxon['children'][$image->entity_id]['collector'] = $collector;
    $taxon['children'][$image->entity_id]['collector_number'] = '';
    $taxon['children'][$image->entity_id]['provided_tsn'] = '';
    
    $county = trim($node->{'field_bgimage_county'}[LANGUAGE_NONE][0]['safe_value']);
    if (substr(strtolower($county), -7) == ' county') {
      $county = substr($county, 0, -7);
    }
    $taxon['children'][$image->entity_id]['provided_county_name'] = $county;
    $taxon['children'][$image->entity_id]['provided_state_name'] = $LOCATION_CODES[$node->{'field_bgimage_location_code'}[LANGUAGE_NONE][0]['safe_value']];
    $thumbnail = bgimage_thumb($node);
    // Strip out autogenerated token to avoid having to set image_suppress_itok_output globally.
    $tokenless_thumbnail = preg_replace('/\?(itok.[^&]*)/', '', $thumbnail);
    $tokenless_thumbnail = str_replace('?&', '?', $tokenless_thumbnail);
    
    // Drupal 7 BugGuide thumbnail
    // Currently absolute_thumbnail is overwritten below so thumbnails will point to legacy site.
    // If generated from the command line, we end up with http://./files without the base url.
    $absolute_thumbnail = str_replace('http://./files', 'https://bugguide.net/files', $tokenless_thumbnail);
    //bison_log("drupal 7 thumbnail: $absolute_thumbnail");
    // The URL generated from Drupal 7 for node 1877 is:
    // 
    // https://bugguide.net/images/cache/108/K10/108K10LKZS3ROQHQYQY0BQY05Q10PQ9K5QC04QWKLK102QO04QA0LKB04QUKRKD00KDKWQVK9QB0UQB0GQF04QC05QC0.jpg
    // which deobfuscates to:
    // 665891889baf9ad4d0cb1626a5f56fb51877,bg_small
    // That is, $base . $node->nid . ',bg_small'
    // But, working thumbnail on actual BugGuide 7 site is:
    // files/styles/bg_small/public/108/K10/108K10LKZS3ROQHQYQY0BQY05Q10PQ9K5QC04QWKLK102QO04QA0LKB04QUKRKD00KDKWQVK9QB0UQB0GQF04QC05QC0.jpg?itok=YyXuyk_K

    
    // Legacy BugGuide thumbnail. Comment out when we go to Drupal 7.
    $absolute_thumbnail = str_replace('https://bugguide.net/files/styles/bg_small/public/', 'https://bugguide.net/images/cache/', $absolute_thumbnail);
    $base = $node->field_bgimage_base[LANGUAGE_NONE][0]['value'] . $node->nid;
    //bison_log("obfuscated base: " . image_obfuscate($base));
    //bison_log("url: https://bugguide.net/node/view/$node->nid");
    //bison_log("base: $base");
    $to_obfuscate = $base . "?l=125";
    $obfuscate = image_obfuscate($to_obfuscate);
    $prefix = bgimage_get_prefix($obfuscate);
    $absolute_thumbnail = 'https://bugguide.net/images/cache/' . $prefix . $obfuscate  .'.jpg';
    //bison_log("uri: $uri");
    //bison_log("deobfuscated:" . image_deobfuscate("EHLR9HRRXHAZZL6ZZLWZIL1ZUHWZ4L9ZNHJHILAZ5L9Z7LJHXL9Z9H3HGLRRGH5ZMH4ZXLGZXLUZHL9Z4LWZ4L"));
    //bison_log("working thumbnail on 7 deobfuscated: " . image_deobfuscate("108K10LKZS3ROQHQYQY0BQY05Q10PQ9K5QC04QWKLK102QO04QA0LKB04QUKRKD00KDKWQVK9QB0UQB0GQF04QC05QC0"));
    
    /*
    // This could leave us with url?&foo=bar so change it to url?foo=bar.
    */
    // With description (we're not using description)
    //$taxon['children'][$image->entity_id]['thumb_url'] = '[{\\"url\\":\\"' . $absolute_thumbnail . '\\",\\"description\\":\\"\\"}]';
    // Without description
/*
    $taxon['children'][$image->entity_id]['thumb_url'] = '[{\\"url\\":\\"' . $absolute_thumbnail . '\\"}]';
    $taxon['children'][$image->entity_id]['associated_media'] = '[{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"' . 'https://bugguide.net/node/view/' . $node->nid . '\\"}]';
    
    $general_comments = check_plain(strip_tags($node->{'body'}[LANGUAGE_NONE][0]['safe_value']));
    $taxon['children'][$image->entity_id]['general_comments'] = $general_comments;
    
    // When no common name is available, BugGuide sets the node title to the scientific name.
    // Take common name if available, otherwise set provided_common_name to be empty string.
    $taxon['children'][$image->entity_id]['provided_common_name'] = '';
    
    // Note that we use $taxon array members directly here, since we are in a loop
    // for many records of a single taxon. $r is the record but the $taxon information
    // is in $taxon.
    if ($taxon['common_name'] != $taxon['genus_name'] . ' ' . $taxon['specific_epithet']) {
      $taxon['children'][$image->entity_id]['provided_common_name'] = $taxon['common_name'];
    }

    $taxon['children'][$image->entity_id]['verbatim_locality'] = $node->{'field_bgimage_location'}[LANGUAGE_NONE][0]['safe_value'];
    $taxon['children'][$image->entity_id]['lifeStage'] = $node->{'field_bgimage_life_stage'}[LANGUAGE_NONE][0]['value'];
    
    $taxon['children'][$image->entity_id]['sex'] = '';
    if (isset($node->{'field_bgimage_gender'}[LANGUAGE_NONE])) {
      $taxon['children'][$image->entity_id]['sex'] = $node->{'field_bgimage_gender'}[LANGUAGE_NONE][0]['value'];    
    }

    $taxon['children'][$image->entity_id]['size'] = '';
    if (isset($node->{'field_bgimage_gender'}[LANGUAGE_NONE])) {
      $taxon['children'][$image->entity_id]['size'] = $node->{'field_bgimage_size'}[LANGUAGE_NONE][0]['value'];    
    }
  }
  */
  unset($taxon['children']);
  // Dump current records to file so we can reclaim memory.
  bison_log("dumping taxon");
  //print_r($taxon);
  dump_record($taxon);
  // Free memory.
  $taxon = NULL;
  
  $counter++;
}
