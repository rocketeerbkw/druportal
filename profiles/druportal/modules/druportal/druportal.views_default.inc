<?php

/**
 * Implementation of hook_views_default_views().
 **/
function druportal_views_default_views()
{
  $views = array();

  $views = array_merge($views, druportal_views_default_views_forums());
  $views = array_merge($views, druportal_views_default_views_members());

  return $views;
}

function druportal_views_default_views_members()
{
  $views = array();

  /*
   * View 'sp_portal_members'
   */
  $view = new view;
  $view->name = 'sp_portal_members';
  $view->description = 'sp_portal_members';
  $view->tag = 'tw';
  $view->view_php = '';
  $view->base_table = 'sp_portal_members';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'sp_portal_members', 'default');
  $handler->override_option('fields', array(
    'MEMBER_ID' => array(
      'id' => 'MEMBER_ID',
      'table' => 'sp_portal_members',
      'field' => 'MEMBER_ID',
      'label' => 'MEMBER_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_AGE' => array(
      'id' => 'M_AGE',
      'table' => 'sp_portal_members',
      'field' => 'M_AGE',
      'label' => 'M_AGE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_AIM' => array(
      'id' => 'M_AIM',
      'table' => 'sp_portal_members',
      'field' => 'M_AIM',
      'label' => 'M_AIM',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_AVATAR_URL' => array(
      'id' => 'M_AVATAR_URL',
      'table' => 'sp_portal_members',
      'field' => 'M_AVATAR_URL',
      'label' => 'M_AVATAR_URL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_BIO' => array(
      'id' => 'M_BIO',
      'table' => 'sp_portal_members',
      'field' => 'M_BIO',
      'label' => 'M_BIO',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_CITY' => array(
      'id' => 'M_CITY',
      'table' => 'sp_portal_members',
      'field' => 'M_CITY',
      'label' => 'M_CITY',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_COUNTRY' => array(
      'id' => 'M_COUNTRY',
      'table' => 'sp_portal_members',
      'field' => 'M_COUNTRY',
      'label' => 'M_COUNTRY',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_DATE' => array(
      'id' => 'M_DATE',
      'table' => 'sp_portal_members',
      'field' => 'M_DATE',
      'label' => 'M_DATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_DEFAULT_VIEW' => array(
      'id' => 'M_DEFAULT_VIEW',
      'table' => 'sp_portal_members',
      'field' => 'M_DEFAULT_VIEW',
      'label' => 'M_DEFAULT_VIEW',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_EMAIL' => array(
      'id' => 'M_EMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_EMAIL',
      'label' => 'M_EMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_FIRSTNAME' => array(
      'id' => 'M_FIRSTNAME',
      'table' => 'sp_portal_members',
      'field' => 'M_FIRSTNAME',
      'label' => 'M_FIRSTNAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_GLOW' => array(
      'id' => 'M_GLOW',
      'table' => 'sp_portal_members',
      'field' => 'M_GLOW',
      'label' => 'M_GLOW',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_GOLD' => array(
      'id' => 'M_GOLD',
      'table' => 'sp_portal_members',
      'field' => 'M_GOLD',
      'label' => 'M_GOLD',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_GTOTAL' => array(
      'id' => 'M_GTOTAL',
      'table' => 'sp_portal_members',
      'field' => 'M_GTOTAL',
      'label' => 'M_GTOTAL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_HIDE_EMAIL' => array(
      'id' => 'M_HIDE_EMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_HIDE_EMAIL',
      'label' => 'M_HIDE_EMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_HOBBIES' => array(
      'id' => 'M_HOBBIES',
      'table' => 'sp_portal_members',
      'field' => 'M_HOBBIES',
      'label' => 'M_HOBBIES',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_HOMEPAGE' => array(
      'id' => 'M_HOMEPAGE',
      'table' => 'sp_portal_members',
      'field' => 'M_HOMEPAGE',
      'label' => 'M_HOMEPAGE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_ICQ' => array(
      'id' => 'M_ICQ',
      'table' => 'sp_portal_members',
      'field' => 'M_ICQ',
      'label' => 'M_ICQ',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_IP' => array(
      'id' => 'M_IP',
      'table' => 'sp_portal_members',
      'field' => 'M_IP',
      'label' => 'M_IP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_KEY' => array(
      'id' => 'M_KEY',
      'table' => 'sp_portal_members',
      'field' => 'M_KEY',
      'label' => 'M_KEY',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LAST_IP' => array(
      'id' => 'M_LAST_IP',
      'table' => 'sp_portal_members',
      'field' => 'M_LAST_IP',
      'label' => 'M_LAST_IP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LASTHEREDATE' => array(
      'id' => 'M_LASTHEREDATE',
      'table' => 'sp_portal_members',
      'field' => 'M_LASTHEREDATE',
      'label' => 'M_LASTHEREDATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LASTNAME' => array(
      'id' => 'M_LASTNAME',
      'table' => 'sp_portal_members',
      'field' => 'M_LASTNAME',
      'label' => 'M_LASTNAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LASTPOSTDATE' => array(
      'id' => 'M_LASTPOSTDATE',
      'table' => 'sp_portal_members',
      'field' => 'M_LASTPOSTDATE',
      'label' => 'M_LASTPOSTDATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LEVEL' => array(
      'id' => 'M_LEVEL',
      'table' => 'sp_portal_members',
      'field' => 'M_LEVEL',
      'label' => 'M_LEVEL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LINK1' => array(
      'id' => 'M_LINK1',
      'table' => 'sp_portal_members',
      'field' => 'M_LINK1',
      'label' => 'M_LINK1',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LINK2' => array(
      'id' => 'M_LINK2',
      'table' => 'sp_portal_members',
      'field' => 'M_LINK2',
      'label' => 'M_LINK2',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LNEWS' => array(
      'id' => 'M_LNEWS',
      'table' => 'sp_portal_members',
      'field' => 'M_LNEWS',
      'label' => 'M_LNEWS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LOSSES' => array(
      'id' => 'M_LOSSES',
      'table' => 'sp_portal_members',
      'field' => 'M_LOSSES',
      'label' => 'M_LOSSES',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_MARSTATUS' => array(
      'id' => 'M_MARSTATUS',
      'table' => 'sp_portal_members',
      'field' => 'M_MARSTATUS',
      'label' => 'M_MARSTATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_MSN' => array(
      'id' => 'M_MSN',
      'table' => 'sp_portal_members',
      'field' => 'M_MSN',
      'label' => 'M_MSN',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_NAME' => array(
      'id' => 'M_NAME',
      'table' => 'sp_portal_members',
      'field' => 'M_NAME',
      'label' => 'M_NAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_NEWEMAIL' => array(
      'id' => 'M_NEWEMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_NEWEMAIL',
      'label' => 'M_NEWEMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_OCCUPATION' => array(
      'id' => 'M_OCCUPATION',
      'table' => 'sp_portal_members',
      'field' => 'M_OCCUPATION',
      'label' => 'M_OCCUPATION',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PAGE_VIEWS' => array(
      'id' => 'M_PAGE_VIEWS',
      'table' => 'sp_portal_members',
      'field' => 'M_PAGE_VIEWS',
      'label' => 'M_PAGE_VIEWS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PASSWORD' => array(
      'id' => 'M_PASSWORD',
      'table' => 'sp_portal_members',
      'field' => 'M_PASSWORD',
      'label' => 'M_PASSWORD',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PHOTO_URL' => array(
      'id' => 'M_PHOTO_URL',
      'table' => 'sp_portal_members',
      'field' => 'M_PHOTO_URL',
      'label' => 'M_PHOTO_URL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PMEMAIL' => array(
      'id' => 'M_PMEMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_PMEMAIL',
      'label' => 'M_PMEMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PMRECEIVE' => array(
      'id' => 'M_PMRECEIVE',
      'table' => 'sp_portal_members',
      'field' => 'M_PMRECEIVE',
      'label' => 'M_PMRECEIVE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_POSTS' => array(
      'id' => 'M_POSTS',
      'table' => 'sp_portal_members',
      'field' => 'M_POSTS',
      'label' => 'M_POSTS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_QUOTE' => array(
      'id' => 'M_QUOTE',
      'table' => 'sp_portal_members',
      'field' => 'M_QUOTE',
      'label' => 'M_QUOTE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_RECEIVE_EMAIL' => array(
      'id' => 'M_RECEIVE_EMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_RECEIVE_EMAIL',
      'label' => 'M_RECEIVE_EMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_RECMAIL' => array(
      'id' => 'M_RECMAIL',
      'table' => 'sp_portal_members',
      'field' => 'M_RECMAIL',
      'label' => 'M_RECMAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_REP' => array(
      'id' => 'M_REP',
      'table' => 'sp_portal_members',
      'field' => 'M_REP',
      'label' => 'M_REP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_RNAME' => array(
      'id' => 'M_RNAME',
      'table' => 'sp_portal_members',
      'field' => 'M_RNAME',
      'label' => 'M_RNAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_RTOTAL' => array(
      'id' => 'M_RTOTAL',
      'table' => 'sp_portal_members',
      'field' => 'M_RTOTAL',
      'label' => 'M_RTOTAL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_SEX' => array(
      'id' => 'M_SEX',
      'table' => 'sp_portal_members',
      'field' => 'M_SEX',
      'label' => 'M_SEX',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_SIG' => array(
      'id' => 'M_SIG',
      'table' => 'sp_portal_members',
      'field' => 'M_SIG',
      'label' => 'M_SIG',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_STATE' => array(
      'id' => 'M_STATE',
      'table' => 'sp_portal_members',
      'field' => 'M_STATE',
      'label' => 'M_STATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_STATUS' => array(
      'id' => 'M_STATUS',
      'table' => 'sp_portal_members',
      'field' => 'M_STATUS',
      'label' => 'M_STATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_SUBSCRIPTION' => array(
      'id' => 'M_SUBSCRIPTION',
      'table' => 'sp_portal_members',
      'field' => 'M_SUBSCRIPTION',
      'label' => 'M_SUBSCRIPTION',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_TITLE' => array(
      'id' => 'M_TITLE',
      'table' => 'sp_portal_members',
      'field' => 'M_TITLE',
      'label' => 'M_TITLE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_USERNAME' => array(
      'id' => 'M_USERNAME',
      'table' => 'sp_portal_members',
      'field' => 'M_USERNAME',
      'label' => 'M_USERNAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_WINS' => array(
      'id' => 'M_WINS',
      'table' => 'sp_portal_members',
      'field' => 'M_WINS',
      'label' => 'M_WINS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_YAHOO' => array(
      'id' => 'M_YAHOO',
      'table' => 'sp_portal_members',
      'field' => 'M_YAHOO',
      'label' => 'M_YAHOO',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_ZIP' => array(
      'id' => 'M_ZIP',
      'table' => 'sp_portal_members',
      'field' => 'M_ZIP',
      'label' => 'M_ZIP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'THEME_ID' => array(
      'id' => 'THEME_ID',
      'table' => 'sp_portal_members',
      'field' => 'THEME_ID',
      'label' => 'THEME_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_SHOW_BIRTHDAY' => array(
      'id' => 'M_SHOW_BIRTHDAY',
      'table' => 'sp_portal_members',
      'field' => 'M_SHOW_BIRTHDAY',
      'label' => 'M_SHOW_BIRTHDAY',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PMSTATUS' => array(
      'id' => 'M_PMSTATUS',
      'table' => 'sp_portal_members',
      'field' => 'M_PMSTATUS',
      'label' => 'M_PMSTATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_PMBLACKLIST' => array(
      'id' => 'M_PMBLACKLIST',
      'table' => 'sp_portal_members',
      'field' => 'M_PMBLACKLIST',
      'label' => 'M_PMBLACKLIST',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_DONATE' => array(
      'id' => 'M_DONATE',
      'table' => 'sp_portal_members',
      'field' => 'M_DONATE',
      'label' => 'M_DONATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LANG' => array(
      'id' => 'M_LANG',
      'table' => 'sp_portal_members',
      'field' => 'M_LANG',
      'label' => 'M_LANG',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_LCID' => array(
      'id' => 'M_LCID',
      'table' => 'sp_portal_members',
      'field' => 'M_LCID',
      'label' => 'M_LCID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_TIME_OFFSET' => array(
      'id' => 'M_TIME_OFFSET',
      'table' => 'sp_portal_members',
      'field' => 'M_TIME_OFFSET',
      'label' => 'M_TIME_OFFSET',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'M_TIME_TYPE' => array(
      'id' => 'M_TIME_TYPE',
      'table' => 'sp_portal_members',
      'field' => 'M_TIME_TYPE',
      'label' => 'M_TIME_TYPE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'table wizard administration',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Contents of sp_portal_members');
  $handler->override_option('header', 'This is a view of a raw database table. It may be sorted in various ways by clicking the column headers.

        If you identify a particular field that does not need to be used in views of this table, go to the <a href="/dev/druportal/admin/content/tw/analyze/1">analysis page</a> and check the <em>Ignore</em> box for that field. It will then no longer appear here.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty', 'There are no rows in this table.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'MEMBER_ID' => 'MEMBER_ID',
      'M_AGE' => 'M_AGE',
      'M_AIM' => 'M_AIM',
      'M_AVATAR_URL' => 'M_AVATAR_URL',
      'M_BIO' => 'M_BIO',
      'M_CITY' => 'M_CITY',
      'M_COUNTRY' => 'M_COUNTRY',
      'M_DATE' => 'M_DATE',
      'M_DEFAULT_VIEW' => 'M_DEFAULT_VIEW',
      'M_EMAIL' => 'M_EMAIL',
      'M_FIRSTNAME' => 'M_FIRSTNAME',
      'M_GLOW' => 'M_GLOW',
      'M_GOLD' => 'M_GOLD',
      'M_GTOTAL' => 'M_GTOTAL',
      'M_HIDE_EMAIL' => 'M_HIDE_EMAIL',
      'M_HOBBIES' => 'M_HOBBIES',
      'M_HOMEPAGE' => 'M_HOMEPAGE',
      'M_ICQ' => 'M_ICQ',
      'M_IP' => 'M_IP',
      'M_KEY' => 'M_KEY',
      'M_LAST_IP' => 'M_LAST_IP',
      'M_LASTHEREDATE' => 'M_LASTHEREDATE',
      'M_LASTNAME' => 'M_LASTNAME',
      'M_LASTPOSTDATE' => 'M_LASTPOSTDATE',
      'M_LEVEL' => 'M_LEVEL',
      'M_LINK1' => 'M_LINK1',
      'M_LINK2' => 'M_LINK2',
      'M_LNEWS' => 'M_LNEWS',
      'M_LOSSES' => 'M_LOSSES',
      'M_MARSTATUS' => 'M_MARSTATUS',
      'M_MSN' => 'M_MSN',
      'M_NAME' => 'M_NAME',
      'M_NEWEMAIL' => 'M_NEWEMAIL',
      'M_OCCUPATION' => 'M_OCCUPATION',
      'M_PAGE_VIEWS' => 'M_PAGE_VIEWS',
      'M_PASSWORD' => 'M_PASSWORD',
      'M_PHOTO_URL' => 'M_PHOTO_URL',
      'M_PMEMAIL' => 'M_PMEMAIL',
      'M_PMRECEIVE' => 'M_PMRECEIVE',
      'M_POSTS' => 'M_POSTS',
      'M_QUOTE' => 'M_QUOTE',
      'M_RECEIVE_EMAIL' => 'M_RECEIVE_EMAIL',
      'M_RECMAIL' => 'M_RECMAIL',
      'M_REP' => 'M_REP',
      'M_RNAME' => 'M_RNAME',
      'M_RTOTAL' => 'M_RTOTAL',
      'M_SEX' => 'M_SEX',
      'M_SIG' => 'M_SIG',
      'M_STATE' => 'M_STATE',
      'M_STATUS' => 'M_STATUS',
      'M_SUBSCRIPTION' => 'M_SUBSCRIPTION',
      'M_TITLE' => 'M_TITLE',
      'M_USERNAME' => 'M_USERNAME',
      'M_WINS' => 'M_WINS',
      'M_YAHOO' => 'M_YAHOO',
      'M_ZIP' => 'M_ZIP',
      'THEME_ID' => 'THEME_ID',
      'M_SHOW_BIRTHDAY' => 'M_SHOW_BIRTHDAY',
      'M_PMSTATUS' => 'M_PMSTATUS',
      'M_PMBLACKLIST' => 'M_PMBLACKLIST',
      'M_DONATE' => 'M_DONATE',
      'M_LANG' => 'M_LANG',
      'M_LCID' => 'M_LCID',
      'M_TIME_OFFSET' => 'M_TIME_OFFSET',
      'M_TIME_TYPE' => 'M_TIME_TYPE',
    ),
    'info' => array(
      'MEMBER_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_AGE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_AIM' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_AVATAR_URL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_BIO' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_CITY' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_COUNTRY' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_DATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_DEFAULT_VIEW' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_EMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_FIRSTNAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_GLOW' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_GOLD' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_GTOTAL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_HIDE_EMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_HOBBIES' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_HOMEPAGE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_ICQ' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_IP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_KEY' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LAST_IP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LASTHEREDATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LASTNAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LASTPOSTDATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LEVEL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LINK1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LINK2' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LNEWS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LOSSES' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_MARSTATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_MSN' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_NAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_NEWEMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_OCCUPATION' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PAGE_VIEWS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PASSWORD' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PHOTO_URL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PMEMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PMRECEIVE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_POSTS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_QUOTE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_RECEIVE_EMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_RECMAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_REP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_RNAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_RTOTAL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_SEX' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_SIG' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_STATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_STATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_SUBSCRIPTION' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_TITLE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_USERNAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_WINS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_YAHOO' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_ZIP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'THEME_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_SHOW_BIRTHDAY' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PMSTATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_PMBLACKLIST' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_DONATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LANG' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_LCID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_TIME_OFFSET' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'M_TIME_TYPE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => -1,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/tw/view/sp_portal_members');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  return $views;
}

function druportal_views_default_views_forums()
{
  $views = array();

  /*
   * View 'sp_portal_category'
   */
  $view = new view;
  $view->name = 'sp_portal_category';
  $view->description = 'sp_portal_category';
  $view->tag = 'tw';
  $view->view_php = '';
  $view->base_table = 'sp_portal_category';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'sp_portal_category', 'default');
  $handler->override_option('fields', array(
    'CAT_ID' => array(
      'id' => 'CAT_ID',
      'table' => 'sp_portal_category',
      'field' => 'CAT_ID',
      'label' => 'CAT_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'CAT_NAME' => array(
      'id' => 'CAT_NAME',
      'table' => 'sp_portal_category',
      'field' => 'CAT_NAME',
      'label' => 'CAT_NAME',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'CAT_ORDER' => array(
      'id' => 'CAT_ORDER',
      'table' => 'sp_portal_category',
      'field' => 'CAT_ORDER',
      'label' => 'CAT_ORDER',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'CAT_STATUS' => array(
      'id' => 'CAT_STATUS',
      'table' => 'sp_portal_category',
      'field' => 'CAT_STATUS',
      'label' => 'CAT_STATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'table wizard administration',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Contents of sp_portal_category');
  $handler->override_option('header', 'This is a view of a raw database table. It may be sorted in various ways by clicking the column headers.

        If you identify a particular field that does not need to be used in views of this table, go to the <a href="/dev/druportal/admin/content/tw/analyze/10">analysis page</a> and check the <em>Ignore</em> box for that field. It will then no longer appear here.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty', 'There are no rows in this table.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'CAT_ID' => 'CAT_ID',
      'CAT_NAME' => 'CAT_NAME',
      'CAT_ORDER' => 'CAT_ORDER',
      'CAT_STATUS' => 'CAT_STATUS',
    ),
    'info' => array(
      'CAT_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'CAT_NAME' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'CAT_ORDER' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'CAT_STATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => -1,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/tw/view/sp_portal_category');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  /*
   * View 'sp_portal_forum'
   */
  $view = new view;
  $view->name = 'sp_portal_forum';
  $view->description = 'sp_portal_forum';
  $view->tag = 'tw';
  $view->view_php = '';
  $view->base_table = 'sp_portal_forum';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'sp_portal_forum', 'default');
  $handler->override_option('fields', array(
    'CAT_ID' => array(
      'id' => 'CAT_ID',
      'table' => 'sp_portal_forum',
      'field' => 'CAT_ID',
      'label' => 'CAT_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_COUNT' => array(
      'id' => 'F_COUNT',
      'table' => 'sp_portal_forum',
      'field' => 'F_COUNT',
      'label' => 'F_COUNT',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_DESCRIPTION' => array(
      'id' => 'F_DESCRIPTION',
      'table' => 'sp_portal_forum',
      'field' => 'F_DESCRIPTION',
      'label' => 'F_DESCRIPTION',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_MAIL' => array(
      'id' => 'F_MAIL',
      'table' => 'sp_portal_forum',
      'field' => 'F_MAIL',
      'label' => 'F_MAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_PASSWORD_NEW' => array(
      'id' => 'F_PASSWORD_NEW',
      'table' => 'sp_portal_forum',
      'field' => 'F_PASSWORD_NEW',
      'label' => 'F_PASSWORD_NEW',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_PRIVATEFORUMS' => array(
      'id' => 'F_PRIVATEFORUMS',
      'table' => 'sp_portal_forum',
      'field' => 'F_PRIVATEFORUMS',
      'label' => 'F_PRIVATEFORUMS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_STATUS' => array(
      'id' => 'F_STATUS',
      'table' => 'sp_portal_forum',
      'field' => 'F_STATUS',
      'label' => 'F_STATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_SUBJECT' => array(
      'id' => 'F_SUBJECT',
      'table' => 'sp_portal_forum',
      'field' => 'F_SUBJECT',
      'label' => 'F_SUBJECT',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_TOPICS' => array(
      'id' => 'F_TOPICS',
      'table' => 'sp_portal_forum',
      'field' => 'F_TOPICS',
      'label' => 'F_TOPICS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_TYPE' => array(
      'id' => 'F_TYPE',
      'table' => 'sp_portal_forum',
      'field' => 'F_TYPE',
      'label' => 'F_TYPE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'F_URL' => array(
      'id' => 'F_URL',
      'table' => 'sp_portal_forum',
      'field' => 'F_URL',
      'label' => 'F_URL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'FORUM_ID' => array(
      'id' => 'FORUM_ID',
      'table' => 'sp_portal_forum',
      'field' => 'FORUM_ID',
      'label' => 'FORUM_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'FORUM_ORDER' => array(
      'id' => 'FORUM_ORDER',
      'table' => 'sp_portal_forum',
      'field' => 'FORUM_ORDER',
      'label' => 'FORUM_ORDER',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'L_ARCHIVE' => array(
      'id' => 'L_ARCHIVE',
      'table' => 'sp_portal_forum',
      'field' => 'L_ARCHIVE',
      'label' => 'L_ARCHIVE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'table wizard administration',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Contents of sp_portal_forum');
  $handler->override_option('header', 'This is a view of a raw database table. It may be sorted in various ways by clicking the column headers.

      If you identify a particular field that does not need to be used in views of this table, go to the <a href="/dev/druportal/admin/content/tw/analyze/13">analysis page</a> and check the <em>Ignore</em> box for that field. It will then no longer appear here.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty', 'There are no rows in this table.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'CAT_ID' => 'CAT_ID',
      'F_COUNT' => 'F_COUNT',
      'F_DESCRIPTION' => 'F_DESCRIPTION',
      'F_MAIL' => 'F_MAIL',
      'F_PASSWORD_NEW' => 'F_PASSWORD_NEW',
      'F_PRIVATEFORUMS' => 'F_PRIVATEFORUMS',
      'F_STATUS' => 'F_STATUS',
      'F_SUBJECT' => 'F_SUBJECT',
      'F_TOPICS' => 'F_TOPICS',
      'F_TYPE' => 'F_TYPE',
      'F_URL' => 'F_URL',
      'FORUM_ID' => 'FORUM_ID',
      'FORUM_ORDER' => 'FORUM_ORDER',
      'L_ARCHIVE' => 'L_ARCHIVE',
    ),
    'info' => array(
      'CAT_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_COUNT' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_DESCRIPTION' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_MAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_PASSWORD_NEW' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_PRIVATEFORUMS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_STATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_SUBJECT' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_TOPICS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_TYPE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'F_URL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'FORUM_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'FORUM_ORDER' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'L_ARCHIVE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => -1,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/tw/view/sp_portal_forum');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  /*
   * View 'sp_portal_reply'
   */
  $view = new view;
  $view->name = 'sp_portal_reply';
  $view->description = 'sp_portal_reply';
  $view->tag = 'tw';
  $view->view_php = '';
  $view->base_table = 'sp_portal_reply';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'sp_portal_reply', 'default');
  $handler->override_option('fields', array(
    'CAT_ID' => array(
      'id' => 'CAT_ID',
      'table' => 'sp_portal_reply',
      'field' => 'CAT_ID',
      'label' => 'CAT_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'FORUM_ID' => array(
      'id' => 'FORUM_ID',
      'table' => 'sp_portal_reply',
      'field' => 'FORUM_ID',
      'label' => 'FORUM_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_AUTHOR' => array(
      'id' => 'R_AUTHOR',
      'table' => 'sp_portal_reply',
      'field' => 'R_AUTHOR',
      'label' => 'R_AUTHOR',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_DATE' => array(
      'id' => 'R_DATE',
      'table' => 'sp_portal_reply',
      'field' => 'R_DATE',
      'label' => 'R_DATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_IP' => array(
      'id' => 'R_IP',
      'table' => 'sp_portal_reply',
      'field' => 'R_IP',
      'label' => 'R_IP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_MAIL' => array(
      'id' => 'R_MAIL',
      'table' => 'sp_portal_reply',
      'field' => 'R_MAIL',
      'label' => 'R_MAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_MESSAGE' => array(
      'id' => 'R_MESSAGE',
      'table' => 'sp_portal_reply',
      'field' => 'R_MESSAGE',
      'label' => 'R_MESSAGE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_MSGICON' => array(
      'id' => 'R_MSGICON',
      'table' => 'sp_portal_reply',
      'field' => 'R_MSGICON',
      'label' => 'R_MSGICON',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'R_SIG' => array(
      'id' => 'R_SIG',
      'table' => 'sp_portal_reply',
      'field' => 'R_SIG',
      'label' => 'R_SIG',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'REPLY_ID' => array(
      'id' => 'REPLY_ID',
      'table' => 'sp_portal_reply',
      'field' => 'REPLY_ID',
      'label' => 'REPLY_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'TOPIC_ID' => array(
      'id' => 'TOPIC_ID',
      'table' => 'sp_portal_reply',
      'field' => 'TOPIC_ID',
      'label' => 'TOPIC_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'table wizard administration',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Contents of sp_portal_reply');
  $handler->override_option('header', 'This is a view of a raw database table. It may be sorted in various ways by clicking the column headers.

      If you identify a particular field that does not need to be used in views of this table, go to the <a href="/dev/druportal/admin/content/tw/analyze/20">analysis page</a> and check the <em>Ignore</em> box for that field. It will then no longer appear here.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty', 'There are no rows in this table.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'CAT_ID' => 'CAT_ID',
      'FORUM_ID' => 'FORUM_ID',
      'R_AUTHOR' => 'R_AUTHOR',
      'R_DATE' => 'R_DATE',
      'R_IP' => 'R_IP',
      'R_MAIL' => 'R_MAIL',
      'R_MESSAGE' => 'R_MESSAGE',
      'R_MSGICON' => 'R_MSGICON',
      'R_SIG' => 'R_SIG',
      'REPLY_ID' => 'REPLY_ID',
      'TOPIC_ID' => 'TOPIC_ID',
    ),
    'info' => array(
      'CAT_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'FORUM_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_AUTHOR' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_DATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_IP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_MAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_MESSAGE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_MSGICON' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'R_SIG' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'REPLY_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'TOPIC_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => -1,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/tw/view/sp_portal_reply');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  /*
   * View 'sp_portal_topics'
   */
  $view = new view;
  $view->name = 'sp_portal_topics';
  $view->description = 'sp_portal_topics';
  $view->tag = 'tw';
  $view->view_php = '';
  $view->base_table = 'sp_portal_topics';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'sp_portal_topics', 'default');
  $handler->override_option('fields', array(
    'CAT_ID' => array(
      'id' => 'CAT_ID',
      'table' => 'sp_portal_topics',
      'field' => 'CAT_ID',
      'label' => 'CAT_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'FORUM_ID' => array(
      'id' => 'FORUM_ID',
      'table' => 'sp_portal_topics',
      'field' => 'FORUM_ID',
      'label' => 'FORUM_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_AUTHOR' => array(
      'id' => 'T_AUTHOR',
      'table' => 'sp_portal_topics',
      'field' => 'T_AUTHOR',
      'label' => 'T_AUTHOR',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_DATE' => array(
      'id' => 'T_DATE',
      'table' => 'sp_portal_topics',
      'field' => 'T_DATE',
      'label' => 'T_DATE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_INPLACE' => array(
      'id' => 'T_INPLACE',
      'table' => 'sp_portal_topics',
      'field' => 'T_INPLACE',
      'label' => 'T_INPLACE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_IP' => array(
      'id' => 'T_IP',
      'table' => 'sp_portal_topics',
      'field' => 'T_IP',
      'label' => 'T_IP',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_LAST_POST' => array(
      'id' => 'T_LAST_POST',
      'table' => 'sp_portal_topics',
      'field' => 'T_LAST_POST',
      'label' => 'T_LAST_POST',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_LAST_POST_AUTHOR' => array(
      'id' => 'T_LAST_POST_AUTHOR',
      'table' => 'sp_portal_topics',
      'field' => 'T_LAST_POST_AUTHOR',
      'label' => 'T_LAST_POST_AUTHOR',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_LAST_POSTER' => array(
      'id' => 'T_LAST_POSTER',
      'table' => 'sp_portal_topics',
      'field' => 'T_LAST_POSTER',
      'label' => 'T_LAST_POSTER',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_MAIL' => array(
      'id' => 'T_MAIL',
      'table' => 'sp_portal_topics',
      'field' => 'T_MAIL',
      'label' => 'T_MAIL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_MESSAGE' => array(
      'id' => 'T_MESSAGE',
      'table' => 'sp_portal_topics',
      'field' => 'T_MESSAGE',
      'label' => 'T_MESSAGE',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_MSGICON' => array(
      'id' => 'T_MSGICON',
      'table' => 'sp_portal_topics',
      'field' => 'T_MSGICON',
      'label' => 'T_MSGICON',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_NEWS' => array(
      'id' => 'T_NEWS',
      'table' => 'sp_portal_topics',
      'field' => 'T_NEWS',
      'label' => 'T_NEWS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_POLL' => array(
      'id' => 'T_POLL',
      'table' => 'sp_portal_topics',
      'field' => 'T_POLL',
      'label' => 'T_POLL',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_REPLIES' => array(
      'id' => 'T_REPLIES',
      'table' => 'sp_portal_topics',
      'field' => 'T_REPLIES',
      'label' => 'T_REPLIES',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_SIG' => array(
      'id' => 'T_SIG',
      'table' => 'sp_portal_topics',
      'field' => 'T_SIG',
      'label' => 'T_SIG',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_STATUS' => array(
      'id' => 'T_STATUS',
      'table' => 'sp_portal_topics',
      'field' => 'T_STATUS',
      'label' => 'T_STATUS',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_SUBJECT' => array(
      'id' => 'T_SUBJECT',
      'table' => 'sp_portal_topics',
      'field' => 'T_SUBJECT',
      'label' => 'T_SUBJECT',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'T_VIEW_COUNT' => array(
      'id' => 'T_VIEW_COUNT',
      'table' => 'sp_portal_topics',
      'field' => 'T_VIEW_COUNT',
      'label' => 'T_VIEW_COUNT',
      'exclude' => 0,
      'relationship' => 'none',
    ),
    'TOPIC_ID' => array(
      'id' => 'TOPIC_ID',
      'table' => 'sp_portal_topics',
      'field' => 'TOPIC_ID',
      'label' => 'TOPIC_ID',
      'exclude' => 0,
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'table wizard administration',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Contents of sp_portal_topics');
  $handler->override_option('header', 'This is a view of a raw database table. It may be sorted in various ways by clicking the column headers.

      If you identify a particular field that does not need to be used in views of this table, go to the <a href="/dev/druportal/admin/content/tw/analyze/16">analysis page</a> and check the <em>Ignore</em> box for that field. It will then no longer appear here.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty', 'There are no rows in this table.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'CAT_ID' => 'CAT_ID',
      'FORUM_ID' => 'FORUM_ID',
      'T_AUTHOR' => 'T_AUTHOR',
      'T_DATE' => 'T_DATE',
      'T_INPLACE' => 'T_INPLACE',
      'T_IP' => 'T_IP',
      'T_LAST_POST' => 'T_LAST_POST',
      'T_LAST_POST_AUTHOR' => 'T_LAST_POST_AUTHOR',
      'T_LAST_POSTER' => 'T_LAST_POSTER',
      'T_MAIL' => 'T_MAIL',
      'T_MESSAGE' => 'T_MESSAGE',
      'T_MSGICON' => 'T_MSGICON',
      'T_NEWS' => 'T_NEWS',
      'T_POLL' => 'T_POLL',
      'T_REPLIES' => 'T_REPLIES',
      'T_SIG' => 'T_SIG',
      'T_STATUS' => 'T_STATUS',
      'T_SUBJECT' => 'T_SUBJECT',
      'T_VIEW_COUNT' => 'T_VIEW_COUNT',
      'TOPIC_ID' => 'TOPIC_ID',
    ),
    'info' => array(
      'CAT_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'FORUM_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_AUTHOR' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_DATE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_INPLACE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_IP' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_LAST_POST' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_LAST_POST_AUTHOR' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_LAST_POSTER' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_MAIL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_MESSAGE' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_MSGICON' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_NEWS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_POLL' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_REPLIES' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_SIG' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_STATUS' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_SUBJECT' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'T_VIEW_COUNT' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'TOPIC_ID' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => -1,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/tw/view/sp_portal_topics');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  return $views;
}
