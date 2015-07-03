<?php

/**
 * To define a migration process from a set of source data to a particular
 * kind of Drupal object (for example, a specific node type), you define
 * a class derived from Migration. You must define a constructor to initialize
 * your migration object.
 *
 * For your classes to be instantiated so they can be used to import content,
 * you must register them - look at migrate_example.migrate.inc to see how
 * registration works. Right now, it's important to understand that each
 * migration will have a unique "machine name", which is displayed in the UI
 * and is used to reference the migration in drush commands.
 *
 * In any serious migration project, you will find there are some options
 * which are common to the individual migrations you're implementing. You can
 * define an abstract intermediate class derived from Migration, then derive your
 * individual migrations from that, to share settings, utility functions, etc.
 */
abstract class BasicBugGuideMigration extends Migration {
  // A Migration constructor takes an array of arguments as its first parameter.
  // The arguments must be passed through to the parent constructor.
  public function __construct($arguments) {
    parent::__construct($arguments);

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
   // $this->team = array(
   //   new MigrateTeamMember('Liz Taster', 'ltaster@example.com',
   //                        t('Product Owner')),
   //   new MigrateTeamMember('Larry Brewer', 'lbrewer@example.com',
   //                         t('Implementor')),
   // );

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
    $query->fields('bgp', array('nid', 'parent', 'scientific_name', 'names', 'counts', 'size', 'id', 'raynge', 'habitat', 'season', 'food', 'life_cycle', 'pronunciation', 'etymology', 'synonyms', 'see_also', 'print_references', 'taxon', 'hodges_number', 'uids', 'location_codes'));
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
         ->description(t('Other common names'));
   $this->addFieldMapping('field_counts', 'counts')
         ->description(t('Counts'));
   $this->addFieldMapping('field_size', 'size')
         ->description(t('Size'));
   $this->addFieldMapping('field_id', 'id')
         ->description(t('ID'));
   $this->addFieldMapping('field_range', 'raynge')
         ->description(t('Range'));
   $this->addFieldMapping('field_habitat', 'habitat')
         ->description(t('Habitat'));
   $this->addFieldMapping('field_season', 'season')
         ->description(t('Season'));
   $this->addFieldMapping('field_food', 'food')
         ->description(t('Food'));
   $this->addFieldMapping('field_life_cycle', 'life_cycle')
         ->description(t('Life Cycle'));
   $this->addFieldMapping('field_pronunciation', 'pronunciation')
         ->description(t('Pronunciation'));
   $this->addFieldMapping('field_etymology', 'etymology')
         ->description(t('Etymology'));
   $this->addFieldMapping('field_synonyms', 'synonyms')
         ->description(t('Synonyms'));
   $this->addFieldMapping('field_taxon', 'taxon')
         ->description(t('Taxon'));
   $this->addFieldMapping('field_hodges_number', 'hodges_numbers')
         ->description(t('Hodges Number'));
   $this->addFieldMapping('field_editors', 'uids')
         ->description(t('Editors'));
   $this->addFieldMapping('field_location_codes', 'location_codes')
         ->description(t('Location Codes'));
   $this->addFieldMapping('field_see_also', 'see_also')
         ->description(t('See also'));
   $this->addFieldMapping('field_print_references', 'print_references')
         ->description(t('Print references'));

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
      'is_new','body',
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
      'field_internet_references',
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

    /*


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
    */
  }
}
