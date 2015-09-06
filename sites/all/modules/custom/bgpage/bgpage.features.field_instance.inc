<?php
/**
 * @file
 * bgpage.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function bgpage_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-bgpage-body'
  $field_instances['node-bgpage-body'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'homepage' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'trim_length' => 600,
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
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
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_common_name'
  $field_instances['node-bgpage-field_common_name'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Try to find a unique common name. Otherwise use the scientific name for the taxon. If no common name is available for a species page, use the genus and species together, but do not capitalize the species. Preferred common name sources include:<br/><a href="http://www.entsoc.org/common-names" target="blank">ESA: Common Names of Insects &amp; Related Organisms</a><br/><a href="http://www.esc-sec.ca/commonnames.html" target="blank">ESC: Common Names of Insects in Canada</a><br/><a href="http://www.naba.org/pubs/enames.html" target="blank">NABA: English Names of North American Butterflies Occuring North of Mexico</a><br/><a href="http://www.pugetsound.edu/academics/academic-resources/slater-museum/biodiversity-resources/dragonflies/north-american-odonata/" target="blank">DSA: The Odonata of North America</a><br/><a href="http://www.americanarachnology.org/AAS_information.html" target="blank">AAS: Common and Scientific Names of Arachnids</a>',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
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
    'field_name' => 'field_common_name',
    'label' => 'Common Name',
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
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_counts'
  $field_instances['node-bgpage-field_counts'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Examples here might be number of orders, families, species and/or subspecies for particular regions (or worldwide). One count per line.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'homepage' => array(
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
    'field_name' => 'field_counts',
    'label' => 'Counts',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_editors'
  $field_instances['node-bgpage-field_editors'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 35,
      ),
      'homepage' => array(
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
    'field_name' => 'field_editors',
    'label' => 'Editors',
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
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_etymology'
  $field_instances['node-bgpage-field_etymology'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Notes on the meaning of the scientific and common names.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'homepage' => array(
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
    'field_name' => 'field_etymology',
    'label' => 'Explanation of Names',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 4,
      ),
      'type' => 'text_textarea',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_food'
  $field_instances['node-bgpage-field_food'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Indicate any particular food preferences. You may want to note different food requirements for larvae versus adults.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'homepage' => array(
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
    'field_name' => 'field_food',
    'label' => 'Food',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_habitat'
  $field_instances['node-bgpage-field_habitat'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where generally found. In or around water? In the ground? On trees or low bushes?',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
      'homepage' => array(
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
    'field_name' => 'field_habitat',
    'label' => 'Habitat',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_hodges_number'
  $field_instances['node-bgpage-field_hodges_number'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Only available for species of Lepidoptera.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'homepage' => array(
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
    'field_name' => 'field_hodges_number',
    'label' => 'Hodges Number',
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
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_id'
  $field_instances['node-bgpage-field_id'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Typical identification marks, especially diagnostic or distinguishing features. You may want to note variability or regional differences.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
      'homepage' => array(
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
    'field_name' => 'field_id',
    'label' => 'Identification',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 10,
      ),
      'type' => 'text_textarea',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_internet_references'
  $field_instances['node-bgpage-field_internet_references'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Notable references on the internet. Create links with HTML or BBCode, e.g., [url=http://www.bugguide.net]BugGuide.Net[/url]',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 16,
      ),
      'homepage' => array(
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
    'field_name' => 'field_internet_references',
    'label' => 'Internet References',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 6,
      ),
      'type' => 'text_textarea',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_life_cycle'
  $field_instances['node-bgpage-field_life_cycle'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Details about the various stages of development and information about reproduction.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 12,
      ),
      'homepage' => array(
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
    'field_name' => 'field_life_cycle',
    'label' => 'Life Cycle',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 4,
      ),
      'type' => 'text_textarea',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_location_codes'
  $field_instances['node-bgpage-field_location_codes'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
      ),
      'homepage' => array(
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
    'field_name' => 'field_location_codes',
    'label' => 'Location Codes',
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
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_other_common_names'
  $field_instances['node-bgpage-field_other_common_names'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Additional common names; one per line. Note that larvae sometimes have different common names than adults.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'homepage' => array(
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
    'field_name' => 'field_other_common_names',
    'label' => 'Other common names',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_parent'
  $field_instances['node-bgpage-field_parent'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
      ),
      'homepage' => array(
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
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_print_references'
  $field_instances['node-bgpage-field_print_references'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Notable references in print. Use citations as explained above for publication information to appear in a Works Cited section.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 15,
      ),
      'homepage' => array(
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
    'field_name' => 'field_print_references',
    'label' => 'Print References',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 6,
      ),
      'type' => 'text_textarea',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_pronunciation'
  $field_instances['node-bgpage-field_pronunciation'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'A simple guide to pronunciation showing syllables and emphasis. For example, lepidoptera might be leh-pih-DOP-ter-ra. Particularly useful for scientific names and those with unexpected pronunciations.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
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
    'field_name' => 'field_pronunciation',
    'label' => 'Pronunciation',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_range'
  $field_instances['node-bgpage-field_range'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Just a simple and general text description of the limits of the range.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'homepage' => array(
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
    'field_name' => 'field_range',
    'label' => 'Range',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_remarks'
  $field_instances['node-bgpage-field_remarks'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Any general remarks or notes of interest.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'homepage' => array(
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
    'field_name' => 'field_remarks',
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
        'rows' => 15,
      ),
      'type' => 'text_textarea',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_representative_images'
  $field_instances['node-bgpage-field_representative_images'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'It is probably best to leave this blank and let the system randomly choose from among all images marked as representative. If you want to eliminate a particular image just edit the image and uncheck representative. This will be most useful for guide pages high up in the taxonomy. In that case we may wish to select the most common representatives from the multitude of candidates. To specify, enter the image node numbers in a comma delimited list (e.g., 5234,1243,4534).',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
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
    'field_name' => 'field_representative_images',
    'label' => 'Representative Images',
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

  // Exported field_instance: 'node-bgpage-field_scientific_name'
  $field_instances['node-bgpage-field_scientific_name'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
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
    'field_name' => 'field_scientific_name',
    'label' => 'Scientific Name',
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

  // Exported field_instance: 'node-bgpage-field_season'
  $field_instances['node-bgpage-field_season'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'When typically found. For butterflies, moths, and dragonflies, when do they fly? You may want to note separately when the larvae are found (caterpillars, for example).',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 10,
      ),
      'homepage' => array(
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
    'field_name' => 'field_season',
    'label' => 'Season',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_see_also'
  $field_instances['node-bgpage-field_see_also'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Similar creatures or those easily confused with or having a significant relationship to this one. Consider providing links to other guide pages.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 14,
      ),
      'homepage' => array(
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
    'field_name' => 'field_see_also',
    'label' => 'See also',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 4,
      ),
      'type' => 'text_textarea',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_size'
  $field_instances['node-bgpage-field_size'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Typical specimen dimensions may be specified here. Metric is preferred, but English units may additionally be specified. Be sure to indicate what the measure applies to (wingspan, perhaps, or body length). It may also be appropriate to include sizes for larvae (caterpillars, for example).',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'homepage' => array(
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
    'field_name' => 'field_size',
    'label' => 'Size',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_synonyms'
  $field_instances['node-bgpage-field_synonyms'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Classification changes can be noted here.',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'homepage' => array(
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
    'field_name' => 'field_synonyms',
    'label' => 'Synonyms and other taxonomic changes',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-bgpage-field_taxon'
  $field_instances['node-bgpage-field_taxon'] = array(
    'bundle' => 'bgpage',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'browse' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
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
    'field_name' => 'field_taxon',
    'label' => 'Taxon',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 21,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A simple guide to pronunciation showing syllables and emphasis. For example, lepidoptera might be leh-pih-DOP-ter-ra. Particularly useful for scientific names and those with unexpected pronunciations.');
  t('Additional common names; one per line. Note that larvae sometimes have different common names than adults.');
  t('Any general remarks or notes of interest.');
  t('Body');
  t('Classification changes can be noted here.');
  t('Common Name');
  t('Counts');
  t('Details about the various stages of development and information about reproduction.');
  t('Editors');
  t('Examples here might be number of orders, families, species and/or subspecies for particular regions (or worldwide). One count per line.');
  t('Explanation of Names');
  t('Food');
  t('Habitat');
  t('Hodges Number');
  t('Identification');
  t('Indicate any particular food preferences. You may want to note different food requirements for larvae versus adults.');
  t('Internet References');
  t('It is probably best to leave this blank and let the system randomly choose from among all images marked as representative. If you want to eliminate a particular image just edit the image and uncheck representative. This will be most useful for guide pages high up in the taxonomy. In that case we may wish to select the most common representatives from the multitude of candidates. To specify, enter the image node numbers in a comma delimited list (e.g., 5234,1243,4534).');
  t('Just a simple and general text description of the limits of the range.');
  t('Life Cycle');
  t('Location Codes');
  t('Notable references in print. Use citations as explained above for publication information to appear in a Works Cited section.');
  t('Notable references on the internet. Create links with HTML or BBCode, e.g., [url=http://www.bugguide.net]BugGuide.Net[/url]');
  t('Notes on the meaning of the scientific and common names.');
  t('Only available for species of Lepidoptera.');
  t('Other common names');
  t('Parent');
  t('Print References');
  t('Pronunciation');
  t('Range');
  t('Remarks');
  t('Representative Images');
  t('Scientific Name');
  t('Season');
  t('See also');
  t('Similar creatures or those easily confused with or having a significant relationship to this one. Consider providing links to other guide pages.');
  t('Size');
  t('Synonyms and other taxonomic changes');
  t('Taxon');
  t('Try to find a unique common name. Otherwise use the scientific name for the taxon. If no common name is available for a species page, use the genus and species together, but do not capitalize the species. Preferred common name sources include:<br/><a href="http://www.entsoc.org/common-names" target="blank">ESA: Common Names of Insects &amp; Related Organisms</a><br/><a href="http://www.esc-sec.ca/commonnames.html" target="blank">ESC: Common Names of Insects in Canada</a><br/><a href="http://www.naba.org/pubs/enames.html" target="blank">NABA: English Names of North American Butterflies Occuring North of Mexico</a><br/><a href="http://www.pugetsound.edu/academics/academic-resources/slater-museum/biodiversity-resources/dragonflies/north-american-odonata/" target="blank">DSA: The Odonata of North America</a><br/><a href="http://www.americanarachnology.org/AAS_information.html" target="blank">AAS: Common and Scientific Names of Arachnids</a>');
  t('Typical identification marks, especially diagnostic or distinguishing features. You may want to note variability or regional differences.');
  t('Typical specimen dimensions may be specified here. Metric is preferred, but English units may additionally be specified. Be sure to indicate what the measure applies to (wingspan, perhaps, or body length). It may also be appropriate to include sizes for larvae (caterpillars, for example).');
  t('When typically found. For butterflies, moths, and dragonflies, when do they fly? You may want to note separately when the larvae are found (caterpillars, for example).');
  t('Where generally found. In or around water? In the ground? On trees or low bushes?');

  return $field_instances;
}
