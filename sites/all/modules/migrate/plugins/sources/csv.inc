<?php
// $Id: csv.inc,v 1.1.2.4 2011/01/25 21:10:29 weitzman Exp $

/**
 * @file
 * Define a MigrateSource for importing from comma separated values file.
 */

/**
 * Implementation of MigrateSource, to handle imports from CVV file.
 */
class MigrateSourceCSV extends MigrateSource {
  /**
   * Number of eligible rows processed so far (used for itemlimit checking)
   *
   * @var int
   */
  protected $numProcessed = 0;

  /**
   * List of available source fields.
   *
   * @var array
   */
  protected $fields = array();
  
  /**
   * Parameters for the fgetcsv() call.
   *
   * @var array
   */
  protected $fgetcsv = array();

  protected $mapJoinable = FALSE;

  protected $usingHighwater = FALSE;

  /**
   * Simple initialization.
   *
   * @param atring $path
   *  The path to the source file
   * @param array $csvcolumns
   *  Keys are integers. values are array(field name, description).
   * @param array $options
   *  Options applied to this source.
   * @param array $fields
   *  Optional - keys are field names, values are descriptions. Use to override
   *  the default descriptions, or to add additional source fields which the
   *  migration will add via other means (e.g., prepareRow()).
   */
  public function __construct($path, array $csvcolumns = array(), array $options = array(), array $fields = array()) {
    parent::__construct();
    $this->file = $path;
    $this->csvcolumns = $csvcolumns;
    $this->options = $options;
    $this->fields = $fields;
    // fgetcsv specific options
    foreach (array('length' => NULL, 'delimiter' => ',', 'enclosure' => '"', 'escape' => '\\') as $key => $default) {
      $this->fgetcsv[$key] = isset($options[$key]) ? $options[$key] : $default;
    }
  }


  /**
   * Return a string representing the source query.
   *
   * @return string
   */
  public function __toString() {
    return $this->file;
  }

  /**
   * Returns a list of fields available to be mapped from the source query.
   *
   * @return array
   *  Keys: machine names of the fields (to be passed to addFieldMapping)
   *  Values: Human-friendly descriptions of the fields.
   */
  public function fields() {
    foreach ($this->csvcolumns as $int => $values) {
      $fields[$values[0]] = $values[1];
    }
    
    // Any caller-specified fields with the same names as extracted fields will
    // override them; any others will be added
    if ($this->fields) {
      $fields = $this->fields + $fields;
    }
    
    return $fields;
  }

  /**
   * Return a count of all available source records.
   *
   * @param boolean $refresh
   *  If TRUE, or if there is no cached count, perform a SQL COUNT query to
   *  retrieve and cache the number of rows in the query. Otherwise, return
   *  the last cached value.
   *
   *  TODO: Implement caching
   */
  public function count($refresh = FALSE) {
    // TODO. If this takes too much time/memory, use exec('wc -l')
    $count = count(file($this->file));
    return $count;
  }

  /**
   * Implementation of Iterator::rewind() - called before beginning a foreach loop.
   */
  public function rewind() {
    $migration = Migration::currentMigration();
    $this->result = NULL;
    $this->currentRow = NULL;
    $this->numProcessed = 0;
    

    migrate_instrument_start('MigrateSourceCSV execute');
    $this->result = fopen($this->file, 'r');
    migrate_instrument_stop('MigrateSourceCSV execute');

    // Load up the first row
    $this->next();
  }

  /**
   * Implementation of Iterator::next() - called at the bottom of the loop implicitly,
   * as well as explicitly from rewind().
   */
  public function next() {
    $migration = Migration::currentMigration();
    $this->currentRow = NULL;
    $this->currentKey = NULL;
    // If we couldn't add the itemlimit to the query directly, enforce it here
    if (!$this->mapJoinable) {
      $itemlimit = $migration->getOption('itemlimit');
      if ($itemlimit && $this->numProcessed >= $itemlimit) {
        return;
      }
    }

    // get next row
    migrate_instrument_start('MigrateSourceCSV next');
    $map = $migration->getMap();
    // @todo $this->fgetcsv['escape'] not used as it gives warning in 5.2 - http://drupal.org/node/1039808.
    while ($row = fgetcsv($this->result, $this->fgetcsv['length'], $this->fgetcsv['delimiter'], $this->fgetcsv['enclosure'])) {
      // Set meaningful keys for the columns mentioned in $this->csvcolumns().
      foreach ($this->csvcolumns as $int => $values) {
        list($key, $description) = $values;
        // Copy value to more descriptive string based key and then unset original.
        $row[$key] = $row[$int];
        unset($row[$int]);
      }
      $this->currentRow = (object) $row;
      
      foreach ($map->getSourceKey() as $field_name => $field_schema) {
        $this->currentKey[$field_name] = $this->currentRow->$field_name;
      }

      if (!$this->mapJoinable) {
        $map_row = $migration->getMap()->getRowBySource($this->currentKey);
        if (!$map_row) {
          // Unmigrated row, take it
        }
        elseif ($map_row && $map_row['needs_update'] == 1) {
          // We always want to take this row if needs_update = 1
        }
        else {
          if ($this->usingHighwater) {
            // With highwater, we want to take this row if it's above the highwater
            // mark
            $highwaterField = $migration->getHighwaterField();
            $highwaterField = $highwaterField['name'];
            if ($this->currentRow->$highwaterField <= $migration->getHighwater()) {
              continue;
            }
          }
          else {
            // With no highwater, we want to take this row if it's not in the map table
            if ($map_row) {
              continue;
            }
          }
        }
        // Add map info to the row, if present
        if ($map_row) {
          foreach ($map_row as $field => $value) {
            $field = 'migrate_map_' . $field;
            $this->currentRow->$field = $value;
          }
        }
      }

      // Add some debugging, just for the first row.
      if (empty($this->numProcessed)) {
        $migration->showMessage(print_r($this->currentRow, TRUE));
      }

      // Allow the Migration to prepare this row. prepareRow() can return boolean
      // FALSE to stop processing this row. To add/modify fields on the
      // result, modify $row by reference.
      $return = TRUE;
      if (method_exists($migration, 'prepareRow')) {
        $return = $migration->prepareRow($this->currentRow);
      }

      if ($return !== FALSE) {
        $this->numProcessed++;
        break;
      }
    }
    if (!is_object($this->currentRow)) {
      $this->currentRow = NULL;
    }
    migrate_instrument_stop('MigrateSourceCSV next');
  }
}
