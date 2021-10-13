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

  // Exported field_instance: 'node-bgimage-body'.
  $field_instances['node-bgimage-body'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, sex of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).',
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
        'weight' => 40,
      ),
      'recent' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 31,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Remarks',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          'xbbcode' => 'xbbcode',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            1 => array(
              'weight' => -10,
            ),
            2 => array(
              'weight' => -9,
            ),
            3 => array(
              'weight' => 0,
            ),
            4 => array(
              'weight' => 1,
            ),
            'xbbcode' => array(
              'weight' => -6,
            ),
          ),
        ),
      ),
      'display_summary' => 0,
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
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_base'.
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
        'weight' => 41,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 33,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
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
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_copyright_owner'.
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
        'weight' => 40,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 35,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 35,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 40,
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

  // Exported field_instance: 'node-bgimage-field_bgimage_county'.
  $field_instances['node-bgimage-field_bgimage_county'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
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

  // Exported field_instance: 'node-bgimage-field_bgimage_date'.
  $field_instances['node-bgimage-field_bgimage_date'] = array(
    'bundle' => 'bgimage',
    'deleted' => 0,
    'description' => 'Date taken, if known (mm/dd/yy). Only specify this for wild specimens.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'bg_short_F_j_Y',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => FALSE,
        ),
        'type' => 'date_default',
        'weight' => 8,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
      ),
      'recent' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 33,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_date',
    'label' => 'Date taken',
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
        'input_format' => 'n/j/Y',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '1902:+0',
      ),
      'type' => 'date_popup',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_id'.
  $field_instances['node-bgimage-field_bgimage_id'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Optional. An identifier for your own use. If you choose something unique here from your own records, you can easily find this image later using search.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 38,
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
        'weight' => 32,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 38,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_id',
    'label' => 'Identifier',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          'xbbcode' => 'xbbcode',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            1 => array(
              'weight' => -10,
            ),
            2 => array(
              'weight' => -9,
            ),
            3 => array(
              'weight' => 0,
            ),
            4 => array(
              'weight' => 1,
            ),
            'xbbcode' => array(
              'weight' => -6,
            ),
          ),
        ),
      ),
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

  // Exported field_instance: 'node-bgimage-field_bgimage_image'.
  $field_instances['node-bgimage-field_bgimage_image'] = array(
    'bundle' => 'bgimage',
    'deleted' => 0,
    'description' => 'If you have more than one image of the <b>same specimen</b>, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.<br />',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'bgimage',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'bg_large',
        ),
        'type' => 'bgimage_conditional_link_formatter',
        'weight' => 0,
      ),
      'homepage' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'bg_large',
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
        'weight' => 0,
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_life_stage'.
  $field_instances['node-bgimage-field_bgimage_life_stage'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 10,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 39,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
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

  // Exported field_instance: 'node-bgimage-field_bgimage_location'.
  $field_instances['node-bgimage-field_bgimage_location'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'To narrow things down, you may optionally specify a city or other well known location. <b>Do not include the county, state, or province here</b>. Specify that above, except for captive specimens.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
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
        'weight' => 26,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_location',
    'label' => 'Location',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          'xbbcode' => 'xbbcode',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            1 => array(
              'weight' => -10,
            ),
            2 => array(
              'weight' => -9,
            ),
            3 => array(
              'weight' => 0,
            ),
            4 => array(
              'weight' => 1,
            ),
            'xbbcode' => array(
              'weight' => -6,
            ),
          ),
        ),
      ),
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

  // Exported field_instance: 'node-bgimage-field_bgimage_location_code'.
  $field_instances['node-bgimage-field_bgimage_location_code'] = array(
    'bundle' => 'bgimage',
    'default_value' => array(
      0 => array(
        'value' => 'ZZ',
      ),
    ),
    'deleted' => 0,
    'description' => '<strong>Note that we only accept images of specimens from the United States and Canada.</strong><br />To ensure the accuracy of our collection data, specify the state or province where the specimen was found. Range information is derived from this data, so only provide this for wild specimens.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 42,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_bgimage_location_code',
    'label' => 'State/Province',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_photo_quality'.
  $field_instances['node-bgimage-field_bgimage_photo_quality'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'fivestar',
        'settings' => array(
          'expose' => 1,
          'style' => 'average',
          'text' => 'average',
          'widget' => array(
            'fivestar_widget' => 'sites/all/modules/fivestar/widgets/outline/outline.css',
          ),
        ),
        'type' => 'fivestar_formatter_default',
        'weight' => 15,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
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
        'weight' => 32,
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
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-bgimage-field_bgimage_representative'.
  $field_instances['node-bgimage-field_bgimage_representative'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'fivestar',
        'settings' => array(
          'expose' => 1,
          'style' => 'average',
          'text' => 'average',
          'widget' => array(
            'fivestar_widget' => 'sites/all/modules/fivestar/widgets/outline/outline.css',
          ),
        ),
        'type' => 'fivestar_formatter_default',
        'weight' => 14,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 39,
      ),
      'recent' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 31,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_representative',
    'label' => 'Representative of Taxon',
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

  // Exported field_instance: 'node-bgimage-field_bgimage_sex'.
  $field_instances['node-bgimage-field_bgimage_sex'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 11,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 32,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 38,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 39,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_sex',
    'label' => 'Sex',
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

  // Exported field_instance: 'node-bgimage-field_bgimage_size'.
  $field_instances['node-bgimage-field_bgimage_size'] = array(
    'bundle' => 'bgimage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Size, if known.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 12,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 38,
      ),
      'recent' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 35,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bgimage_size',
    'label' => 'Size',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          'xbbcode' => 'xbbcode',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            1 => array(
              'weight' => -10,
            ),
            2 => array(
              'weight' => -9,
            ),
            3 => array(
              'weight' => 0,
            ),
            4 => array(
              'weight' => 1,
            ),
            'xbbcode' => array(
              'weight' => -6,
            ),
          ),
        ),
      ),
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

  // Exported field_instance: 'node-bgimage-field_parent'.
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
        'weight' => 39,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
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
      'weight' => 14,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<b>Leave this blank if the image is your own</b>. If the image is not your own you must get permission from the owner before submitting it here. If you have permission, specify the copyright owner\'s name here.');
  t('<strong>Note that we only accept images of specimens from the United States and Canada.</strong><br />To ensure the accuracy of our collection data, specify the state or province where the specimen was found. Range information is derived from this data, so only provide this for wild specimens.');
  t('Base');
  t('Copyright Owner');
  t('County/Parish/District/Region');
  t('Date taken');
  t('Date taken, if known (mm/dd/yy). Only specify this for wild specimens.');
  t('Feel free to elaborate on this image or to share observations you made while taking it. You need not include a copyright notice, sex of the subject, or the scientific name; if appropriate, these will all appear automatically (check the preview).');
  t('Identifier');
  t('If known, otherwise leave blank. Do not include the word \'County\' or \'Parish\' here as the system will provide that as needed.');
  t('If you don\'t know for sure, don\'t check it. For example: for caterpillars check immature and for butterflies and moths check adult. If an image shows more than one life stage, check each one.');
  t('If you don\'t know for sure, don\'t check it. If the photo shows mating behavior, check both male and female.');
  t('If you have more than one image of the <b>same specimen</b>, submit this form first. Then view the first submitted image and select the "add image" link to add another. Please limit yourself to just a few of your best shots for a particular specimen.<br />');
  t('Image');
  t('Life stage');
  t('Location');
  t('State/Province');
  t('Optional. An identifier for your own use. If you choose something unique here from your own records, you can easily find this image later using search.');
  t('Parent');
  t('Photographic Quality');
  t('Remarks');
  t('Representative of Taxon');
  t('Sex');
  t('Size');
  t('Size, if known.');
  t('To narrow things down, you may optionally specify a city or other well known location. <b>Do not include the county, state, or province here</b>. Specify that above, except for captive specimens.');

  return $field_instances;
}
