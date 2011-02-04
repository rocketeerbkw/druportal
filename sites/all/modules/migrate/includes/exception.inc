<?php
// $Id: exception.inc,v 1.1.2.3 2010/05/26 02:33:56 mikeryan Exp $

/**
 * @file
 * Custom exception class for the migrate module.
 */

class MigrateException extends Exception {
  protected $level;
  public function getLevel() {
    return $this->level;
  }

  public function __construct($message, $level = Migration::MESSAGE_ERROR) {
    $this->level = $level;
    parent::__construct($message);
  }
}
