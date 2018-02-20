<?php
/**
 * @file
 * Migration class for bglink nodes.
 */

/**
 * Migrates bglink custom table into fields.
 */
class BGLinkFieldMigration extends BasicBugGuideMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Links');

    // Only update existing nodes; do not create new nodes. The definitive
    // node id is the one in the destination. Since we are migrating data from
    // a MySQL table into existing Drupal 7 nodes/fields, this makes sense.
    // https://www.drupal.org/node/1117454
    $this->systemOfRecord = Migration::DESTINATION;

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'BG Link Node ID.',
          'alias' => 'bgl',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = db_select('bglink', 'bgl');
    $query->fields('bgl', array('nid', 'parent', 'link'));
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type bglink.
    $this->destination = new MigrateDestinationNode('bglink');

    // Mapped fields
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('field_parent', 'parent')
         ->description(t('Parent'));
    $this->addFieldMapping('field_link', 'link')
         ->description(t('Link'));
  }
}
