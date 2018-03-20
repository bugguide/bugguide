<?php
/**
 * @file
 * bgimage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function bgimage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home';
  $page->task = 'page';
  $page->admin_title = 'Home';
  $page->admin_description = '';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_home__panel';
  $handler->task = 'page';
  $handler->subtask = 'home';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'bgmegapanels';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top_full' => NULL,
      'top_grow_first' => NULL,
      'top_1' => NULL,
      'top_2' => NULL,
      'top_3' => NULL,
      'top_4' => NULL,
      'top_grow_last' => NULL,
      'middle_grow_first' => NULL,
      'middle_1' => NULL,
      'middle_2' => NULL,
      'middle_3' => NULL,
      'middle_4' => NULL,
      'middle_grow_last' => NULL,
      'bottom_grow_first' => NULL,
      'bottom_1' => NULL,
      'bottom_2' => NULL,
      'bottom_3' => NULL,
      'bottom_4' => NULL,
      'bottom_grow_last' => NULL,
      'bottom_full' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '30f4ae23-7383-4d00-accb-1ca7bb90ab7d';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_home__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-8904bf34-4aa2-4fee-8963-1967315a418a';
  $pane->panel = 'top_grow_first';
  $pane->type = 'block';
  $pane->subtype = 'views-recent_images-block';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '8904bf34-4aa2-4fee-8963-1967315a418a';
  $display->content['new-8904bf34-4aa2-4fee-8963-1967315a418a'] = $pane;
  $display->panels['top_grow_first'][0] = 'new-8904bf34-4aa2-4fee-8963-1967315a418a';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-8904bf34-4aa2-4fee-8963-1967315a418a';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home'] = $page;

  return $pages;

}
