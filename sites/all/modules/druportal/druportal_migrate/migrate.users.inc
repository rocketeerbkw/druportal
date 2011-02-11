<?php

/**
 * @file
 *   Import SkyPortal(TM) members from CSV
 */

class DruportalUserMigration extends DruportalMigration {
  public function __construct(array $arguments) {
    // When run from drush, the path to the file may be passed as an argument
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import members from SkyPortal<sup>TM</sup>');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array('member_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Member ID'
      )),
      MigrateDestinationUser::getKeySchema()
    );

    $file = isset($arguments['source_file']) ? $arguments['source_file'] : DRUPAL_ROOT . '/portal_members.csv';

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceCSV($file, $this->csvColumns());

    $this->destination = new MigrateDestinationUser();

    // Mapped Fields
    $this->addFieldMapping('name', 'm_name')
         ->dedupe('users', 'name');
    $this->addFieldMapping('pass', 'm_password');
    $this->addFieldMapping('mail', 'm_email');
    $this->addFieldMapping('signature', 'm_sig');
    $this->addFieldMapping('created', 'm_date');
    $this->addFieldMapping('access', 'm_lastheredate');
    $this->addFieldMapping('login', 'm_lastheredate');
    $this->addFieldMapping('status', 'm_status');

    // Unmapped destination fields
    $this->addFieldMapping('roles')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('theme')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('signature_format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('timezone')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('picture')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('init')
       ->issueGroup(t('DNM'));

    // Unmappped Source Fields
    
  }
  
  function csvColumns() {
    $columns[0]  = array('member_id', 'Member ID');
    $columns[1]  = array('m_age', 'Age');
    $columns[2]  = array('m_aim', 'AIM Screen Name');
    $columns[3]  = array('m_avatar_url', 'Avatar URL');
    $columns[4]  = array('m_bio', '');
    $columns[5]  = array('m_city', 'City');
    $columns[6]  = array('m_country', 'Country');
    $columns[7]  = array('m_date', 'Created Date');
    $columns[8]  = array('m_default_view', '');
    $columns[9]  = array('m_email', 'Email Address');
    $columns[10] = array('m_firstname', 'First Name');
    $columns[11] = array('m_glow', '');
    $columns[12] = array('m_gold', 'Gold');
    $columns[13] = array('m_gtotal', '');
    $columns[14] = array('m_hide_email', '');
    $columns[15] = array('m_hobbies', '');
    $columns[16] = array('m_homepage', '');
    $columns[17] = array('m_icq', 'ICQ Screen Name');
    $columns[18] = array('m_ip', '');
    $columns[19] = array('m_key', '');
    $columns[20] = array('m_last_ip', 'Last Seen IP Address');
    $columns[21] = array('m_lastheredate', 'Last Seen Date');
    $columns[22] = array('m_lastname', 'Last Name');
    $columns[23] = array('m_lastpostdate', 'Last Date User Posted Anything');
    $columns[24] = array('m_level', '');
    $columns[25] = array('m_link1', '');
    $columns[26] = array('m_link2', '');
    $columns[27] = array('m_lnews', '');
    $columns[28] = array('m_losses', '');
    $columns[29] = array('m_marstatus', 'Marital Status');
    $columns[30] = array('m_msn', 'MSN Screen Name');
    $columns[31] = array('m_name', 'Username');
    $columns[32] = array('m_newemail', '');
    $columns[33] = array('m_occupation', '');
    $columns[34] = array('m_page_views', '');
    $columns[35] = array('m_password', 'Password');
    $columns[36] = array('m_photo_url', '');
    $columns[37] = array('m_pmemail', '');
    $columns[38] = array('m_pmreceive', '');
    $columns[39] = array('m_posts', '');
    $columns[40] = array('m_quote', '');
    $columns[41] = array('m_receive_email', '');
    $columns[42] = array('m_recmail', '');
    $columns[43] = array('m_rep', '');
    $columns[44] = array('m_rname', '');
    $columns[45] = array('m_rtotal', '');
    $columns[46] = array('m_sex', 'Sex');
    $columns[47] = array('m_sig', 'Signature');
    $columns[48] = array('m_state', '');
    $columns[49] = array('m_status', 'Status');
    $columns[50] = array('m_subscription', '');
    $columns[51] = array('m_title', '');
    $columns[52] = array('m_username', 'Username');
    $columns[53] = array('m_wins', '');
    $columns[54] = array('m_yahoo', 'Yahoo! Screen Name');
    $columns[55] = array('m_zip', 'Zip Code');
    $columns[56] = array('theme_id', '');
    $columns[57] = array('m_show_birthday', '');
    $columns[58] = array('m_pmstatus', '');
    $columns[59] = array('m_pmblacklist', '');
    $columns[60] = array('m_donate', '');
    $columns[61] = array('m_lang', '');
    $columns[62] = array('m_lcid', '');
    $columns[63] = array('m_time_offset', '');
    $columns[64] = array('m_time_type', '');

    return $columns;


  }

  function prepareRow($row) {
    // Convert dates from SkyPortal(TM) to unix epoch
    $row->m_date = $this->spDateConvert($row->m_date);
    $row->m_lastheredate = $this->spDateConvert($row->m_lastheredate);

    // Signature can't be more than 255 characters long
    $row->m_sig = substr($row->m_sig, 0, 255);
  }
}