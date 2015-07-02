<?php

/**
 * @file
 * Global variables for BugGuide.
 */

global $base_url;
global $image_dir;
$image_dir = DRUPAL_ROOT .'/images/';

global $image_url;
$image_url = $base_url . '/images/';

global $amazon_image_dir;
$amazon_image_dir = $image_dir . 'amazon/';

global $tmp_image_dir;
$tmp_image_dir = $image_dir . 'tmp/';

global $upload_image_dir;
$upload_image_dir = $image_dir . 'upload/';

global $raw_image_dir;
$raw_image_dir = $image_dir . 'raw/';

global $cache_image_dir;
$cache_image_dir = $image_dir . 'cache/';

global $tmp_image_url;
$tmp_image_url = $image_url . 'tmp/';

global $raw_image_url;
$raw_image_url = $image_url . 'raw/';

global $cache_image_url;
$cache_image_url = $image_url . 'cache/';

global $amazon_image_url;
$amazon_image_url = $image_url . 'amazon/';

global $maps_dir;
$maps_dir = DRUPAL_ROOT .'/maps/';

global $AMAZON_DEVELOPER_KEY;
$AMAZON_DEVELOPER_KEY = 'D35T4PG1MPY9AV';

global $AMAZON_AFFILIATE_ID;
$AMAZON_AFFILIATE_ID = 'bugguide-20';

global $TAXON_NAMES;
$TAXON_NAMES[1000] = 'Kingdom';
$TAXON_NAMES[1100] = 'Phylum';
$TAXON_NAMES[1200] = 'Subphylum';
$TAXON_NAMES[1300] = 'Superclass';
$TAXON_NAMES[1400] = 'Class';
$TAXON_NAMES[1500] = 'Subclass';
$TAXON_NAMES[1600] = 'Infraclass';
$TAXON_NAMES[1700] = 'Cohort';
$TAXON_NAMES[1800] = 'Division';
$TAXON_NAMES[1900] = 'Subdivision';
$TAXON_NAMES[2000] = 'Section';
$TAXON_NAMES[2100] = 'Subsection';
$TAXON_NAMES[2200] = 'Superorder';
$TAXON_NAMES[2300] = 'Order';
$TAXON_NAMES[2400] = 'Suborder';
$TAXON_NAMES[2500] = 'Infraorder';
$TAXON_NAMES[2600] = 'Superfamily';
$TAXON_NAMES[2700] = 'Family';
$TAXON_NAMES[2800] = 'Subfamily';
$TAXON_NAMES[2900] = 'Supertribe';
$TAXON_NAMES[3000] = 'Tribe';
$TAXON_NAMES[3100] = 'Subtribe';
$TAXON_NAMES[3200] = 'Infratribe';
$TAXON_NAMES[3300] = 'Genus';
$TAXON_NAMES[3400] = 'Species';
$TAXON_NAMES[3500] = 'Subspecies';

global $TAXON_IDS;
$TAXON_IDS['Kingdom'] = 1000;
$TAXON_IDS['Phylum'] = 1100;
$TAXON_IDS['Subphylum'] = 1200;
$TAXON_IDS['Superclass'] = 1300;
$TAXON_IDS['Class'] = 1400;
$TAXON_IDS['Subclass'] = 1500;
$TAXON_IDS['Infraclass'] = 1600;
$TAXON_IDS['Cohort'] = 1700;
$TAXON_IDS['Division'] = 1800;
$TAXON_IDS['Subdivision'] = 1900;
$TAXON_IDS['Section'] = 2000;
$TAXON_IDS['Subsection'] = 2100;
$TAXON_IDS['Superorder'] = 2200;
$TAXON_IDS['Order'] = 2300;
$TAXON_IDS['Suborder'] = 2400;
$TAXON_IDS['Infraorder'] = 2500;
$TAXON_IDS['Superfamily'] = 2600;
$TAXON_IDS['Family'] = 2700;
$TAXON_IDS['Subfamily'] = 2800;
$TAXON_IDS['Supertribe'] = 2900;
$TAXON_IDS['Tribe'] = 3000;
$TAXON_IDS['Subtribe'] = 3100;
$TAXON_IDS['Infratribe'] = 3200;
$TAXON_IDS['Genus'] = 3300;
$TAXON_IDS['Species'] = 3400;
$TAXON_IDS['Subspecies'] = 3500;

global $LOCATION_CODES;
$LOCATION_CODES[''] = 'Unknown';
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

global $CANADA_CODES;
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