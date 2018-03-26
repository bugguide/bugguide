<?php

/**
 * @file
 * Definition of bgimage_handler_filter_month.
 */

/**
 * Filters images by month.
 */
class bgimage_handler_filter_month extends views_handler_filter {

  /**
   * Show a select field with months.
   */
  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'select',
      '#title' => 'Month',
      '#options' => array(
        '1' => 'January',
        '2' => 'February',
        '3' => 'March',
        '4' => 'April',
        '5' => 'May',
        '6' => 'June',
        '7' => 'July',
        '8' => 'August',
        '9' => 'September',
        '10' => 'October',
        '11' => 'November',
        '12' => 'December',
      ),
      '#default_value' => $this->value,
    );
  }


  /**
   * Filter by month.
   */
  public function query() {
    if (empty($this->value)) {
      return;
    }

    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    $this->query->add_where_expression($this->options['group'], 'EXTRACT(MONTH FROM(' . $field . ')) = ' . $this->value[0]);
  }

}
