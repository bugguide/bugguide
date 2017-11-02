<?php

// BISON export script.
// Exports BugGuide data for a given tree node on down in BISON format.
//
// Run it like this, from the command line in the root of a bugguide7 install:
// REMOTE_ADDR=127.0.0.1 php -f ./bison_export.php
//
// John VanDyk

// START CONFIGURATION

// logging
// $debug_logging = TRUE;
// Which node is the top of the tree? (Arthropods is node 3).
// Retrieve only records that are children of this node in the tree.
// Can be set in environment variable e.g., TREETOP=3
$treetop = getenv('TREETOP', TRUE);
if (!$treetop) {
  $treetop = '3';
  // or hardcode it here
  //$treetop = '191';
}

$laterthan = getenv('LATERTHAN', TRUE);
if (!$laterthan) {
  $laterthan = 0;
}

// Limit. This is the number of nodes we will retrieve.
// For debugging, use LIMIT 3
// Otherwise, use a blank string.
$limit = '';
//$limit = 'LIMIT 4';

// There will be a link to a thumbnail image in the output. How wide of an image
// will this be? 125 is thumbnail width; 560 is regular image width.
$width_of_thumbnail = 125;

// END CONFIGURATION

function bison_log($message) {
  global $debug_logging;
  if ($debug_logging) echo $message . "\n";
}

bison_log("Beginning");

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
 SELECT n.title, tx.entity_id, tx.revision_id, p.field_parent_value, sn.field_scientific_name_value
  FROM field_data_field_taxon tx
  JOIN field_data_field_parent p ON tx.revision_id = p.revision_id
  JOIN node n ON tx.revision_id = n.vid
  LEFT JOIN field_data_field_scientific_name sn ON sn.revision_id = p.revision_id
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
    'immediate_parent' => end(explode(',', $record->field_parent_value)),
    'specific_epithet' => $specific_epithet,
    'common_name' => $record->title,
    'children' => array(),
  );
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
  echo "clean_provided_scientific_name \t";
  echo "itis_common_name \t";
  echo "itis_tsn \t";
  echo "basis_of_record \t";
  echo "verbatimEventDate \t";
  echo "occurrence_date \t";
  echo "year \t";
  echo "provider \t";
  echo "provier_url \t";
  echo "resource \t";
  echo "resource_url \t";
  echo "occurrence_url \t";
  echo "catalog_number \t";
  echo "collector \t";
  echo "collector_number \t";
  echo "valid_accepted_scientific_name \t";
  echo "valid_accepted_tsn \t";
  echo "provided_scientific_name \t";
  echo "provided_tsn \t";
  echo "latitude \t";
  echo "longitude \t";
  echo "verbatim_elevation \t";
  echo "verbatim_depth \t";
  echo "calculated_county_name \t";
  echo "calculated_fips \t";
  echo "calculated_state_name \t";
  echo "centroid \t";
  echo "provided_county_name \t";
  echo "provided_fips \t";
  echo "provided_state_name \t";
  echo "thumb_url \t";
  echo "associated_media \t";
  echo "associated_references \t";
  echo "general_comments \t";
  echo "id \t";
  echo "provider_id \t";
  echo "resource_id \t";
  echo "provided_common_name \t";
  echo "provided_kingdom \t";
  echo "geodetic_datum \t";
  echo "coordinate_precision \t";
  echo "coordinate_uncertainty \t";
  echo "verbatim_locality \t";
  echo "iso_country_code \t";
  echo "AdditionalDarwinCore \t";
  echo "lifeStage \t";
  echo "Sex \t";
  echo "Size";
  echo "\n";
}

function dump_record($taxon) {
  foreach ($taxon['children'] as $record) {
  //print_r($record);
  
    // The data template.
    
    // clean_provided_scientific_name (Scientific name (monomial, binomial, trinomial or quadrinomial) with all taxon author and year values, special characters etc. removed.)
    // Misumenoides formosipes	
    dump($taxon['genus_name'] . ' ' . $taxon['specific_epithet']);
  
    // itis_common_name ([Inserted by BISON] Common name that according to ITIS, corresponds to the clean_provided_scientific name.)
    // whitebanded crab spider	
    dump();
  
    // itis_tsn ([Inserted by BISON] ITIS Taxonomic Serial Number (TSN) that is associated with the clean_provided_scientific_name.)
    // 883799
    dump();
  
    // basis_of_record (Controlled vocabulary options: observation, living, specimen, fossil, literature, unknown.)
    // observation	
    dump('observation');
  
    // verbatimEventDate (Date as it appears in original raw dataset.)
    // September 10, 2011	
    dump($record['verbatimeEventDate']);

    // occurrence_date (ISO 8601 Standard Formatted date generated or derived from verbatimEventDate. Format: yyyy-mm-dd or yyyy only.)
    // 2011-09-10	
    dump($record['occurrence_date']);
    
    // year (yyyy)
    // 2011	
    dump($record['year']);

    // provider (BISON)
    // BISON
    dump('BISON');
    
    // provider_url (http://bison.usgs.ornl.gov)	
    // http://bison.usgs.ornl.gov
    dump('http://bison.usgs.ornl.gov');
    
    // resource ([Inserted by BISON] Dataset name following BISON Standardized Syntax (See Data Providers page on BISON Web site).)	
    // BugGuide (negotiable)
    dump('BugGuide');
    
    // resource_url ([Inserted by BISON] Link to the metadata record published in the BISON IPT in association with this dataset.)	
    // http://bison.ornl.gov/ipt/resource.do?r=bugguide (DRAFT not public yet)	
    dump('http://bison.ornl.gov/ipt/resource.do?r=bugguide');

    // occurrence_url (Unique URL pointing to species page specific to a single occurrence record.)
    // https://bugguide.net/node/view/580134	
    dump($record['occurrence_url']);

    // catalog_number (Unique specimen/number or record unique-identifier. Usually persistent, unique within and among datasets.)
    // 580134	
    dump($record['catalog_number']);

    // collector (Name(s) of collector(s) for each species occurrence.)
    // esellers	
    dump($record['collector']);

    // collector_number ((Specimen) number sometimes applied by collectors while out collecting in the field. Sometimes unique within a dataset.)
    // DSCF6910sml	
    dump($record['collector_number']);

    // valid_accepted_scientific_name ([Inserted by BISON] Taxonomically valid or accepted scientific name according to ITIS. May be the same as or different from provided_scientific_name).
    // Misumenoides formosipes	
    dump();

    // valid_accepted_tsn ([Inserted by BISON] ITIS TSN that corresponds to the valid_accepted_scientific_name).
    // 883799	
    dump();

    // provided_scientific_name (Verbatim scientific name as it appears in the original raw dataset. May contain taxon author and year information and/or special characters etc.).
    // Misumenoides formosipes	
	dump($taxon['genus_name'] . ' ' . $taxon['specific_epithet']);

    // provided_tsn (ITIS or other taxonomic serial number associated with the provided_scientific_name in the original raw dataset.)
    //
    dump();

    // latitude (Decimal latitude (up to 6 decimal places). If missing from raw original dataset, this can be calculated by performing a join between provided_county_name field and and county centroid coordinates index.)
    // Either a specific point coordinate or a centroid coordinate generated at BugGuide or at BISON (the latter based on provided_county_name)
    dump();
    
    // longitude (Decimal longitude (up to 6 decimal places). If missing from raw original dataset, this can be calculated by performing a join between provided_county_name field and and county centroid coordinates index.)
    // Either a specific point coordinate or a centroid coordinate generated at BugGuide or at BISON (the latter based on provided_county_name)	
	dump();
	
	// verbatim_elevation (Elevation as it appears in original raw dataset.)
	//
	dump();
	
	// verbatim_depth (Depth as it appears in original raw dataset. Usually in aquatic/marine datasets.)
	//
	dump();
	
	// calculated_county_name ([Inserted by BISON] Value is calculated based on latitude and longitude coordinates.)
	//
	dump();
	
	// calculated_fips ([Inserted by BISON] Federal Information Process Standard five-digit numeric code for state and county calculated based on values in the provided_county_name and provided_state_name values.)
	//
	dump();
	
	// calculated_state_name ([Inserted by BISON] Value is calculated based on latitude and longitude coordinates.)
	//
	dump();
	
	// centroid (Controlled vocabulary:  county (also used for parish, or organized borough), state, protected area, 10 Minute Block, HUC12 (Hydrologic Unit Code (HUC)), HUC10, HUC8, HUC6, lake (calculated centroid of a lake or other coastal or inland water body), other (known type of centroid not on this list), unknown (nature of the centroid of the record is generic or undefined), zip code.)
	// county
	dump();
	
	// provided_county_name (County name as it appears in original raw dataset.)
    // Loudoun	
    dump($record['provided_county_name']);
    
    // provided_fips (Federal Information Processing Standard numeric code as it appears in original raw dataset.)
    //
    dump();
    
    // provided_state_name (State name as it appears in original raw dataset.)
    // Virginia
    dump($record['provided_state_name']);
    
    // thumb_url (A VERY SPECIFIC SYNTAX field for associating thumbnail images or media icons with original(size) associated_media items.*The description section is not required. e.g. [{\\"url\\":\\"BugGuideThumbNailImageURL\\",\\"description\\":\\"WhateverYouWantforImageCaption\\"}]    Multiple thumbnails are each enclosed in curly brackets and separated in the syntax string by a comma e.g.   [{\\"url\\":\\"BugGuideThumbNailImageURL_1\\",\\"description\\":\\"ImageCaption_1\\"},{\\"url\\":\\"BugGuideThumbNailImageURL_2\\",\\"description\\":\\"ImageCaption_2\\"}])
    // [{\\"url\\":\\"https://bugguide.net/images/cache/HKU/KQK/HKUKQKNKMKO09QHS1QLSVQT08QT0ZKUKSKWK8KAKNQ1KNQHSWQV0WQ30AQY0XKRS8KDKSKCKMKCKGK1KBQZSMKDKMK.jpg\\",\\"description\\":\\"Whitebanded Crab Spider (Misumenoides formosipes)\\"}]	
    dump($record['thumb_url']);

    // associated_media (A VERY SPECIFIC SYNTAX field for defining and linking thumbnail images or icons referenced in thumb_url field with with associated_media (e.g. original(sized) images, video, audio) NOTE that the order of the thumbnail images must match the order of the original images e.g.  [{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"BugGuideRecordSpecificORIGINALImageURL\\"}]  *Multiple Original Image URLs are each surrounded by curly brackets and separated by a comma e.g.  [{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"BugGuideRecordSpecificORIGINALImageURL_1\\"},{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"BugGuideRecordSpecificORIGINALImageURL_2\\"}])
    // [{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"https://bugguide.net/images/raw/VRY/KUR/VRYKUR3K9R0QFR0QS0E0Z020DQ50AR40ARYKBRXQBRLQNRHQYQJKDQM0Z0I0FQI0TQ40WRFKFQM0FQ.jpg\\"}]	
    dump($record['associated_media']);
	
	// associated_references (A VERY SPECIFIC SYNTAX field for defining and linking (usually bibliographic) citations for publication or Web resources. Can be dataset-specific or individual record-specific e.g.   [{\\"url\\":\\"http://dx.doi.org/10.15560/11.3.1665\\",\\"description\\":\\"Sellers, E. and D. McCarthy. 2015. Distribution and floral hosts of Anthophorula micheneri (Timberlake, 1947) and Hylaeus sparsus (Cresson, 1869), (Insecta: Hymenoptera: Apoidea: Anthophila), with new state records in Giles and Loudoun counties, Virginia, eastern USA. Check List 11(3):1665. doi:10.15560/11.3.1665\\"}]  OR  [{\\"url\\":\\"yourURLgoesHere\\",\\"description\\":\\"TextOfYourCitationGoesHere_CanIncludeURLatEnd\\"}])
	//
	dump();
	
	// general_comments (As its name suggests, this field can contain general comments about the dataset, field notes or other concatenated data fields that were not already accommodated by BISON fields.)
    // Hunting among goldenrod (Solidago sp.) flowers as usual.	
	dump($record['general_comments']);
	
	// id ([Inserted by BISON] Record-level ID, unique within the dataset but not necessarily persistent. Do not use this field for your unique and/or persistent record identifiers. Suggest using the catalog_number field if it is not already populated.)
	//
	dump();
	
	// provider_id (440)
    // 440
    dump('440');
    
    // resource_id (Unique identifier for the dataset. [Inserted by BISON])
    //
    dump('100061');
    
    // provided_common_name (Common name as it appears in original raw dataset.)
    //
    dump($record['provided_common_name']);
    
    // 	provided_kingdom (Controlled vocabulary: Animalia, Plantae, Bacteria, Fungi, Protozoa, Chromista, Archaea, Virus.)
    // Animalia
    dump('Animalia');

    // geodetic_datum (Ellipsoid, geodetic datum, or spatial reference system (SRS) upon which the geographic coordinates given in the Latitude and Longitude fields are based (e.g. WGS84))	
	//
	dump();
	
	// coordinate_precision (Decimal representation of the exactness of the latitude and longitude coordinates.)
	//
	dump();
	
	// coordinate_uncertainty (Horizontal distance (in meters) from the latitude and longitude coordinates, describing the smallest circle containing the whole of the species occurrence location. Not necessary for county centroid coordinate pairs.)
	//
	dump();
	
	// verbatim_locality (Locality information not already contained in other geographic/locality fields e.g. Name of a city, national park, lake, wildlife refuge or other protected area; or a narrative description of how to get to the collection location e.g. Near the large boulder to the left of the waterfall.)
    // Banshee Reeks Nature Preserve
    dump($record['verbatim_locality']);
    
    // iso_country_code (Controlled vocabulary: AS = American Samoa, GU = Guam, FM = Micronesia, Federated States of, PW = Palau, Republic of, UM = United States Minor Outlying Islands, MH = Marshall Islands, Republic of, MP = Northern Mariana Islands, PR = Puerto Rico, VI = Virgin Islands, U.S.)	
    // US
    dump($record['iso_country_code']);	
    
    // Additional DarwinCore compatible data fields we can publish to GBIF (not currently accommodated in BISON. REF: http://rs.tdwg.org/dwc/terms/) -->	
    //
    dump();
    
    // lifeStage
    //
    dump($record['lifeStage']);
    
    // Sex
    //
    dump($record['sex']);
    
    // Size
    //
    dump($record['size'], TRUE);
  }
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
  bison_log("Finding children for:");
  //print_r($t);
  $taxon = $t;

  // Find child images of this species.
  $parent = $taxon['parent'] . ',' . $taxon['entity_id'];
  // Regex for parent 1,2,3 matches 1,2,3 and 1,2,3,4 and 1,2,3,5
  bison_log("Querying for $parent");
  $result = db_query("SELECT entity_id FROM field_data_field_parent WHERE field_parent_value REGEXP '$parent(\,|$)'");
  
  // Load each image and mine for data.
  foreach ($result as $image) {
    // If LATERTHAN was specified, select only records later than this.
    if ($laterthan) {
      bison_log('entity id ' . $image->entity_id);
      $recent_result = db_query('SELECT created FROM {node} WHERE nid = :nid', array(':nid' => $image->entity_id));
      bison_log('finished query');
      bison_log($recent_result->created);
      if ($recent_result->created < $laterthan) {
        continue;
      }
    }

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
    // 
    $to_obfuscate = $base . "?l=" . $width_of_thumbnail;
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
    $taxon['children'][$image->entity_id]['thumb_url'] = '[{\\"url\\":\\"' . $absolute_thumbnail . '\\"}]';
    $taxon['children'][$image->entity_id]['associated_media'] = '[{\\"type\\":\\"image\\",\\"mediaUrl\\":\\"' . 'https://bugguide.net/node/view/' . $node->nid . '\\"}]';
    
    $general_comments = check_plain(strip_tags($node->{'body'}[LANGUAGE_NONE][0]['safe_value']));
    $taxon['children'][$image->entity_id]['general_comments'] = $general_comments;
    
    // When no common name is available, BugGuide sets the node title to the scientific name.
    // Take common name if available, otherwise set provided_common_name to be empty string.
    $taxon['children'][$image->entity_id]['provided_common_name'] = '';
    
    // Note that we us $taxon array members directly here, since we are in a loop
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
  
  // Dump current records to file so we can reclaim memory.
  bison_log("dumping taxon");
  //print_r($taxon);
  dump_record($taxon);
  // Free memory.
  $taxon = NULL;
  
  $counter++;
}
