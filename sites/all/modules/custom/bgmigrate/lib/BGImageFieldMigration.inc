<?php
/**
 * @file
 * Migration class for bgimage nodes.
 */

class BGImageFieldMigration extends BasicBugGuideMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('BGImages');

    // Only update existing nodes; do not create new nodes. The definitive
    // node id is the one in the destination. Since we are migrating data from
    // a MySQL table into existing Drupal 7 nodes/fields, this makes sense.
    // https://www.drupal.org/node/1117454
    $this->systemOfRecord = Migration::DESTINATION;

    // You may optionally declare dependencies for your migration - other migrations
    // which should run first. In this case, terms assigned to our nodes and
    // the authors of the nodes should be migrated before the nodes themselves.
    //$this->dependencies = array('BeerTerm', 'BeerUser');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'BG Node ID.',
          'alias' => 'bgi',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = db_select('bgimage', 'bgi');
    $query->fields('bgi', array('nid', 'parent', 'base', 'id', 'location', 'size', 'date_taken', 'width', 'height', 'owner', 'county', 'location_code', 'male', 'female', 'adult', 'immature'));
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type bgimage
    $this->destination = new MigrateDestinationNode('bgimage');

    // Mapped fields
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('field_parent', 'parent');
    $this->addFieldMapping('field_bgimage_base', 'base');
    $this->addFieldMapping('field_bgimage_id', 'id');
    $this->addFieldMapping('field_bgimage_location', 'location');
    $this->addFieldMapping('field_bgimage_size', 'size');
    $this->addFieldMapping('field_bgimage_date', 'date_taken');
    $this->addFieldMapping('field_bgimage_copyright_owner', 'owner');
    $this->addFieldMapping('field_bgimage_county', 'county');
    $this->addFieldMapping('field_bgimage_location_code', 'location_code');
    $this->addFieldMapping('field_bgimage_sex', 'sex');
    $this->addFieldMapping('field_bgimage_life_stage', 'life_stage');


    $this->addUnmigratedDestinations(array(
      'title',
      'uid',
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'body',
      'body:summary',
      'body:format',
      'body:language',
      'comment',
      'field_bgimage_date:rrule',
      'field_bgimage_date:to',
      'field_bgimage_date:timezone',
      'field_bgimage_photo_quality',
      'field_bgimage_photo_quality:target',
      'field_bgimage_representative',
      'field_bgimage_representative:target',
      'field_bgimage_image',
      'field_bgimage_image:file_class',
      'field_bgimage_image:preserve_files',
      'field_bgimage_image:destination_dir',
      'field_bgimage_image:destination_file',
      'field_bgimage_image:file_replace',
      'field_bgimage_image:source_dir',
      'field_bgimage_image:urlencode',
      'field_bgimage_image:alt',
      'field_bgimage_image:title',
      'field_bgimage_image:width',
      'field_bgimage_image:height',
    ));
  }

  /**
   * Called from the source plugin upon first pulling the raw data from the source.
   */
  public function prepareRow($row) {
    // Prepare values for field_bgimage_sex.
    $row->sex = array();
    if ($row->female == 1) {
      $row->sex[] = 'female';
    }
    if ($row->male == 1) {
      $row->sex[] = 'male';
    }

    // Prepare values for field_bgimage_life_stage.
    $row->life_stage = array();
    if ($row->adult == 1) {
      $row->life_stage[] = 'adult';
    }
    if ($row->immature == 1) {
      $row->life_stage[] = 'immature';
    }

    return parent::prepareRow($row);
  }

  /**
   * Acts after a node has been saved.
   *
   * Attaches the image to the node.
   */
  public function complete($entity, stdClass $row) {
    $obfuscate = image_obfuscate($row->base . $entity->nid);
    $prefix = bgimage_get_prefix($obfuscate);
    $directory = 'public://raw/' . $prefix;
    $filename = $obfuscate . '.jpg';
    $uri = $directory . $filename;

    // If the image was found save it to Drupal and attach it to the node.
    if (file_exists($uri)) {
      // First, save the image as a file entity.
      $file = array(
        'filename' => $filename,
        'uri' => $uri,
        'status' => FILE_STATUS_PERMANENT,
        'filemime' => file_get_mimetype($uri),
      );
      $file_entity = file_save((object) $file);

      // Then, attach the file to the node.
      $node = new stdClass();
      $node->nid = $entity->nid;
      $node->type = 'bgimage';
      $node->field_bgimage_image[LANGUAGE_NONE][0]['fid'] = $file_entity->fid;
      $node->field_bgimage_image[LANGUAGE_NONE][0]['width'] = $row->width;
      $node->field_bgimage_image[LANGUAGE_NONE][0]['height'] = $row->height;
      field_attach_update('node', $node);
      entity_get_controller('node')->resetCache(array($node->nid));
    }
  }
}
