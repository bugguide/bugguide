<?php

/**
 * Implements hook_drush_command().
 */
function bgmigrate_drush_command() {

  $items['bgmigrate-users'] = array(
    'description' => 'Migrate users to D7 fields.',
    'aliases' => array('bgmu'),
  );
  $items['bgmigrate-users-data'] = array(
    'description' => 'Enumerate user data.',
    'aliases' => array('bgmud'),
  );

  return $items;
}

function drush_bgmigrate_users() {
  $result = db_query('SELECT uid FROM {users} WHERE uid > 0');
  foreach ($result as $record) {
    $uid = $record->uid;
    watchdog('bgmigrate', $uid);
    
    $account = user_load($uid);
    if (!isset($account->data)) {
      continue;
    }
    
    $data = $account->data;
    
    $user_full_name = isset($data['full_name']) ? $data['full_name'] : '';
    $account->field_user_full_name[LANGUAGE_NONE][0]['value'] = $user_full_name;
    
    $public_email = isset($data['public_email']) ? $data['public_email'] : '';
    $account->field_email[LANGUAGE_NONE][0]['email'] = $public_email;
    
    $homepage = isset($data['homepage']) ? $data['homepage'] : '';
    $account->field_user_homepage[LANGUAGE_NONE][0]['value'] = $homepage;
    
    // contact
    // $data['contact'] - information on how to contact user
    // This is being replaced by the Contact module which provides
    // anonymous contact.
    $contact_info = isset($data['contact']) ? $data['contact'] : '';
    $account->field_user_contact_info[LANGUAGE_NONE][0] = $contact_info;
    $account->field_user_biography[LANGUAGE_NONE][0]['format'] = 1;    
    
    // location
    $city_state_country = isset($data['location']) ? $data['location'] : '';
    $account->field_user_city_state_country[LANGUAGE_NONE][0] = $city_state_country;
    
    // biography
    $biography = isset($data['biography']) ? $data['biography'] : '';
    $account->field_user_biography[LANGUAGE_NONE][0]['value'] = $biography;
    $account->field_user_biography[LANGUAGE_NONE][0]['format'] = 1;
    
    // license
    // Two values possible. 0 = All rights reserved. 1 = CC_BY_NC_ND
    $license_num = isset($data['license']) ? $data['license'] : 0;
    if ($license_num == 0) {
      $account->field_user_content_license[LANGUAGE_NONE][0]['value'] = 'CC_NONE';
    }
    else {
      $account->field_user_content_license[LANGUAGE_NONE][0]['value'] = 'CC_BY_NC_ND';
    }
    
    // license_details
    $license_details = isset($data['license_details']) ? $data['license_details'] : '';
    $account->field_user_content_license_add[LANGUAGE_NONE][0]['value'] = $license_details;
    $account->field_user_biography[LANGUAGE_NONE][0]['format'] = 1;
    
    // subscriptions_auto
    // TODO: look in modern subscriptions module to see how this is stored
    
    // subscriptions_subscribe
    // TODO: what is this?
    
    // bugguide_homepage
    $bg_homepage = isset($data['bugguide_homepage']) ? $data['bugguide_homepage'] : '';
    $account->field_user_bg_homepage[LANGUAGE_NONE][0]['value'] = $bg_homepage;
        
    // TODO
    // location code is something like 'IA'
    // Map this into addressfield
    //$location_code = isset($data['location_code']) ? $data['location_code'] : '';
    //$account->field_default_state_country
    
    // county
    $default_county = isset($data['county']) ? $data['county'] : '';
    $account->field_user_default_county[LANGUAGE_NONE][0]['value'] = $default_county;
    
    // fullsize - what is this?
    // This was the capability to allow a user full-size access to one or more
    // images. This was not used and we are leaving it behind.
    
    // field_user_breadcrumb_format and field_user_scientific_use are list fields
    
    $breadcrumbs = isset($account->data['guide_breadcrumbs']) ? $data['guide_breadcrumbs'] : '0';    
    switch($breadcrumbs) {
      case '0':
        $account->field_user_breadcrumb_format[LANGUAGE_NONE][0]['value'] = 'Common name (Scientific name)';
        break;
        
      case '1':
        $account->field_user_breadcrumb_format[LANGUAGE_NONE][0]['value'] = 'Scientific name (Common name)';
        break;
        
      case '2':
        $account->field_user_breadcrumb_format[LANGUAGE_NONE][0]['value'] = 'Common name';
        break;
        
      case '3':
        $account->field_user_breadcrumb_format[LANGUAGE_NONE][0]['value'] = 'Scientific name';
        break;
        
    }
    
    // All users default to this; they can opt-out by unchecking the box.
    $account->field_user_scientific_use[LANGUAGE_NONE][0]['value'] = 1;
   
    user_save($account); 
   }
}

function bgmigrate_user_presave(&$edit, $account, $category) {
  $keys = array(
    'biography',
    'block',
    'contact',
    'county',
    'full_name',
    'fullsize',
    'license_details',
    'location',
    'public_email',
    'homepage',
    'bugguide_homepage',
    'guide_breadcrumbs',
    'pass1',
    'pass2',
    'session',
  );
  foreach ($keys as $key) {
    unset($edit['data'][$key]);
  }
  
}

/**
 * Walk through the legacy serialized data in users table. Requires >1024M RAM.
 * Usage:
 * 
 * drush bgmud
 */
function drush_bgmigrate_users_data() {
  $data = array();
  $data['nodata'] = 0;
  $data['notset'] = 0;
  $data['CC'] = 0;
  $data['CC_NONE'] = 0;
  
  $result = db_query('SELECT uid FROM {users} WHERE uid > 0');
  foreach ($result as $record) {
    $uid = $record->uid;
    $account = user_load($uid);
    if (!isset($account->data)) {
      $data['nodata']++;
      continue;
    }
    
    if (!is_array($account->data)) {
      print "Data is not an array in uid $uid";
      print "\r";
    }
    
    $field_of_interest = 'license';
    $account_data = $account->data;
    if (isset($account_data[$field_of_interest])) {
      if ($account_data[$field_of_interest] == 1) {
        $data['CC']++;
      }
      if ($account_data[$field_of_interest] == 0) {
        $data['CC_NONE']++;
      }
      //print_r( $account->data['subscriptions_subscribe']);//[$field_of_interest];
      print "\r";
    }
    else {
      $data['notset']++;
    }
    
    //foreach($account->data as $key => $value) {
    //  if (!isset($data[$key])) {
    //    $data[$key] = 0;
    //  }
    //  $data[$key]++;
    //}
    
    //Every 1000 give some output.
    if ($uid % 1000 == 0) {
      print $uid . "\r\n";
      print $data['notset'] . ' ' . $data['CC'] . ' ' . $data['CC_NONE'] . ' ' . $data['nodata'] . "\r\n";
    }
  }
  print_r($data);
}