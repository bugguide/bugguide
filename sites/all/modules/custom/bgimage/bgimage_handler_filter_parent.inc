<?php

/**
 * @file
 * Definition of bgimage_filter_handler_parent.
 */

/**
 * Filters content whose parent is included in the parent tree.
 */
class bgimage_handler_filter_parent extends views_handler_filter_string {

  /**
   * Executes the query.
   *
   * @TODO refactor this logic along with bgref_views_query_alter and bglink_views_query_alter.
   */
  function query() {
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    // Load the bgpage node.
    $bgpage = node_load($this->value);
    if (empty($bgpage)) {
      return;
    }

    // Build the bgpage node's tree. Then add it as a condition.
    $parents = $bgpage->nid;
    if (!empty($bgpage->field_parent['und'][0]['value'])) {
      $parents = $bgpage->field_parent['und'][0]['value'] . ',' . $bgpage->nid;
    }

    $this->query->add_where($this->options['group'], db_or()
      ->condition($field, $parents, '=')
      ->condition($field, $parents . ',%', 'LIKE')
    );
  }

}
