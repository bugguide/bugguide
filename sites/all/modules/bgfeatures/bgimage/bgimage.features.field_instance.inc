<?php
/**
 * @file
 * bgimage.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function bgimage_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-image-field_bgimage_copyright_owner'
  $field_instances['node-image-field_bgimage_copyright_owner'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '<b>Leave this blank if the image is your own</b>. If the image is not your own you must get permission from the owner before submitting it here. If you have permission, specify the copyright owner\'s name here.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_copyright_owner',
    'label' => 'Copyright Owner',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_county'
  $field_instances['node-image-field_bgimage_county'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_county',
    'label' => 'County/Parish/District/Region',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_custom_tag'
  $field_instances['node-image-field_bgimage_custom_tag'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional. An identifier for your own use. If you choose something unique here from your own records, you can easily find this image later using search.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_custom_tag',
    'label' => 'Custom Tag',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_date'
  $field_instances['node-image-field_bgimage_date'] = array(
    'bundle' => 'image',
    'deleted' => 0,
    'description' => 'Date taken, if known (mm/dd/yy). Only specify this for wild specimens.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_date',
    'label' => 'Date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'j M Y - g:i:sa',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_gender'
  $field_instances['node-image-field_bgimage_gender'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_gender',
    'label' => 'Gender',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_image'
  $field_instances['node-image-field_bgimage_image'] = array(
    'bundle' => 'image',
    'deleted' => 0,
    'description' => 'If you have more than one image of the same specimen, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'image',
      'file_extensions' => 'jpg',
      'max_filesize' => '5 MB',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'medium',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_life_stage'
  $field_instances['node-image-field_bgimage_life_stage'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_life_stage',
    'label' => 'Life Stage',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_location'
  $field_instances['node-image-field_bgimage_location'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
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
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_location',
    'label' => 'Location',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(
          'CA' => 'CA',
          'US' => 'US',
        ),
        'default_country' => 'US',
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-postal-code' => 'address-hide-postal-code',
          'address-hide-street' => 'address-hide-street',
          'address-optional' => 'address-optional',
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_remarks'
  $field_instances['node-image-field_bgimage_remarks'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, gender of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_remarks',
    'label' => 'Remarks',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_representative'
  $field_instances['node-image-field_bgimage_representative'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'fivestar',
        'settings' => array(
          'expose' => TRUE,
          'style' => 'average',
          'text' => 'average',
          'widget' => array(
            'fivestar_widget' => NULL,
          ),
        ),
        'type' => 'fivestar_formatter_default',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_representative',
    'label' => 'Representative Images',
    'required' => 0,
    'settings' => array(
      'allow_clear' => 0,
      'allow_ownvote' => 1,
      'allow_revote' => 1,
      'stars' => 5,
      'target' => 'none',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'fivestar',
      'settings' => array(),
      'type' => 'exposed',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-image-field_bgimage_size'
  $field_instances['node-image-field_bgimage_size'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Size, if known, in millimeters.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_size',
    'label' => 'Size',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
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

  // Translatables
  // Included for use with string extractors like potx.
  t('<b>Leave this blank if the image is your own</b>. If the image is not your own you must get permission from the owner before submitting it here. If you have permission, specify the copyright owner\'s name here.');
  t('Copyright Owner');
  t('County/Parish/District/Region');
  t('Custom Tag');
  t('Date');
  t('Date taken, if known (mm/dd/yy). Only specify this for wild specimens.');
  t('Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, gender of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).');
  t('Gender');
  t('If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.');
  t('If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.');
  t('If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.');
  t('If you have more than one image of the same specimen, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.');
  t('Image');
  t('Life Stage');
  t('Location');
  t('Optional. An identifier for your own use. If you choose something unique here from your own records, you can easily find this image later using search.');
  t('Remarks');
  t('Representative Images');
  t('Size');
  t('Size, if known, in millimeters.');

  return $field_instances;
}
