<?php

/**
 * @file
 * Definition of bgimage_handler_immediate_parent.
 */

/**
 * Renders the immediate parent as a link.
 */
class bgimage_handler_immediate_parent extends views_handler_field {

  /**
   * Add some required fields needed on render().
   */
  function construct() {
    parent::construct();
    $this->additional_fields['field_parent'] = array(
      'table' => 'field_data_field_parent',
      'field' => 'field_parent_value',
    );
  }

  /**
   * Loads additional fields.
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Extracts the immediate parent and renders a link to it.
   */
  function render($values) {
    $parents = $this->get_value($values, 'field_parent');
    // TODO refactor bg_get_parent_nid() so it can be used here.
    if (empty($parents)) {
      return;
    }

    $parents = explode(',', $parents);
    $nid = end($parents);
    $bgpage = node_load($nid);
    if (empty($bgpage)) {
      return;
    }

    return l($bgpage->title, 'node/' . $bgpage->nid);
  }
}
