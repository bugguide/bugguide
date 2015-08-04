<?php
/**
 * @file
 * Migration class for bgpage nodes.
 */

class BGPageFieldMigration extends BasicBugGuideMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('BGPages');

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
          'alias' => 'bgp',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = db_select('bgpage_archive', 'bgp');
    $query->fields('bgp', array('nid', 'parent', 'scientific_name', 'names', 'counts', 'size', 'id', 'raynge', 'habitat', 'season', 'food', 'life_cycle', 'pronunciation', 'etymology', 'synonyms', 'see_also', 'print_references', 'web_references', 'taxon', 'hodges_number', 'uids', 'location_codes'));
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type bgpage
    $this->destination = new MigrateDestinationNode('bgpage');

    // Mapped fields
    $this->addFieldMapping('field_scientific_name', 'scientific_name')
         ->description(t('Mapping scientific name'));
    $this->addFieldMapping('nid', 'nid')
         ->description(t('Node ID'));
    $this->addFieldMapping('field_parent', 'parent')
         ->description(t('Parent'));
   $this->addFieldMapping('field_other_common_names', 'names')
         ->description(t('Other common names'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_counts', 'counts')
         ->description(t('Counts'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_size', 'size')
         ->description(t('Size'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_id', 'id')
         ->description(t('ID'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_range', 'raynge')
         ->description(t('Range'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_habitat', 'habitat')
         ->description(t('Habitat'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_season', 'season')
         ->description(t('Season'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_food', 'food')
         ->description(t('Food'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_life_cycle', 'life_cycle')
         ->description(t('Life Cycle'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_pronunciation', 'pronunciation')
         ->description(t('Pronunciation'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_etymology', 'etymology')
         ->description(t('Etymology'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_synonyms', 'synonyms')
         ->description(t('Synonyms'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_taxon', 'taxon')
         ->description(t('Taxon'));
   $this->addFieldMapping('field_hodges_number', 'hodges_numbers')
         ->description(t('Hodges Number'));
   $this->addFieldMapping('field_editors', 'uids')
         ->description(t('Editors'));
   $this->addFieldMapping('field_location_codes', 'location_codes')
         ->description(t('Location Codes'));
   $this->addFieldMapping('field_see_also', 'see_also')
         ->description(t('See also'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_print_references', 'print_references')
         ->description(t('Print references'))
         ->arguments(array('format' => 1));
   $this->addFieldMapping('field_internet_references', 'web_references')
         ->description(t('Internet references'))
         ->arguments(array('format' => 1));

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
      'field_common_name',
      'field_common_name:language',
      'field_counts:format',
      'field_counts:language',
      'field_editors:language',
      'field_etymology:format',
      'field_etymology:language',
      'field_food:format',
      'field_food:language',
      'field_habitat:format',
      'field_habitat:language',
      'field_id:language',
      'field_id:format',
      'field_internet_references:format',
      'field_internet_references:language',
      'field_life_cycle:format',
      'field_life_cycle:language',
      'field_location_codes:language',
      'field_other_common_names:format',
      'field_other_common_names:language',
      'field_parent:language',
      'field_print_references:format',
      'field_print_references:language',
      'field_pronunciation:format',
      'field_pronunciation:language',
      'field_range:format',
      'field_range:language',
      'field_remarks',
      'field_remarks:format',
      'field_remarks:language',
      'field_representative_images',
      'field_representative_images:language',
      'field_scientific_name:language',
      'field_season:format',
      'field_season:language',
      'field_see_also:format',
      'field_see_also:language',
      'field_size:format',
      'field_size:language',
      'field_synonyms:format',
      'field_synonyms:language',
      'comment',
    ));
  }

  /**
   * Acts after a node has been saved.
   */
  public function complete($entity, stdClass $row) {
    // Copy body into field_remarks.
    $entity->field_remarks[LANGUAGE_NONE][0] = array(
      'value' => $entity->body[LANGUAGE_NONE][0]['value'],
      'format' => 1,
    );
    node_save($entity);
  }
}
