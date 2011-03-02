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
    $this->source = new DruportalMigrateSourceCSV($file, $this->csvColumns());

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
         ->issueGroup(t('DNM'));
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

class DruportalForumMigration extends DruportalMigration {
  public function __construct(array $arguments) {
    // When run from drush, the path to the file may be passed as an argument
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import forums from SkyPortal<sup>TM</sup>');

    $this->dependencies = array('DruportalForumCategory');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array('forum_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Forum ID'
      )),
      MigrateDestinationTerm::getKeySchema()
    );

    $file = isset($arguments['source_file']) ? $arguments['source_file'] : DRUPAL_ROOT . '/portal_forum.csv';

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new DruportalMigrateSourceCSV($file, $this->csvColumns());

    $this->destination = new MigrateDestinationTerm('forums');

    // Mapped fields
    $this->addFieldMapping('name', 'f_subject');
    $this->addFieldMapping('description', 'f_description');
    $this->addFieldMapping('weight', 'forum_order');
    $this->addFieldMapping('parent', 'cat_id')
         ->sourceMigration('DruportalForumCategory');

    // Unmapped destination fields
    $this->addFieldMapping('format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('parent_name')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('path')
         ->issueGroup(t('DNM'));

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'f_count')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_ip')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_last_post')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_last_post_author')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_mail')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_password_new')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_privateforums')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_status')
         ->description(t('Indicates of forum is locked.'))
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_topics')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_type')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'f_url')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'l_archive')
         ->issueGroup(t('DNM'));
  }

  function csvColumns() {
    $columns[0] = array('cat_id', 'Parent Category ID');
    $columns[1] = array('f_count', 'Number of posts in forum');
    $columns[2] = array('f_description', 'Forum Description');
    $columns[3] = array('f_ip', '');
    $columns[4] = array('f_last_post', 'Date of last post');
    $columns[5] = array('f_last_post_author', 'Author of last post');
    $columns[6] = array('f_mail', '');
    $columns[7] = array('f_password_new', '');
    $columns[8] = array('f_privateforums', '');
    $columns[9] = array('f_status', 'Forum Locked');
    $columns[10] = array('f_subject', 'Forum Name');
    $columns[11] = array('f_topics', 'Number of topics in forum');
    $columns[12] = array('f_type', '');
    $columns[13] = array('f_url', '');
    $columns[14] = array('forum_id', 'Forum ID');
    $columns[15] = array('forum_order', 'Forum Order');
    $columns[16] = array('l_archive', '');

    return $columns;
  }

  function prepareRow($row) {
    // Check for CSV header row
    if (strtolower($row->cat_id) == 'cat_id') {
      return FALSE;
    }
  }
}

class DruportalForumTopicMigration extends DruportalMigration {
  public function __construct(array $arguments) {
    // When run from drush, the path to the file may be passed as an argument
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import forum topics from SkyPortal<sup>TM</sup>');

    $this->dependencies = array('DruportalForum', 'DruportalUser');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array('topic_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Topic ID'
      )),
      MigrateDestinationNode::getKeySchema()
    );

    $file = isset($arguments['source_file']) ? $arguments['source_file'] : DRUPAL_ROOT . '/portal_topics.csv';

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new DruportalMigrateSourceCSV($file, $this->csvColumns());

    $this->destination = new MigrateDestinationNode('forum');

    // Mapped fields
    $this->addFieldMapping('uid', 't_author')
         ->sourceMigration('DruportalUser')
         ->defaultValue(1);
    $this->addFieldMapping('created', 't_date');
    $this->addFieldMapping('changed', 't_date');
    $this->addFieldMapping('promote', 't_news');
    $this->addFieldMapping('sticky', 't_inplace');
    $this->addFieldMapping('title', 't_subject');
    $this->addFieldMapping('body', 't_message');
    // Term mapping
    $this->addFieldMapping('taxonomy_forums', 'forum_id')
         ->sourceMigration('DruportalForum')
         ->arguments(array('source_type' => 'tid'));
    $this->addFieldMapping('comment', 't_status');

    // Unmapped destination fields
    $this->addFieldMapping('is_new')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('revision_uid')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('status')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('revision')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('path')
         ->issueGroup(t('DNM'));

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'cat_id')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_ip')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_last_post')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_last_post_author')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_last_poster')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_mail')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_msgicon')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_poll')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_replies')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_sig')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 't_view_count')
         ->issueGroup(t('DNM'));
  }

  function csvColumns() {
    $columns[0] = array('cat_id', 'Category ID');
    $columns[1] = array('forum_id', 'Forum ID');
    $columns[2] = array('t_author', 'Topic Author ID');
    $columns[3] = array('t_date', 'Date topic created');
    $columns[4] = array('t_inplace', 'Topic Sticky');
    $columns[5] = array('t_ip', 'IP address of author');
    $columns[6] = array('t_last_post', 'Date of last post (topic created or last reply)');
    $columns[7] = array('t_last_post_author', 'Author of last post (topic created or last reply)');
    $columns[8] = array('t_last_poster', '');
    $columns[9] = array('t_mail', '');
    $columns[10] = array('t_message', 'Topic Body');
    $columns[11] = array('t_msgicon', '');
    $columns[12] = array('t_news', 'Topic is News');
    $columns[13] = array('t_poll', 'Topic is Poll');
    $columns[14] = array('t_replies', 'Number of replies to topic');
    $columns[15] = array('t_sig', '');
    $columns[16] = array('t_status', 'Topic Locked');
    $columns[17] = array('t_subject', 'Topic Title');
    $columns[18] = array('t_view_count', 'Number of views for topic');
    $columns[19] = array('topic_id', 'Topic ID');

    return $columns;
  }

  function prepareRow($row) {
    // Check for CSV header row
    if (strtolower($row->cat_id) == 'cat_id') {
      return FALSE;
    }

    // Convert dates from SkyPortal(TM) to unix epoch
    $row->t_date = $this->spDateConvert($row->t_date);

    // t_status is OFF (0) or ON (1), but comment is OFF (0) Read Only (1) Read/Write (2)
    $row->t_status = $row->t_status ? 2 : 1;
  }
}