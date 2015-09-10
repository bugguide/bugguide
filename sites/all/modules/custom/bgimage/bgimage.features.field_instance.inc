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

  // Exported field_instance: 'node-bgimage-body'
  $field_instances['node-bgimage-body'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, gender of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'recent' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Remarks',
    'required' => 0,
    'settings' => array(
      'display_summary' => 1,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_base'
  $field_instances['node-bgimage-field_bgimage_base'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 31,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 20,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_base',
    'label' => 'Base',
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
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_copyright_owner'
  $field_instances['node-bgimage-field_bgimage_copyright_owner'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '<b>Leave this blank if the image is your own</b>. If the image is not your own you must get permission from the owner before submitting it here. If you have permission, specify the copyright owner\'s name here.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
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

  // Exported field_instance: 'node-bgimage-field_bgimage_county'
  $field_instances['node-bgimage-field_bgimage_county'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 32,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 31,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
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
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_date'
  $field_instances['node-bgimage-field_bgimage_date'] = array(
    'bundle' => 'bgimage',
    'deleted' => 0,
    'description' => 'Date taken, if known (mm/dd/yy). Only specify this for wild specimens.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'bg_short_F_j_Y',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 7,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
      'recent' => array(
        'label' => 'hidden',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'bg_short_F_j_Y',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_date',
    'label' => 'Date taken',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
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
      'type' => 'date_popup',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_gender'
  $field_instances['node-bgimage-field_bgimage_gender'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 33,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 32,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
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

  // Exported field_instance: 'node-bgimage-field_bgimage_id'
  $field_instances['node-bgimage-field_bgimage_id'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_id',
    'label' => 'ID',
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

  // Exported field_instance: 'node-bgimage-field_bgimage_image'
  $field_instances['node-bgimage-field_bgimage_image'] = array(
    'bundle' => 'bgimage',
    'deleted' => 0,
    'description' => 'If you have more than one image of the same specimen, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.
',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'bg_large',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
      'homepage' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'bg_small',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'recent' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'bg_small',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'bg_small',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_image',
    'label' => 'Image',
    'required' => 1,
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
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_life_stage'
  $field_instances['node-bgimage-field_bgimage_life_stage'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 33,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 21,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_life_stage',
    'label' => 'Life stage',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_location'
  $field_instances['node-bgimage-field_bgimage_location'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 19,
      ),
      'recent' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_location',
    'label' => 'Location',
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

  // Exported field_instance: 'node-bgimage-field_bgimage_location_code'
  $field_instances['node-bgimage-field_bgimage_location_code'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 21,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_location_code',
    'label' => 'Location code',
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
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_photo_quality'
  $field_instances['node-bgimage-field_bgimage_photo_quality'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Quality of image.<br>1: blurry, taken on a cheap camera phone;<br>5: professional-quality image, great depth of field, excellent lighting.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_photo_quality',
    'label' => 'Photographic Quality',
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
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_representative'
  $field_instances['node-bgimage-field_bgimage_representative'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'How representative of this taxon is this specimen?<br>1: can hardly recognize it as a member of this taxon;<br>5: I would show someone this picture to introduce them to this taxon',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'fivestar',
        'settings' => array(
          'expose' => 1,
          'style' => 'average',
          'text' => 'average',
          'widget' => array(
            'fivestar_widget' => 'default',
          ),
        ),
        'type' => 'fivestar_formatter_default',
        'weight' => 1,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'recent' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_representative',
    'label' => 'Representative Image',
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
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_size'
  $field_instances['node-bgimage-field_bgimage_size'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'recent' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 19,
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_parent'
  $field_instances['node-bgimage-field_parent'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 20,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_parent',
    'label' => 'Parent',
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

  // Translatables
  // Included for use with string extractors like potx.
  t('<b>Leave this blank if the image is your own</b>. If the image is not your own you must get permission from the owner before submitting it here. If you have permission, specify the copyright owner\'s name here.');
  t('Base');
  t('Copyright Owner');
  t('County/Parish/District/Region');
  t('Date taken');
  t('Date taken, if known (mm/dd/yy). Only specify this for wild specimens.');
  t('Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, gender of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).');
  t('Gender');
  t('How representative of this taxon is this specimen?<br>1: can hardly recognize it as a member of this taxon;<br>5: I would show someone this picture to introduce them to this taxon');
  t('ID');
  t('If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.');
  t('If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.');
  t('If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.');
  t('If you have more than one image of the same specimen, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.
');
  t('Image');
  t('Life stage');
  t('Location');
  t('Location code');
  t('Parent');
  t('Photographic Quality');
  t('Quality of image.<br>1: blurry, taken on a cheap camera phone;<br>5: professional-quality image, great depth of field, excellent lighting.');
  t('Remarks');
  t('Representative Image');
  t('Size');

  return $field_instances;
}
