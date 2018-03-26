<?php

/**
 * @file
 * Definition of bgimage_handler_filter_hide_images.
 */

/**
 * Hides the images column.
 */
class bgimage_handler_filter_hide_images extends views_handler_filter_boolean_operator {

  /**
   * Hide the images column if the filter was activated.
   */
  public function query() {
    if (!empty($this->value)) {
      $this->view->field['field_bgimage_image']->options['exclude'] = TRUE;
    }
  }

}
