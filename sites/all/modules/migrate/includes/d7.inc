<?php
// $Id: d7.inc,v 1.1.2.6 2010/12/22 01:41:03 mikeryan Exp $

/**
 * @file
 * Drupal 7 functions 'n' things implemented in Drupal 6, to ease backporting
 */

define('LANGUAGE_NONE', 'und');

function node_type_set_defaults($info) {
  return (object)_node_type_set_defaults($info);
}

function node_type_load($type) {
  static $node_types;
  if (!isset($node_types)) {
    $node_types = node_get_types();
  }
  return $node_types[$type];
}

function taxonomy_vocabulary_save(&$vocabulary) {
  if (!is_array($vocabulary)) {
    $vocabulary = (array)$vocabulary;
  }
  return taxonomy_save_vocabulary($vocabulary);
}

function taxonomy_term_load($tid) {
  return (object)taxonomy_get_term($tid);
}

function user_delete_multiple($uids) {
  foreach ($uids as $uid) {
    user_delete(array(), $uid);
  }
}

function comment_delete_multiple($cids) {
  require_once drupal_get_path('module', 'comment') . '/comment.admin.inc';
  foreach ($cids as $cid) {
    comment_delete($cid);
  }
}

function filter_fallback_format() {
  return FILTER_FORMAT_DEFAULT;
}
