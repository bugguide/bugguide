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
    $query->fields('bgi', array('nid', 'parent', 'base', 'id', 'location', 'size', 'date_taken', 'owner', 'county', 'location_code'));
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type bgpage
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
      'body:summary',
      'body:format',
      'body:language',
      'comment',
    ));
  }
}
