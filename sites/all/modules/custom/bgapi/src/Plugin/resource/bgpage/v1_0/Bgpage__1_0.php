<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\bgpage\v1_0\Bgpage__1_0
 */

namespace Drupal\bgapi\Plugin\resource\bgpage\v1_0;


use Drupal\restful\Plugin\resource\ResourceEntity;

/**
 * Class Bgpage__1_0
 * @package Drupal\bgapi\Plugin\resource\bgpag\v1_0
 *
 * @Resource(
 *   name = "bgpage:1.0",
 *   resource = "bgpage",
 *   label = "Guide Page",
 *   description = "Export the Guide Pages with all authentication providers.",
 *   authenticationTypes = TRUE,
 *   authenticationOptional = TRUE,
 *   dataProvider = {
 *     "entityType": "node",
 *     "bundles": {
 *       "bgpage"
 *     },
 *   },
 *   majorVersion = 1,
 *   minorVersion = 0
 * )
 */
class Bgpage__1_0 extends ResourceEntity
{
    /**
     * @inheritdoc
     */
    protected function publicFields()
    {
        $public_fields = parent::publicFields();
        $public_fields['name'] = $public_fields['label'];
        unset($public_fields['label']);

        $public_fields['id']['methods'] = array('GET');

        $public_fields['scientific_name'] = array(
            'property' => 'field_scientific_name'
        );

        return $public_fields;
    }

}
