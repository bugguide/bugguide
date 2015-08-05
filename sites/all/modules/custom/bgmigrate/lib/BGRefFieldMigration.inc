<?php
/**
 * @file
 * Migration class for bgref nodes.
 */

/**
 * Migrates bgref content into book_reference nodes.
 */
class BGRefFieldMigration extends BasicBugGuideMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Book References');

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
          'description' => 'Book Reference Node ID.',
          'alias' => 'bgr',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = db_select('bgref', 'bgr');
    $query->fields('bgr', array('nid', 'parent', 'isbn', 'author', 'weight', 'publisher', 'year', 'show_image'));
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type book_reference.
    $this->destination = new MigrateDestinationNode('book_reference');

    // Mapped fields
    $this->addFieldMapping('field_book_reference_isbn', 'isbn')
         ->description(t('ISBN'));
    $this->addFieldMapping('nid', 'nid')
         ->description(t('Node ID'));
    $this->addFieldMapping('field_parent', 'parent')
         ->description(t('Parent'));
   $this->addFieldMapping('field_book_reference_author', 'author')
         ->description(t('Author'));
   $this->addFieldMapping('field_book_reference_weight', 'weight')
         ->description(t('Weight'));
   $this->addFieldMapping('field_book_reference_publisher', 'publisher')
         ->description(t('Publisher'));
   $this->addFieldMapping('field_book_reference_year', 'year')
         ->description(t('Year'));
   $this->addFieldMapping('field_book_reference_show_image', 'show_image')
         ->description(t('Show image'));
  }
}
