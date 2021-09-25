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

  // Exported field_instance: 'user-user-field_email'.
  $field_instances['user-user-field_email'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional email address for others to see. You may wish to modify it in an obvious way to avoid spam (for example, me_NO_SPAM@example.com).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email',
    'label' => 'Public e-mail address',
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
      'weight' => -6,
    ),
  );

  // Exported field_instance: 'user-user-field_user_bg_homepage'.
  $field_instances['user-user-field_user_bg_homepage'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional. If you enter a URL here, you will be taken to that URL each time you log in. For example, to be taken to the most recent additions enter bgimage/recent',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
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
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'user-user-field_user_biography'.
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
        'weight' => 5,
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
      'weight' => -2,
    ),
  );

  // Exported field_instance: 'user-user-field_user_breadcrumb_format'.
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
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
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
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'user-user-field_user_city_state_country'.
  $field_instances['user-user-field_user_city_state_country'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Care to share where you live?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_city_state_country',
    'label' => 'City, state, country',
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
      'weight' => -3,
    ),
  );

  // Exported field_instance: 'user-user-field_user_contact_info'.
  $field_instances['user-user-field_user_contact_info'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'You may provide additional contact details if, for example, someone wants to license an image you have contributed.',
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
    'field_name' => 'field_user_contact_info',
    'label' => 'Contact Information',
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
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'user-user-field_user_content_license'.
  $field_instances['user-user-field_user_content_license'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 'CC_BY_NC_SA',
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
        'weight' => 6,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_content_license',
    'label' => 'Contributed content license terms',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => -1,
    ),
  );

  // Exported field_instance: 'user-user-field_user_content_license_add'.
  $field_instances['user-user-field_user_content_license_add'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you chose Custom license terms, provide more specific license information here.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_content_license_add',
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
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'user-user-field_user_default_county'.
  $field_instances['user-user-field_user_default_county'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Image submissions will use this by default.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_default_county',
    'label' => 'Default County/Parish/District/Region',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'user-user-field_user_default_location_code'.
  $field_instances['user-user-field_user_default_location_code'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Image submissions will use this by default.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_default_location_code',
    'label' => 'Default State/Province',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'user-user-field_user_full_name'.
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
      'weight' => -7,
    ),
  );

  // Exported field_instance: 'user-user-field_user_homepage'.
  $field_instances['user-user-field_user_homepage'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional URL of your home page on the internet.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(
          'custom_title' => '',
        ),
        'type' => 'link_url',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_homepage',
    'label' => 'Homepage',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 0,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'convert_aliases' => 0,
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 0,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_allowed_values' => '',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => 0,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => -5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional license information');
  t('Biography');
  t('BugGuide Homepage');
  t('Care to share where you live?');
  t('City, state, country');
  t('Contact Information');
  t('Contributed content license terms');
  t('Default County/Parish/District/Region');
  t('Default State/Province');
  t('Full Name');
  t('Homepage');
  t('If you chose Custom license terms, provide more specific license information here.');
  t('If you wish, tell others a little bit about yourself.');
  t('Image submissions will use this by default.');
  t('Optional URL of your home page on the internet.');
  t('Optional email address for others to see. You may wish to modify it in an obvious way to avoid spam (for example, me_NO_SPAM@example.com).');
  t('Optional full name for others to see. If you leave this blank, your username will be used instead.');
  t('Optional. If you enter a URL here, you will be taken to that URL each time you log in. For example, to be taken to the most recent additions enter bgimage/recent');
  t('Public e-mail address');
  t('Show me Guide breadcrumbs using');
  t('You may provide additional contact details if, for example, someone wants to license an image you have contributed.');

  return $field_instances;
}
