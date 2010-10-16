<?php

/**
 * Implementation of hook_views_default_views().
 **/
function druportal_views_default_views()
{
  $views = array();

  $views = array_merge($views, druportal_views_default_views_forums());

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
