<?php

/**
 * @file
 * Definition of bgimage_handler_filter_species_level.
 */

/**
 * Filters images whose immediate parent is at the species level.
 */
class bgimage_handler_filter_species_level extends views_handler_filter_boolean_operator {

  /**
   * Executes the query.
   */
  function query() {
    if (empty($this->value)) {
      return;
    }

    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    $this->query->add_field(NULL,
      '(SELECT field_taxon_value FROM {field_data_field_taxon} WHERE entity_id=SUBSTRING_INDEX(' . $field . ',\',\',-1))',
      'taxon_id'
    );

    $this->query->add_having($this->options['group'], 'taxon_id', 3400, '<');
  }

}
