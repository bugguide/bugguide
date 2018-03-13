<?php

/**
 * @file
 * Install bgapi module.
 *
 * We install its dependencies first in order to avoid a bug
 * related with entity reference during install.
 * @see https://www.drupal.org/project/commerce_affiliate/issues/2383209
 */

module_enable(array('entityreference'));
_field_info_collate_types(TRUE);
module_enable(array('restful'));
module_enable(array('restful_token_auth'));
module_enable(array('bgapi'));
