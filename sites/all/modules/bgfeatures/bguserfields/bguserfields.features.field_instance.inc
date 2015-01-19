<?php
/**
 * @file
 * bguserfields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function bguserfields_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_user_bg_homepage'
  $field_instances['user-user-field_user_bg_homepage'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional. If you enter a URL here, you will be taken to that URL each time you log in. For example, to be taken to the most recent additions enter bgimage/recent',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_bg_homepage',
    'label' => 'BugGuide Homepage',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'user-user-field_user_biography'
  $field_instances['user-user-field_user_biography'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you wish, tell others a little bit about yourself.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_biography',
    'label' => 'Biography',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'user-user-field_user_breadcrumb_format'
  $field_instances['user-user-field_user_breadcrumb_format'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 'Common name (Scientific name)',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_breadcrumb_format',
    'label' => 'Show me Guide breadcrumbs using',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'user-user-field_user_city_state_country''
  $field_instances['user-user-field_user_city_state_country''] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where you live. This information is optional but it allows us to create this interesting <a href="">map of BugGuide users</a>. By default only state and country are shown publicly. If you want to contribute to the map but not show any location information publicly check the Do not share publicly box.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_city_state_country'',
    'label' => 'City, State, Country',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(),
        'default_country' => '',
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'user-user-field_user_default_state_country'
  $field_instances['user-user-field_user_default_state_country'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Image submissions will use this location by default. (You can change it during image submission.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_default_state_country',
    'label' => 'Default State and Country',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(
          'CA' => 'CA',
          'US' => 'US',
        ),
        'default_country' => '',
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'user-user-field_user_email'
  $field_instances['user-user-field_user_email'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional email address for others to see. You may wish to modify it in an obvious way to avoid spam (for example, me_NO_SPAM@example.com).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_email',
    'label' => 'Public e-mail address',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'user-user-field_user_full_name'
  $field_instances['user-user-field_user_full_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional full name for others to see. If you leave this blank, your username will be used instead.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_full_name',
    'label' => 'Full Name',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'user-user-field_user_homepage'
  $field_instances['user-user-field_user_homepage'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 'http://',
      ),
    ),
    'deleted' => 0,
    'description' => 'Optional URL of your home page on the internet.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_homepage',
    'label' => 'Homepage',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'user-user-field_user_license'
  $field_instances['user-user-field_user_license'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'creative_commons',
        'settings' => array(),
        'type' => 'creative_commons_small_image',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_license',
    'label' => 'Contributed content license terms',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'creative_commons',
      'settings' => array(),
      'type' => 'radios',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'user-user-field_user_license_additional'
  $field_instances['user-user-field_user_license_additional'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Feel free to provide more specific license information here.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_license_additional',
    'label' => 'Additional license information',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'user-user-field_user_scientific_use'
  $field_instances['user-user-field_user_scientific_use'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => 'The collection of data at BugGuide is very useful. For example, a researcher may want to use BugGuide observations to plot the spread of a species over time. We would very much like to include 

data that you submit in the BugGuide data set. Your images will never be published without your permission, just included in scientific analyses. However, if you do not want your submissions included, you may uncheck this box.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_scientific_use',
    'label' => 'Include My Data in Scientific Use',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 15,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional license information');
  t('Biography');
  t('BugGuide Homepage');
  t('City, State, Country');
  t('Contributed content license terms');
  t('Default State and Country');
  t('Feel free to provide more specific license information here.');
  t('Full Name');
  t('Homepage');
  t('If you wish, tell others a little bit about yourself.');
  t('Image submissions will use this location by default. (You can change it during image submission.)');
  t('Include My Data in Scientific Use');
  t('Optional URL of your home page on the internet.');
  t('Optional email address for others to see. You may wish to modify it in an obvious way to avoid spam (for example, me_NO_SPAM@example.com).');
  t('Optional full name for others to see. If you leave this blank, your username will be used instead.');
  t('Optional. If you enter a URL here, you will be taken to that URL each time you log in. For example, to be taken to the most recent additions enter bgimage/recent');
  t('Public e-mail address');
  t('Show me Guide breadcrumbs using');
  t('The collection of data at BugGuide is very useful. For example, a researcher may want to use BugGuide observations to plot the spread of a species over time. We would very much like to include 

data that you submit in the BugGuide data set. Your images will never be published without your permission, just included in scientific analyses. However, if you do not want your submissions included, you may uncheck this box.');
  t('Where you live. This information is optional but it allows us to create this interesting <a href="">map of BugGuide users</a>. By default only state and country are shown publicly. If you want to contribute to the map but not show any location information publicly check the Do not share publicly box.');

  return $field_instances;
}
