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
    $query->join('field_data_body', 'fdb', 'fdb.entity_id = bgp.nid');
    $query->join('node', 'n', 'fdb.entity_id = n.nid');
    $query->fields('bgp', array('nid', 'parent', 'images', 'scientific_name', 'names', 'counts', 'size', 'id', 'raynge', 'habitat', 'season', 'food', 'life_cycle', 'pronunciation', 'etymology', 'synonyms', 'see_also', 'print_references', 'web_references', 'taxon', 'hodges_number', 'uids', 'location_codes', 'sequence'))
          ->fields('fdb', array('body_value'));
    $query->addField('n', 'title');
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type bgpage
    $this->destination = new MigrateDestinationNode('bgpage');

    // Mapped fields
    $this->addFieldMapping('field_common_name', 'title');
    $this->addFieldMapping('field_remarks', 'body_value');
    $this->addFieldMapping('field_remarks:format')->defaultValue('f');
    $this->addFieldMapping('field_scientific_name', 'scientific_name');
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('field_parent', 'parent');
    $this->addFieldMapping('field_other_common_names', 'names');
    $this->addFieldMapping('field_other_common_names:format')->defaultValue('f');
    $this->addFieldMapping('field_counts', 'counts');
    $this->addFieldMapping('field_counts:format')->defaultValue('f');
    $this->addFieldMapping('field_size', 'size');
    $this->addFieldMapping('field_size:format')->defaultValue('f');
    $this->addFieldMapping('field_id', 'id');
    $this->addFieldMapping('field_id:format')->defaultValue('f');
    $this->addFieldMapping('field_range', 'raynge');
    $this->addFieldMapping('field_range:format')->defaultValue('f');
    $this->addFieldMapping('field_habitat', 'habitat');
    $this->addFieldMapping('field_habitat:format')->defaultValue('f');
    $this->addFieldMapping('field_season', 'season');
    $this->addFieldMapping('field_season:format')->defaultValue('f');
    $this->addFieldMapping('field_food', 'food');
    $this->addFieldMapping('field_food:format')->defaultValue('f');
    $this->addFieldMapping('field_life_cycle', 'life_cycle');
    $this->addFieldMapping('field_life_cycle:format')->defaultValue('f');
    $this->addFieldMapping('field_pronunciation', 'pronunciation');
    $this->addFieldMapping('field_pronunciation:format')->defaultValue('f');
    $this->addFieldMapping('field_etymology', 'etymology');
    $this->addFieldMapping('field_etymology:format')->defaultValue('f');
    $this->addFieldMapping('field_synonyms', 'synonyms');
    $this->addFieldMapping('field_synonyms:format')->defaultValue('f');
    $this->addFieldMapping('field_taxon', 'taxon');
    $this->addFieldMapping('field_hodges_number', 'hodges_number');
    $this->addFieldMapping('field_editors', 'uids');
    $this->addFieldMapping('field_location_codes', 'location_codes');
    $this->addFieldMapping('field_see_also', 'see_also');
    $this->addFieldMapping('field_see_also:format')->defaultValue('f');
    $this->addFieldMapping('field_print_references', 'print_references');
    $this->addFieldMapping('field_print_references:format')->defaultValue('f');
    $this->addFieldMapping('field_internet_references', 'web_references');
    $this->addFieldMapping('field_internet_references:format')->defaultValue('f');
    $this->addFieldMapping('field_representative_images', 'images');
    $this->addFieldMapping('field_weight', 'sequence');

    $this->addUnmigratedDestinations(array(
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
      'field_bgimage_image',
      'comment',
    ));
  }
}
