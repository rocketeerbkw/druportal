<?php

/**
 * @file
 *   Import SkyPortal(TM) forums from CSV
 */

class DruportalForumCategoryMigration extends DruportalMigration {
  public function __construct(array $arguments) {
    // When run from drush, the path to the file may be passed as an argument
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import forum categories from SkyPortal<sup>TM</sup>');

    // Make sure forums is installed and enabled
    if (!module_exists('forum')) {
      $this->enabled = false;
      $this->description .= ' (Requires forum module be enabled)';
    }

    $this->softDependencies = array('DruportalUser');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array('cat_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Category ID'
      )),
      MigrateDestinationTerm::getKeySchema()
    );

    $file = isset($arguments['source_file']) ? $arguments['source_file'] : DRUPAL_ROOT . '/portal_category.csv';

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceCSV($file, $this->csvColumns());

    $this->destination = new MigrateDestinationTerm('forums');

    // Mapped fields
    $this->addFieldMapping('name', 'cat_name');
    $this->addFieldMapping('weight', 'cat_order');

    // Unmapped destination fields
    $this->addFieldMapping('description')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('parent_name')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('parent')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('path')
         ->issueGroup(t('DNM'));

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'cat_status')
         ->description(t('Indicates of category is locked.'))
         ->issueGroup(t('DNN'));
  }

  function csvColumns() {
    $columns[0]  = array('cat_id', 'Category ID');
    $columns[1]  = array('cat_name', 'Category Name');
    $columns[2]  = array('cat_order', 'Category Order');
    $columns[3]  = array('cat_status', 'Category Locked');

    return $columns;
  }

  function prepareRow($row) {
    // Check for CSV header row
    if (strtolower($row->cat_id) == 'cat_id') {
      return FALSE;
    }
  }
}
