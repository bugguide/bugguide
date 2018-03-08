<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\bgimage_search\v1_0\BgImageSearch.
 */

namespace Drupal\bgapi\Plugin\resource\bgimage_search\v1_0;
use Drupal\restful\Plugin\resource\ResourceInterface;
use Drupal\restful\Plugin\resource\Resource;

/**
 * Class BgImageSearch
 * @package Drupal\bgapi\Plugin\resource\bgimage_search\v1_0
 *
 * @Resource(
 *   name = "bgimage_search:1.0",
 *   resource = "bgimage_search",
 *   label = "BgImage Search",
 *   description = "Provides basic info doing Search API searches.",
 *   renderCache = {
 *     "render": FALSE,
 *   },
 *   dataProvider = {
 *     "idField": "entity_id",
 *   },
 *   authenticationTypes = {
 *     "token"
 *   },
 *   authenticationOptional = FALSE,
 *   majorVersion = 1,
 *   minorVersion = 0
 * )
 */
class BgImageSearch__1_0 extends Resource implements ResourceInterface {

  /**
   * {@inheritdoc}
   */
  protected function dataProviderClassName() {
    return '\\Drupal\\bgapi\\Plugin\\resource\\DataProvider\\DataProviderApacheSolr';
  }

  /**
   * Overrides Resource::publicFields().
   */
  public function publicFields() {
    return array(
      'entity_id' => array(
        'property' => 'entity_id',
        'process_callbacks' => array(
          'intVal',
        ),
      ),
      'label' => array(
        'property' => 'label',
      ),
      'url' => array(
        'property' => 'url',
      ),
    );
  }

}
