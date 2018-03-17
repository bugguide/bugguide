<?php
/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\bgimage\v1_0\BgImage__0_1.
 */

namespace Drupal\bgapi\Plugin\resource\bgimage\v1_0;

use Drupal\restful\Plugin\resource\ResourceInterface;
use Drupal\restful\Plugin\resource\ResourceNode;

/**
 * Class BgImage
 * @package Drupal\bgapi\Plugin\resource\bgimage\v1_0
 *
 * @Resource(
 *   name = "bgimage:1.0",
 *   resource = "bgimage",
 *   label = "Images",
 *   description = "A RESTful service resource exposing bgimage nodes.",
 *   authenticationTypes = {
 *     "token"
 *   },
 *   authenticationOptional = FALSE,
 *   dataProvider = {
 *     "entityType": "node",
 *     "bundles": {
 *       "bgimage"
 *     },
 *   },
 *   majorVersion = 1,
 *   minorVersion = 0
 * )
 */
class BgImage__1_0 extends ResourceNode implements ResourceInterface {

  /**
   * Overrides ResourceEntity::publicFieldsInfo().
   */
  protected function publicFields() {
    $fields = parent::publicFields();

    $fields['owner'] = array(
      'property' => 'author',
      'sub_property' => 'uid',
    );

    $fields['image'] = array(
      'property' => 'field_bgimage_image',
    );

    return $fields;
  }
}
