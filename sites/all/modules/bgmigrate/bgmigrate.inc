<?php

/**
 * To define a migration process from a set of source data to a particular
 * kind of Drupal object (for example, a specific node type), you define
 * a class derived from Migration. You must define a constructor to initialize
 * your migration object. By default, your class name will be the "machine name"
 * of the migration, by which you refer to it. Note that the machine name is
 * case-sensitive.
 *
 * In any serious migration project, you will find there are some options
 * which are common to the individual migrations you're implementing. You can
 * define an abstract intermediate class derived from Migration, then derive your
 * individual migrations from that, to share settings, utility functions, etc.
 */
abstract class BasicBugGuideMigration extends DynamicMigration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct();

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    //$this->team = array(
    //  new MigrateTeamMember('Liz Taster', 'ltaster@example.com', t('Product Owner')),
    //  new MigrateTeamMember('Larry Brewer', 'lbrewer@example.com', t('Implementor')),
    //);

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    //$this->issuePattern = 'http://drupal.org/node/:id:';
  }
}

/**
 * The BeerNodeMigration uses the migrate_example_beer_node table as source
 * and creates Drupal nodes of type 'Beer' as destination.
 */
class BGPageFieldMigration extends BasicBugGuideMigration {
  public function __construct() {
    parent::__construct();
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
          'alias' => 'bgnid',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    
    $query = db_select('bgpage', 'bgp');
    $this->source = new MigrateSourceSQL($query, array());

    // Set up our destination - nodes of type migrate_example_beer
    $this->destination = new MigrateDestinationNode('bgpage');

    // Mapped fields
    $this->addFieldMapping('title', 'name')
         ->description(t('Mapping beer name in source to node title'));


         
         
         
         
    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE. This works only if we're importing into a system that
    // has no existing nodes with the nids being imported.
    $this->addFieldMapping('nid', 'bid')
         ->description(t('Preserve old beer ID as nid in Drupal'));
    $this->addFieldMapping('is_new')
         ->defaultValue(TRUE);

    // References to related objects (such as the author of the content) are
    // most likely going to be identifiers from the source data, not Drupal
    // identifiers (such as uids). You can use the mapping from the relevant
    // migration to translate from the old ID to the Drupal identifier.
    // Note that we also provide a default value of 1 - if the lookup fails to
    // find a corresponding uid for the aid, the owner will be the administrative
    // account.
    $this->addFieldMapping('uid', 'aid')
         ->sourceMigration('BeerUser')
         ->defaultValue(1);

    // This is a multi-value text field
    $this->addFieldMapping('field_migrate_example_country', 'countries')
         ->separator('|');
    // These are related terms, which by default will be looked up by name
    $this->addFieldMapping('migrate_example_beer_styles', 'terms')
         ->separator(',');

    // Some fields may have subfields such as text formats or summaries
    // (equivalent to teasers in previous Drupal versions).
    // These can be individually mapped as we see here.
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:summary', 'excerpt');

    // Copy an image file, write DB record to files table, and save in Field storage.
    // We map the filename (relative to the source_dir below) to the field itself.
    $this->addFieldMapping('field_migrate_example_image', 'image');
    // Here we specify the directory containing the source files.
    $this->addFieldMapping('field_migrate_example_image:source_dir')
         ->defaultValue(drupal_get_path('module', 'migrate_example'));
    // And we map the alt and title values in the database to those on the image.
    $this->addFieldMapping('field_migrate_example_image:alt', 'image_alt');
    $this->addFieldMapping('field_migrate_example_image:title', 'image_title');

    // No description for images, only alt and title
    $this->addUnmigratedSources(array('image_description'));

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('created', 'changed', 'status',
      'promote', 'revision', 'language', 'revision_uid', 'log', 'tnid',
      'body:format', 'body:language', 'migrate_example_beer_styles:source_type',
      'migrate_example_beer_styles:create_term', 'field_migrate_example_image:destination_dir',
      'field_migrate_example_image:language', 'field_migrate_example_image:file_replace',
      'field_migrate_example_image:preserve_files', 'field_migrate_example_country:language', 'comment',
      'field_migrate_example_image:file_class', 'field_migrate_example_image:destination_file'));

    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')
             ->issueGroup(t('DNM'));
      }
    }
    if (module_exists('statistics')) {
      $this->addUnmigratedDestinations(array('totalcount', 'daycount', 'timestamp'));
    }
  }
}