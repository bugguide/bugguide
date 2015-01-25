<?php

/**
 * Implements hook_drush_command().
 */
function bgmigrate_drush_command() {

  $items['bgmigrate-users'] = array(
    'description' => 'Migrate users to D7 fields.',
    'aliases' => array('bgmu'),
  );

  return $items;
}

function drush_bgmigrate_users() {
  $result = db_query('SELECT uid FROM {users} WHERE uid > 0');
  foreach ($result as $record) {
    $uid = $record->uid;
    $result1 = db_query('SELECT f.name, f.type, v.uid, v.value FROM {profile_field} f INNER JOIN {profile_value} v ON f.fid = v.fid WHERE uid = :uid', array(':uid' => $uid));
    $profile = array();
    foreach ($result1 as $record1) {
      if (empty($profile[$record1->name])) {
        // No need to unserialize because only date needs that
        // and we don't have any date profile fields.
        $profile[$record1->name] = $record1->value;
      }
    }
 
    if (!$profile) {
      continue;
    }
    
    $account = user_load($uid);
    
    $fields = array('user_bg_homepage', 'user_biography', 'city_state_country', 'default_state_country', 'email', 'user_full_name', 'user_homepage', 'license', 'license_additional');
    foreach ($fields as $field) {
      if (isset($profile['profile_' . $field])) {
        $edit['field_' . $field][LANGUAGE_NONE][0]['value'] = $profile['profile_' . $field];
      }
    }
    
    // field_user_breadcrumb_format and field_user_scientific_use are list fields
    $edit['field_user_bg_homepage'][LANGUAGE_NONE][0]['value'] = $account->profile_homepage;
    
    if (!isset($account->data['guide_breadcrumbs'])) {
      //drupal_set_message(print_r($account));
      $account->data['guide_breadcrumbs'] = '0';
    }
    
    switch($account->data['guide_breadcrumbs']) {
      case '0':
        $edit['field_breadcrumb_format'][LANGUAGE_NONE][0]['value'] = 'Common name (Scientific name)';
        break;
        
      case '1':
        $edit['field_breadcrumb_format'][LANGUAGE_NONE][0]['value'] = 'Scientific name (Common name)';
        break;
        
      case '2':
        $edit['field_breadcrumb_format'][LANGUAGE_NONE][0]['value'] = 'Common name';
        break;
        
      case '3':
        $edit['field_breadcrumb_format'][LANGUAGE_NONE][0]['value'] = 'Scientific name';
        break;
        
    }
    
    // All users default to this; they can opt-out by unchecking the box.
    $edit['field_user_scientific_use'][LANGUAGE_NONE][0]['value'] = 1;
    
    // TODO migrate location and county to addressfield
    // TODO migrate subscriptions
   }
}
