<?php

/**
 * This class extends the standard string handler to provide special
 * behavior on the Parent exposed filters.
 * 
 * The search needs to search for all children. So parent 
 * 3,878075,52,77
 * is the dragonflies and a query needs to get all nodes with parent
 * REGEX ^3,878075,52,77,
 *
 */

class views_handler_filter_parent extends views_handler_filter_string {
  
/*
// op_starts might be useful someday, but right now we are just using
// op_equal.

  function op_starts($field) {
    // 1. A38377 -- group and ID together    
    if (ctype_alpha(substr($this->value, 0, 1))) {
      $field = 'field_data_field_groupandid.field_groupandid_value'; 
    }
    // 2. 1A38377 -- FY and group and ID together
    if (ctype_alpha(substr($this->value, 1, 1))) {
      $field = 'field_data_field_fy_groupandid.field_fy_groupandid_value';
    }
    
    $this->query->add_field($field);
    $this->query->add_where($this->options['group'], $field, db_like($this->value) . '%', 'LIKE');
  }
*/
  $foo = 'bar';
  
  function op_equal($field) {
    // Special handling for parent field.
    if ($field == 'field_data_field_parent.field_parent_value') {
       
      $this->query->add_where($this->options['group'], $field, db_like($this->value) . ',%', 'LIKE');   
    }
    else {
      // Original code.
      $this->query->add_where($this->options['group'], $field, $this->value, $this->operator());
    }
  }
}