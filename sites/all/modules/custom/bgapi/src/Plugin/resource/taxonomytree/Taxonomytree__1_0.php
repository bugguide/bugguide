<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\taxonomytree\Taxonomytree__1_0
 */

// built from https://github.com/RESTful-Drupal/restful/wiki/Look-up-a-URL-alias-mapping-with-DataProviderDbQuery 
//
// TODO this is not currently working. Not sure why. bgpage works fine:
//
//  curl https://beta.bugguide.net/api/v1.0/bgpage/60
//  {"data":[{"id":"60","self":"https:\/\/beta.bugguide.net\/api\/v1.0\/bgpage\/60","name":"Beetles","scientific_name":"Coleoptera"}],"self":{"title":"Self","href":"https:\/\/beta.bugguide.net\/api\/v1.0\/bgpage\/60"}}
//
// but
//
// curl https://beta.bugguide.net/api/v1.0/taxonomytree/60
// {"type":"http:\/\/www.w3.org\/Protocols\/rfc2616\/rfc2616-sec10.html#sec10.4.5","title":"Invalid URL path.","status":404,"detail":"Not Found"}
 
namespace Drupal\bgapi\Plugin\resource\taxonomytree;

use Drupal\restful\Plugin\resource\ResourceDbQuery;
use Drupal\restful\Plugin\resource\ResourceInterface;

/**
 * Class Taxonomytree__1_0
 * @package Drupal\bgapi\Plugin\resource\taxonomytree
 *
 * @Resource(
 *   name = "taxonomytree:1.0",
 *   resource = "taxonomytree",
 *   label = "Taxonomy Tree",
 *   description = "Gets the taxonomy tree for a BugGuide ID.",
 *   authenticationTypes = TRUE,
 *   authenticationOptional = TRUE,
 *   dataProvider = {
 *     "tableName": "field_data_field_parent",
 *     "idColumn": "alias",
 *     "primary": "entityid",
 *     "idField": "field_parent_value",
 *   },
 *   majorVersion = 1,
 *   minorVersion = 0,
 *   class = "Taxonomytree__1_0"
 * )
 */

class Taxonomytree__1_0 extends ResourceDbQuery implements ResourceInterface {

  /**
   * {@inheritdoc}
   */
  protected function publicFields() {
    $public_fields['entity_id'] = array(
      'property' => 'entityid'
    );
/**
    $public_fields['source'] = array(
      'property' => 'source'
    );

    $public_fields['alias'] = array(
      'property' => 'alias'
    );
*/
    return $public_fields;
  }
}