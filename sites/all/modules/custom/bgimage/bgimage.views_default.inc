<?php
/**
 * @file
 * bgimage.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bgimage_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'advanced_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Advanced search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Advanced search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 1,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any criterion and click on Apply to see results',
          'format' => 'f',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'pager' => array(
      'bef_format' => 'default',
      'is_secondary' => 0,
    ),
    'field_bgimage_location_code_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_bgimage_county_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_bgimage_location_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'uid' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'parent_ancestor' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'body_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_bgimage_sex_value' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_bgimage_life_stage_value' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'species_level' => array(
      'bef_format' => 'bef_single',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'hide_images' => array(
      'bef_format' => 'bef_single',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'month' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_bgimage_date_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
        'datepicker_options' => '',
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '25, 50, 100, 250, 500';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_bgimage_image' => 'field_bgimage_image',
    'nid' => 'nid',
    'title' => 'title',
    'field_bgimage_date' => 'field_bgimage_date',
    'field_bgimage_county' => 'field_bgimage_county',
    'field_bgimage_location' => 'field_bgimage_location',
    'field_bgimage_location_code' => 'field_bgimage_location_code',
    'immediate_parent' => 'immediate_parent',
  );
  $handler->display->display_options['style_options']['default'] = 'field_bgimage_date';
  $handler->display->display_options['style_options']['info'] = array(
    'field_bgimage_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bgimage_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bgimage_county' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bgimage_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bgimage_location_code' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'immediate_parent' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '@total Results';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_bgimage_image']['id'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['table'] = 'field_data_field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['field'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bgimage_image']['settings'] = array(
    'image_style' => 'bg_small',
    'image_link' => '',
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'ID';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date taken */
  $handler->display->display_options['fields']['field_bgimage_date']['id'] = 'field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['table'] = 'field_data_field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['field'] = 'field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => 'm-d-Y',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: County/Parish/District/Region */
  $handler->display->display_options['fields']['field_bgimage_county']['id'] = 'field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['table'] = 'field_data_field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['field'] = 'field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['label'] = 'County';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_bgimage_location']['id'] = 'field_bgimage_location';
  $handler->display->display_options['fields']['field_bgimage_location']['table'] = 'field_data_field_bgimage_location';
  $handler->display->display_options['fields']['field_bgimage_location']['field'] = 'field_bgimage_location';
  /* Field: Content: Location code */
  $handler->display->display_options['fields']['field_bgimage_location_code']['id'] = 'field_bgimage_location_code';
  $handler->display->display_options['fields']['field_bgimage_location_code']['table'] = 'field_data_field_bgimage_location_code';
  $handler->display->display_options['fields']['field_bgimage_location_code']['field'] = 'field_bgimage_location_code';
  $handler->display->display_options['fields']['field_bgimage_location_code']['label'] = 'State';
  /* Field: Content: Immediate parent */
  $handler->display->display_options['fields']['immediate_parent']['id'] = 'immediate_parent';
  $handler->display->display_options['fields']['immediate_parent']['table'] = 'field_data_field_parent';
  $handler->display->display_options['fields']['immediate_parent']['field'] = 'immediate_parent';
  $handler->display->display_options['fields']['immediate_parent']['label'] = 'Guide Placement';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bgimage' => 'bgimage',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Location code (field_bgimage_location_code) */
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['id'] = 'field_bgimage_location_code_value';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['table'] = 'field_data_field_bgimage_location_code';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['field'] = 'field_bgimage_location_code_value';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['group'] = 1;
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['operator_id'] = 'field_bgimage_location_code_value_op';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['label'] = 'State or Province';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['description'] = 'E.g., NY';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['operator'] = 'field_bgimage_location_code_value_op';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['identifier'] = 'field_bgimage_location_code_value';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['group_info']['label'] = 'Location code (field_bgimage_location_code)';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['group_info']['identifier'] = 'field_bgimage_location_code_value';
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_bgimage_location_code_value']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: County/Parish/District/Region (field_bgimage_county) */
  $handler->display->display_options['filters']['field_bgimage_county_value']['id'] = 'field_bgimage_county_value';
  $handler->display->display_options['filters']['field_bgimage_county_value']['table'] = 'field_data_field_bgimage_county';
  $handler->display->display_options['filters']['field_bgimage_county_value']['field'] = 'field_bgimage_county_value';
  $handler->display->display_options['filters']['field_bgimage_county_value']['group'] = 1;
  $handler->display->display_options['filters']['field_bgimage_county_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['operator_id'] = 'field_bgimage_county_value_op';
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['label'] = 'County/Parish';
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['operator'] = 'field_bgimage_county_value_op';
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['identifier'] = 'field_bgimage_county_value';
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_county_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Location (field_bgimage_location) */
  $handler->display->display_options['filters']['field_bgimage_location_value']['id'] = 'field_bgimage_location_value';
  $handler->display->display_options['filters']['field_bgimage_location_value']['table'] = 'field_data_field_bgimage_location';
  $handler->display->display_options['filters']['field_bgimage_location_value']['field'] = 'field_bgimage_location_value';
  $handler->display->display_options['filters']['field_bgimage_location_value']['group'] = 1;
  $handler->display->display_options['filters']['field_bgimage_location_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['operator_id'] = 'field_bgimage_location_value_op';
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['description'] = 'E.g., Chattahoochee';
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['operator'] = 'field_bgimage_location_value_op';
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['identifier'] = 'field_bgimage_location_value';
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_location_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Author uid */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'node';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Contributor';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Parent ancestor */
  $handler->display->display_options['filters']['parent_ancestor']['id'] = 'parent_ancestor';
  $handler->display->display_options['filters']['parent_ancestor']['table'] = 'field_data_field_parent';
  $handler->display->display_options['filters']['parent_ancestor']['field'] = 'parent_ancestor';
  $handler->display->display_options['filters']['parent_ancestor']['operator'] = 'starts';
  $handler->display->display_options['filters']['parent_ancestor']['group'] = 1;
  $handler->display->display_options['filters']['parent_ancestor']['exposed'] = TRUE;
  $handler->display->display_options['filters']['parent_ancestor']['expose']['operator_id'] = 'parent_ancestor_op';
  $handler->display->display_options['filters']['parent_ancestor']['expose']['label'] = 'Taxon ID';
  $handler->display->display_options['filters']['parent_ancestor']['expose']['description'] = 'E.g., 191 for Odonata';
  $handler->display->display_options['filters']['parent_ancestor']['expose']['operator'] = 'parent_ancestor_op';
  $handler->display->display_options['filters']['parent_ancestor']['expose']['identifier'] = 'taxon';
  $handler->display->display_options['filters']['parent_ancestor']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Body (body) */
  $handler->display->display_options['filters']['body_value']['id'] = 'body_value';
  $handler->display->display_options['filters']['body_value']['table'] = 'field_data_body';
  $handler->display->display_options['filters']['body_value']['field'] = 'body_value';
  $handler->display->display_options['filters']['body_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['body_value']['group'] = 1;
  $handler->display->display_options['filters']['body_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['body_value']['expose']['operator_id'] = 'body_value_op';
  $handler->display->display_options['filters']['body_value']['expose']['label'] = 'Description';
  $handler->display->display_options['filters']['body_value']['expose']['operator'] = 'body_value_op';
  $handler->display->display_options['filters']['body_value']['expose']['identifier'] = 'body_value';
  $handler->display->display_options['filters']['body_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['body_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Sex (field_bgimage_sex) */
  $handler->display->display_options['filters']['field_bgimage_sex_value']['id'] = 'field_bgimage_sex_value';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['table'] = 'field_data_field_bgimage_sex';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['field'] = 'field_bgimage_sex_value';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['operator'] = 'and';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['group'] = 1;
  $handler->display->display_options['filters']['field_bgimage_sex_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['operator_id'] = 'field_bgimage_sex_value_op';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['label'] = 'Sex';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['operator'] = 'field_bgimage_sex_value_op';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['identifier'] = 'field_bgimage_sex_value';
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_sex_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Life stage (field_bgimage_life_stage) */
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['id'] = 'field_bgimage_life_stage_value';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['table'] = 'field_data_field_bgimage_life_stage';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['field'] = 'field_bgimage_life_stage_value';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['operator'] = 'and';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['group'] = 1;
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['operator_id'] = 'field_bgimage_life_stage_value_op';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['label'] = 'Life stage';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['operator'] = 'field_bgimage_life_stage_value_op';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['identifier'] = 'field_bgimage_life_stage_value';
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_life_stage_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Is not classified at species level */
  $handler->display->display_options['filters']['species_level']['id'] = 'species_level';
  $handler->display->display_options['filters']['species_level']['table'] = 'field_data_field_parent';
  $handler->display->display_options['filters']['species_level']['field'] = 'species_level';
  $handler->display->display_options['filters']['species_level']['value'] = '0';
  $handler->display->display_options['filters']['species_level']['exposed'] = TRUE;
  $handler->display->display_options['filters']['species_level']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['species_level']['expose']['label'] = 'Is not classified at species level';
  $handler->display->display_options['filters']['species_level']['expose']['operator'] = 'species_level_op';
  $handler->display->display_options['filters']['species_level']['expose']['identifier'] = 'species_level';
  $handler->display->display_options['filters']['species_level']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['species_level']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['species_level']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Hide images */
  $handler->display->display_options['filters']['hide_images']['id'] = 'hide_images';
  $handler->display->display_options['filters']['hide_images']['table'] = 'field_data_field_bgimage_image';
  $handler->display->display_options['filters']['hide_images']['field'] = 'hide_images';
  $handler->display->display_options['filters']['hide_images']['value'] = '0';
  $handler->display->display_options['filters']['hide_images']['exposed'] = TRUE;
  $handler->display->display_options['filters']['hide_images']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['hide_images']['expose']['label'] = 'Suppress thumbnail images';
  $handler->display->display_options['filters']['hide_images']['expose']['operator'] = 'hide_images_op';
  $handler->display->display_options['filters']['hide_images']['expose']['identifier'] = 'hide_images';
  $handler->display->display_options['filters']['hide_images']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['hide_images']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['hide_images']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Month taken */
  $handler->display->display_options['filters']['month']['id'] = 'month';
  $handler->display->display_options['filters']['month']['table'] = 'field_data_field_bgimage_date';
  $handler->display->display_options['filters']['month']['field'] = 'month';
  $handler->display->display_options['filters']['month']['exposed'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['month']['expose']['label'] = 'Month';
  $handler->display->display_options['filters']['month']['expose']['operator'] = 'month_op';
  $handler->display->display_options['filters']['month']['expose']['identifier'] = 'month';
  $handler->display->display_options['filters']['month']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Date taken (field_bgimage_date) */
  $handler->display->display_options['filters']['field_bgimage_date_value']['id'] = 'field_bgimage_date_value';
  $handler->display->display_options['filters']['field_bgimage_date_value']['table'] = 'field_data_field_bgimage_date';
  $handler->display->display_options['filters']['field_bgimage_date_value']['field'] = 'field_bgimage_date_value';
  $handler->display->display_options['filters']['field_bgimage_date_value']['operator'] = 'between';
  $handler->display->display_options['filters']['field_bgimage_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['operator_id'] = 'field_bgimage_date_value_op';
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['operator'] = 'field_bgimage_date_value_op';
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['identifier'] = 'field_bgimage_date_value';
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_bgimage_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    6 => 0,
    1 => 0,
    5 => 0,
    8 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_bgimage_date_value']['granularity'] = 'year';
  $handler->display->display_options['filters']['field_bgimage_date_value']['year_range'] = '-100:+0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'advanced-search';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_bgimage_image']['id'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['table'] = 'field_data_field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['field'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_bgimage_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bgimage_image']['settings'] = array(
    'image_style' => 'bg_small',
    'image_link' => '',
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'URL';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = 'https://bugguide.net/node/view/[nid]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date taken */
  $handler->display->display_options['fields']['field_bgimage_date']['id'] = 'field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['table'] = 'field_data_field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['field'] = 'field_bgimage_date';
  $handler->display->display_options['fields']['field_bgimage_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => 'm-d-Y',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: County/Parish/District/Region */
  $handler->display->display_options['fields']['field_bgimage_county']['id'] = 'field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['table'] = 'field_data_field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['field'] = 'field_bgimage_county';
  $handler->display->display_options['fields']['field_bgimage_county']['label'] = 'County';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_bgimage_location']['id'] = 'field_bgimage_location';
  $handler->display->display_options['fields']['field_bgimage_location']['table'] = 'field_data_field_bgimage_location';
  $handler->display->display_options['fields']['field_bgimage_location']['field'] = 'field_bgimage_location';
  /* Field: Content: Location code */
  $handler->display->display_options['fields']['field_bgimage_location_code']['id'] = 'field_bgimage_location_code';
  $handler->display->display_options['fields']['field_bgimage_location_code']['table'] = 'field_data_field_bgimage_location_code';
  $handler->display->display_options['fields']['field_bgimage_location_code']['field'] = 'field_bgimage_location_code';
  /* Field: Content: Immediate parent */
  $handler->display->display_options['fields']['immediate_parent']['id'] = 'immediate_parent';
  $handler->display->display_options['fields']['immediate_parent']['table'] = 'field_data_field_parent';
  $handler->display->display_options['fields']['immediate_parent']['field'] = 'immediate_parent';
  $handler->display->display_options['fields']['immediate_parent']['label'] = 'Guide Placement';
  $handler->display->display_options['path'] = 'export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';
  $export['advanced_search'] = $view;

  $view = new view();
  $view->name = 'featured_image';
  $view->description = 'View to create a welcome banner with featured image';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Featured Image';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Featured Image';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['label'] = 'Card Content';
  $handler->display->display_options['header']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['header']['area_text_custom']['content'] = '<h1>Welcome to BugGuide</h1>
<p>We are an online community of naturalists who enjoy learning about and sharing our observations of <strong>insect, spiders, and other related arthropods</strong>.</p>
<p>We enjoy the opportunity to instill in others the <strong>fascination and appreciation</strong> that we share for the intricate lives of these oft-maligned creatures.</p>';
  $handler->display->display_options['header']['area_text_custom']['tokenize'] = TRUE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['label'] = 'Get Started Button';
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<a href="/user" class="card-footer-item">Get Started <span class="icon"><span class="fa fa-arrow-right"></span></span></a>';
  /* Relationship: Content: Image (field_bgimage_image:fid) */
  $handler->display->display_options['relationships']['field_bgimage_image_fid']['id'] = 'field_bgimage_image_fid';
  $handler->display->display_options['relationships']['field_bgimage_image_fid']['table'] = 'field_data_field_bgimage_image';
  $handler->display->display_options['relationships']['field_bgimage_image_fid']['field'] = 'field_bgimage_image_fid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_bgimage_image']['id'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['table'] = 'field_data_field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['field'] = 'field_bgimage_image';
  $handler->display->display_options['fields']['field_bgimage_image']['label'] = '';
  $handler->display->display_options['fields']['field_bgimage_image']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bgimage_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_bgimage_image']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_bgimage_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bgimage_image']['empty'] = 'Blep';
  $handler->display->display_options['fields']['field_bgimage_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bgimage_image']['settings'] = array(
    'image_style' => '',
    'image_link' => 'file',
  );
  /* Field: File: Path */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['relationship'] = 'field_bgimage_image_fid';
  $handler->display->display_options['fields']['uri']['label'] = '';
  $handler->display->display_options['fields']['uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uri']['file_download_path'] = TRUE;
  /* Filter criterion: Content: Nid */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'node';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';
  $handler->display->display_options['filters']['nid']['value']['value'] = '1501655';
  $handler->display->display_options['filters']['nid']['group'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_description'] = 'Welcome Banner';
  $export['featured_image'] = $view;

  $view = new view();
  $view->name = 'recent_images';
  $view->description = 'Shows recently uploaded images';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Recent images';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent images';
  $handler->display->display_options['css_class'] = 'columns';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'column';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'columns mr-0 ml-0';
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['view_mode'] = 'homepage';
  $handler->display->display_options['row_options']['load_comments'] = 0;
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['delta_fieldset']['delta_fields'] = array();
  $handler->display->display_options['row_options']['grouping_fieldset']['group_field'] = 'node|created';
  $handler->display->display_options['row_options']['default_fieldset']['view_mode'] = 'homepage';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bgimage' => 'bgimage',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'More recent images';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'column is-one-quarter-desktop is-half-tablet is-half-mobile';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'columns is-mobile is-multiline';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['view_mode'] = 'homepage';
  $handler->display->display_options['row_options']['load_comments'] = 0;
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['delta_fieldset']['delta_fields'] = array();
  $handler->display->display_options['row_options']['grouping_fieldset']['group_field'] = 'node|created';
  $handler->display->display_options['row_options']['default_fieldset']['view_mode'] = 'homepage';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['label'] = 'More Link';
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<div class="has-text-right mt-2"><a href="/recent" class="button is-primary">More recently added images</a></div>';
  $handler->display->display_options['block_description'] = 'Recent images';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['view_mode'] = 'recent';
  $handler->display->display_options['row_options']['load_comments'] = 0;
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['delta_fieldset']['delta_fields'] = array();
  $handler->display->display_options['row_options']['grouping_fieldset']['group_field'] = 'node|created';
  $handler->display->display_options['row_options']['default_fieldset']['view_mode'] = 'recent';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'recent';
  $export['recent_images'] = $view;

  return $export;
}
