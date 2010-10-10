<?php

/**
 * Implementation of hook_node_info().
 */
function druportal_announcements_node_info() {
  $items = array(
    'announcement' => array(
      'name' => t('Announcement'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Subject'),
      'has_body' => '1',
      'body_label' => t('Message'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function druportal_announcements_views_api() {
  return array(
    'api' => '2',
  );
}
