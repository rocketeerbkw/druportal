<?php
// $Id: migration.inc,v 1.1.2.138 2011/02/12 20:35:46 mikeryan Exp $

/**
 * @file
 * Defines the base class for import/rollback processes.
 */

/**
 * The base class for all import objects. This is where most of the smarts
 * of the migrate module resides. Migrations are created by deriving from this
 * class, and in the constructor (after calling parent::__construct()) initializing
 * at a minimum the name, description, source, and destination properties. The constructor
 * will also usually make several calls to addFieldMapping().
 */
abstract class Migration extends MigrationBase {
  /**
   * Source object for the migration, derived from MigrateSource.
   *
   * @var MigrateSource
   */
  protected $source;
  public function getSource() {
    return $this->source;
  }

  /**
   * Destination object for the migration, derived from MigrateDestination.
   *
   * @var MigrateDestination
   */
  protected $destination;
  public function getDestination() {
    return $this->destination;
  }

  /**
   * Map object tracking relationships between source and destination data
   *
   * @var MigrateMap
   */
  protected $map;
  public function getMap() {
    return $this->map;
  }

  /**
   * Indicate whether the primary system of record for this migration is the
   * source, or the destination (Drupal). In the source case, migration of
   * an existing object will completely replace the Drupal object with data from
   * the source side. In the destination case, the existing Drupal object will
   * be loaded, then changes from the source applied; also, rollback will not be
   * supported.
   *
   * @var int
   */
  const SOURCE = 1;
  const DESTINATION = 2;
  protected $systemOfRecord = Migration::SOURCE;
  public function getSystemOfRecord() {
    return $this->systemOfRecord;
  }

  /**
   * Specify value of needs_update for current map row. Usually set by
   * MigrateFieldHandler implementations.
   *
   * @var boolean
   */
  public $needsUpdate = FALSE;

  /**
   * Simple mappings between destination fields (keys) and source fields (values).
   *
   * @var array
   */
  protected $fieldMappings = array();
  public function getFieldMappings() {
    return $this->fieldMappings;
  }

  /**
   * An array of counts. Initially used for cache hit/miss tracking.
   *
   * @var array
   */
  protected $counts = array();

  /**
   * When performing a bulkRollback(), the maximum number of items to pass in
   * a single call. Can be overridden in derived class constructor.
   *
   * @var int
   */
  protected $rollbackBatchSize = 500;

  /**
   * If present, an array with keys name and alias (optional). Name refers to
   * the source columns used for tracking highwater marks. alias is an
   * optional table alias.
   *
   * @var array
   */
  protected $highwaterField = array();
  public function getHighwaterField() {
    return $this->highwaterField;
  }

  protected $currentSourceKey;

  /**
   * The object currently being constructed
   * @var stdClass
   */
  protected $destinationValues;

  /**
   * The current data row retrieved from the source.
   * @var stdClass
   */
  protected $sourceValues;

  /**
   * General initialization of a Migration object.
   */
  public function __construct() {
    parent::__construct();
  }

  /**
   * Deregister a migration - remove all traces of it from the database (without
   * touching any content which was created by this migration).
   *
   * We'd like to do this at uninstall time, but the implementing module is
   * already disabled, so we can't instantiate it to get at the map. This can
   * be done in hook_disable(), however.
   *
   * @param string $machine_name
   */
  static public function deregisterMigration($machine_name) {
    try {
      // Remove map and message tables
      $migration = self::getInstance($machine_name);
      $migration->map->destroy();

      // TODO: Clear log entries? Or keep for historical purposes?

      // Call the parent deregistration (which clears migrate_status) last, the
      // above will reference it.
      parent::deregisterMigration($machine_name);
    }
    catch (Exception $e) {
      // Fail silently if it's already gone
    }
  }

  ////////////////////////////////////////////////////////////////////
  // Processing

  /**
   * Add a mapping for a destination field, specifying a source field and/or
   * a default value.
   *
   * @param string $destinationField
   *  Name of the destination field.
   * @param string $sourceField
   *  Name of the source field (optional).
   */
  protected function addFieldMapping($destination_field, $source_field = NULL) {
    // Warn of duplicate mappings
    if (!is_null($destination_field) && isset($this->fieldMappings[$destination_field])) {
      $this->showMessage(
        t('!name addFieldMapping: !dest was previously mapped, overridden',
          array('!name' => $this->machineName, '!dest' => $destination_field)),
        'warning');
    }
    $mapping = new MigrateFieldMapping($destination_field, $source_field);
    if (is_null($destination_field)) {
      $this->fieldMappings[] = $mapping;
    }
    else {
      $this->fieldMappings[$destination_field] = $mapping;
    }
    return $mapping;
  }

  /**
   * Remove any existing mappings for a given destination or source field.
   *
   * @param string $destination_field
   *  Name of the destination field.
   * @param string $source_field
   *  Name of the source field.
   */
  protected function removeFieldMapping($destination_field, $source_field = NULL) {
    if (isset($destination_field)) {
      unset($this->fieldMappings[$destination_field]);
    }
    if (isset($source_field)) {
      foreach ($this->fieldMappings as $key => $mapping) {
        if ($mapping->getSourceField() == $source_field) {
          unset($this->fieldMappings[$key]);
        }
      }
    }
  }

  /**
   * Reports whether this migration process is complete (i.e., all available
   * source rows have been processed).
   */
  public function isComplete() {
    $total = $this->source->count(TRUE);
    $imported = $this->importedCount();
    $errors = $this->errorCount();
    return $total <= ($imported + $errors);
  }

  /**
   * Override MigrationBase::beginProcess, to make sure the map/message tables
   * are present.
   *
   * @param int $newStatus
   *  Migration::STATUS_IMPORTING or Migration::STATUS_ROLLING_BACK
   */
  protected function beginProcess($newStatus) {
    parent::beginProcess($newStatus);

    // Do some standard setup
    if (isset($this->options['feedback']) && isset($this->options['feedback']['frequency']) &&
        isset($this->options['feedback']['frequency_unit'])) {
      $this->frequency = $this->options['feedback']['frequency'];
      $this->frequency_unit = $this->options['feedback']['frequency_unit'];
    }
    $this->lastfeedback = $this->starttime;

    $this->total_processed = $this->total_successes =
      $this->processed_since_feedback = $this->successes_since_feedback = 0;

    // Call pre-process methods
    if ($this->status == Migration::STATUS_IMPORTING) {
      $this->preImport();
    }
    else {
      $this->preRollback();
    }
  }

  /**
   * Override MigrationBase::endProcess, to call post hooks. Note that it must
   * be public to be callable as the shutdown function.
   */
  public function endProcess() {
    // Call post-process methods
    if ($this->status == Migration::STATUS_IMPORTING) {
      $this->postImport();
    }
    else {
      $this->postRollback();
    }

    parent::endProcess();
  }

  /**
   * Default implementations of pre/post import/rollback methods. These call
   * the destination methods (if they exist) - when overriding, always
   * call parent::preImport() etc.
   */
  protected function preImport() {
    if (method_exists($this->destination, 'preRollback')) {
      $this->destination->preImport();
    }
  }

  protected function preRollback() {
    if (method_exists($this->destination, 'preRollback')) {
      $this->destination->preRollback();
    }
  }

  protected function postImport() {
    if (method_exists($this->destination, 'postImport')) {
      $this->destination->postImport();
    }
  }

  protected function postRollback() {
    if (method_exists($this->destination, 'postRollback')) {
      $this->destination->postRollback();
    }
  }

  /**
   * Perform a rollback operation - remove migrated items from the destination.
   */
  protected function rollback() {
    $return = MigrationBase::RESULT_COMPLETED;
    $itemlimit = $this->getOption('itemlimit');
    $idlist = $this->getOption('idlist');
    if ($idlist) {
      // Make the IDs keys, to more easily identify them
      $idlist = array_flip(explode(',', $idlist));
    }

    if (method_exists($this->destination, 'bulkRollback')) {
      // Too many at once can lead to memory issues, so batch 'em up
      $destids = array();
      $sourceids = array();
      $batch_count = 0;
      foreach ($this->map as $destination_key) {
        if (($return = $this->checkStatus()) != MigrationBase::RESULT_COMPLETED) {
          break;
        }

        if ($itemlimit && ($this->total_processed + $batch_count >= $itemlimit)) {
          break;
        }

        $this->currentSourceKey = $this->map->getCurrentKey();

        // If there's an idlist, skip anything not in the list
        if ($idlist && !isset($idlist[$this->currentSourceKey['sourceid1']])) {
          continue;
        }

        // Note that bulk rollback is only supported for single-column keys
        $sourceids[] = $this->currentSourceKey;
        $destids[] = $destination_key->destid1;

        $batch_count++;
        if ($batch_count >= $this->rollbackBatchSize) {
          try {
            if ($this->systemOfRecord == Migration::SOURCE) {
              migrate_instrument_start('destination bulkRollback');
              $this->destination->bulkRollback($destids);
              migrate_instrument_stop('destination bulkRollback');
            }
            // Keep track in case of interruption
            migrate_instrument_start('rollback map/message update');
            $this->map->deleteBulk($sourceids);
            migrate_instrument_stop('rollback map/message update');
            $this->total_successes += $batch_count;
            $this->successes_since_feedback += $batch_count;
          }
          catch (Exception $e) {
            $this->showMessage($e->getMessage());
            migrate_instrument_stop('bulkRollback');
            migrate_instrument_stop('rollback map/message update');
          }
          $destids = array();
          $sourceids = array();
          $batch_count = 0;
          // Will increment even if there was an exception... But we don't
          // really have a way to know how many really were successfully rolled back
          $this->total_processed += $batch_count;
          $this->processed_since_feedback += $batch_count;
        }
      }
      if ($batch_count > 0) {
        if ($this->systemOfRecord == Migration::SOURCE) {
          migrate_instrument_start('destination bulkRollback');
          $this->destination->bulkRollback($destids);
          migrate_instrument_stop('destination bulkRollback');
          $this->total_processed += $batch_count;
          $this->total_successes += $batch_count;
          $this->processed_since_feedback += $batch_count;
          $this->successes_since_feedback += $batch_count;
        }
        migrate_instrument_start('rollback map/message update');
        $this->map->deleteBulk($sourceids);
        migrate_instrument_stop('rollback map/message update');
      }
    }
    else {
      foreach ($this->map as $destination_key) {
        if (($return = $this->checkStatus()) != MigrationBase::RESULT_COMPLETED) {
          break;
        }
        if ($itemlimit && ($this->total_processed >= $itemlimit)) {
          break;
        }
        $this->currentSourceKey = $this->map->getCurrentKey();

        // If there's an idlist, skip anything not in the list
        if ($idlist && !isset($idlist[$this->currentSourceKey['sourceid1']])) {
          continue;
        }

        // Rollback one record
        try {
          if ($this->systemOfRecord == Migration::SOURCE) {
            migrate_instrument_start('destination rollback');
            $this->destination->rollback((array)$destination_key);
            migrate_instrument_stop('destination rollback');
          }

          migrate_instrument_start('rollback map/message update');
          $this->map->delete($this->currentSourceKey);
          migrate_instrument_stop('rollback map/message update');
          $this->total_successes++;
          $this->successes_since_feedback++;
        }
        catch (Exception $e) {
          // TODO: At least count failures
          continue;
        }
        $this->total_processed++;
        $this->processed_since_feedback++;
      }
    }

    $this->map->clearMessages();

    $this->progressMessage($return);

    // If we're using highwater marks, reset at completion of a full rollback
    // TODO: What about partial rollbacks? Probably little we can do to make
    // that work cleanly...
    if ($this->highwaterField) {
      $this->saveHighwater('', TRUE);
    }
    return $return;
  }

  /**
   * Perform an import operation - migrate items from source to destination.
   */
  protected function import() {
    $return = MigrationBase::RESULT_COMPLETED;

    foreach ($this->source as $data_row) {
      if (($return = $this->checkStatus()) != MigrationBase::RESULT_COMPLETED) {
        break;
      }

      $this->currentSourceKey = $this->source->getCurrentKey();

      $this->sourceValues = $data_row;
      $this->applyMappings();

      try {
        // Wipe old messages
        $this->map->delete($this->currentSourceKey, TRUE);

        migrate_instrument_start('destination import', TRUE);
        $ids = $this->destination->import($this->destinationValues, $this->sourceValues);
        migrate_instrument_stop('destination import');
        if ($ids) {
          $this->map->saveIDMapping($this->sourceValues, $ids, $this->needsUpdate);
          $this->successes_since_feedback++;
          $this->total_successes++;
        }
        else {
          $message = t('New object was not saved, no error provided');
          $this->saveMessage($message);
          $this->showMessage($message);
        }
      }
      catch (MigrateException $e) {
        $this->saveMessage($e->getMessage(), $e->getLevel());
        $this->showMessage($e->getMessage());
      }
      catch (Exception $e) {
        $this->saveMessage($e->getMessage());
        $this->showMessage($e->getMessage());
      }
      $this->total_processed++;
      $this->processed_since_feedback++;
      if ($this->highwaterField) {
        $this->saveHighwater($this->sourceValues->{$this->highwaterField['name']});
      }

      // Reset row properties.
      unset($this->sourceValues, $this->destinationValues);
      $this->needsUpdate = FALSE;

      // TODO: Temporary. Remove when http://drupal.org/node/375494 is committed.
      // TODO: Should be done in MigrateDestinationEntity
      if (!empty($this->destination->entityType)) {
        entity_get_controller($this->destination->entityType)->resetCache();
      }
    }

    $this->progressMessage($return);

    return $return;
  }

  ////////////////////////////////////////////////////////////////////
  // Utility methods

  /**
   * Convenience function to return count of total source records
   *
   * @param boolean $refresh
   *  Pass TRUE to refresh the cached count.
   */
  public function sourceCount($refresh = FALSE) {
    return $this->source->count($refresh);
  }

  /**
   * Get the number of records successfully imported.
   * @return int
   *  Number of imported records.
   */
  public function importedCount() {
    return $this->map->importedCount();
  }

  /**
   * Get the number of source records which failed to import.
   * TODO: Doesn't yet account for informationals, or multiple errors for
   * a source record.
   *
   * @return int
   *  Number of records errored out.
   */
  public function errorCount() {
    return $this->map->errorCount();
  }

  /**
   * Get the number of messages associated with this migration
   *
   * @return int
   *  Number of messages.
   */
  public function messageCount() {
    return $this->map->messageCount();
  }

  /**
   * Prepares this migration to run as an update - that is, in addition to
   * unmigrated content (source records not in the map table) being imported,
   * previously-migrated content will also be updated in place.
   */
  public function prepareUpdate() {
    $this->map->prepareUpdate();
  }

  /**
   * Outputs a progress message, reflecting the current status of a migration process.
   *
   * @param int $result
   *  Status of the process, represented by one of the Migration::RESULT_* constants.
   */
  protected function progressMessage($result) {
    // In the INCOMPLETE (feedback) case, only proceed under the proper conditions
    if ($result == Migration::RESULT_INCOMPLETE) {
      if (isset($this->frequency)) {
        if (($this->frequency_unit == 'seconds' && time()-$this->lastfeedback >= $this->frequency) ||
            ($this->frequency_unit == 'items' && $this->processed_since_feedback >= $this->frequency)) {
          // Fall through
        }
        else {
          return;
        }
      }
      else {
        return;
      }
    }

    $time = microtime(TRUE) - $this->lastfeedback;
    if ($time > 0) {
      $perminute = round(60*$this->processed_since_feedback/$time);
      $time = round($time, 1);
    }
    else {
      $perminute = '?';
    }

    if ($this->status == Migration::STATUS_IMPORTING) {
      switch ($result) {
        case Migration::RESULT_COMPLETED:
          $basetext = "Imported !successes (!failed failed) in !time sec (!perminute/min) - done with '!name'";
          $type = 'completed';
          break;
        case Migration::RESULT_FAILED:
          $basetext = "Imported !successes (!failed failed) in !time sec (!perminute/min) - failure with '!name'";
          $type = 'failed';
          break;
        case Migration::RESULT_INCOMPLETE:
          $basetext = "Imported !successes (!failed failed) in !time sec (!perminute/min) - continuing with '!name'";
          $type = 'ok';
          break;
        case Migration::RESULT_STOPPED:
          $basetext = "Imported !successes (!failed failed) in !time sec (!perminute/min) - stopped '!name'";
          $type = 'warning';
          break;
      }
    }
    else {
      switch ($result) {
        case Migration::RESULT_COMPLETED:
          $basetext = "Rolled back !numitems in !time sec (!perminute/min) - done with '!name'";
          $type = 'completed';
          break;
        case Migration::RESULT_FAILED:
          $basetext = "Rolled back !numitems in !time sec (!perminute/min) - failure with '!name'";
          $type = 'failed';
          break;
        case Migration::RESULT_INCOMPLETE:
          $basetext = "Rolled back !numitems in !time sec (!perminute/min) - continuing with '!name'";
          $type = 'ok';
          break;
        case Migration::RESULT_STOPPED:
          $basetext = "Rolled back !numitems in !time sec (!perminute/min) - stopped '!name'";
          $type = 'warning';
          break;
      }
    }
    $message = t($basetext,
        array('!numitems' => $this->processed_since_feedback,
              '!successes' => $this->successes_since_feedback,
              '!failed' => $this->processed_since_feedback - $this->successes_since_feedback,
              '!time' => $time,
              '!perminute' => $perminute,
              '!name' => $this->machineName));
    $this->showMessage($message, $type);

    // Report on lookup_cache hit rate. Only visible at 'debug' level.
    if ($result != Migration::RESULT_INCOMPLETE && !empty($this->counts['lookup_cache'])) {
      foreach ($this->counts['lookup_cache'] as $name => $tallies) {
        $tallies += array('hit' => 0, 'miss_hit' => 0, 'miss_miss' => 0); // Set defaults to avoid NOTICE.
        $sum = $tallies['hit']+$tallies['miss_hit']+$tallies['miss_miss'];
        $this->showMessage(
          t('Lookup cache: !mn SM=!name !hit hit, !miss_hit miss_hit, !miss_miss miss_miss (!total total).', array(
                '!mn' => $this->machineName,
                '!name' => $name,
                '!hit' => round((100*$tallies['hit'])/$sum) . '%',
                '!miss_hit' => round((100*$tallies['miss_hit'])/$sum) . '%',
                '!miss_miss' => round((100*$tallies['miss_miss'])/$sum) . '%',
                '!total' => $sum
        )), 'debug');
      }
      $this->counts['lookup_cache'] = array();
    }
    if ($result == Migration::RESULT_INCOMPLETE) {
      $this->lastfeedback = time();
      $this->processed_since_feedback = $this->successes_since_feedback = 0;
    }
  }

  /**
   * Standard top-of-loop stuff, common between rollback and import - check
   * for exceptional conditions, and display feedback.
   */
  protected function checkStatus() {
    if ($this->memoryExceeded()) {
      return MigrationBase::RESULT_INCOMPLETE;
    }
    if ($this->timeExceeded()) {
      return MigrationBase::RESULT_INCOMPLETE;
    }
    if ($this->getStatus() == Migration::STATUS_STOPPING) {
      return MigrationBase::RESULT_STOPPED;
    }
    $this->progressMessage(MigrationBase::RESULT_INCOMPLETE);
    return MigrationBase::RESULT_COMPLETED;
  }

  /**
   * Apply field mappings to a data row received from the source, returning
   * a populated destination object.
   */
  protected function applyMappings() {
    // Apply mappings.
    $this->destinationValues = new stdClass;
    foreach ($this->fieldMappings as $mapping) {
      $destination = $mapping->getDestinationField();
      // Skip mappings with no destination (source fields marked DNM)
      if ($destination) {
        $source = $mapping->getSourceField();
        $default = $mapping->getDefaultValue();
        // If there's a source mapping, and a source value in the data row, copy
        // to the destination
        if ($source && isset($this->sourceValues->$source)) {
          $this->destinationValues->$destination = $this->sourceValues->$source;
        }
        // Otherwise, apply the default value (if any)
        elseif (!is_null($default)) {
          $this->destinationValues->$destination = $default;
        }

        // If there's a separator specified for this destination, then it
        // will be populated as an array exploded from the source value
        $separator = $mapping->getSeparator();
        if ($separator && isset($this->destinationValues->$destination)) {
          $this->destinationValues->$destination = explode($separator, $this->destinationValues->$destination);
        }

        // If a source migration is supplied, use the current value for this field
        // to look up a destination ID from the provided migration
        $source_migration = $mapping->getSourceMigration();
        if ($source_migration && isset($this->destinationValues->$destination)) {
          $this->destinationValues->$destination = $this->handleSourceMigration($source_migration, $this->destinationValues->$destination, $default, $this);
        }

        // If specified, assure a unique value for this property.
        $dedupe = $mapping->getDedupe();
        if ($dedupe && isset($this->destinationValues->$destination)) {
          $this->destinationValues->$destination = $this->handleDedupe($dedupe, $this->destinationValues->$destination, $mapping);
        }

        // Assign any arguments
        if (isset($this->destinationValues->$destination)) {
          $arguments = $mapping->getArguments();
          if ($arguments) {
            if (!is_array($this->destinationValues->$destination)) {
              $this->destinationValues->$destination = array($this->destinationValues->$destination);
            }
            // TODO: Stuffing arguments into the destination field is gross - can
            // we come up with a better way to communicate them to the field
            // handlers?
            $this->destinationValues->{$destination}['arguments'] = array();
            foreach ($arguments as $argname => $destarg) {
              if (is_array($destarg) && isset($destarg['source_field']) && isset($this->sourceValues->$destarg['source_field'])) {
                $this->destinationValues->{$destination}['arguments'][$argname] = $this->sourceValues->$destarg['source_field'];
              }
              elseif (is_array($destarg) && isset($destarg['default_value'])) {
                $this->destinationValues->{$destination}['arguments'][$argname] = $destarg['default_value'];
              }
              else {
                $this->destinationValues->{$destination}['arguments'][$argname] = $destarg;
              }
            }
          }
        }

        // When we're updating existing nodes, if there is a source mapping but there
        // was no value for this row, add a null destination value so it gets removed
        // from the node
        if ($this->systemOfRecord == Migration::DESTINATION && $source && !isset($this->destinationValues->$destination)) {
          $this->destinationValues->$destination = NULL;
        }
      }
    }
  }

  /**
   * Look up a value migrated in another migration.
   *
   * @param mixed $source_migrations
   *   An array of source migrations, or string for a single migration.
   * @param mixed $source_values
   *   An array of source values, or string for a single value.
   * @param mixed $default
   *   The default value, if no ID was found.
   * @param $migration
   *   The implementing migration.
   */
  protected function handleSourceMigration($source_migrations, $source_values, $default = NULL, $migration) {
    // Ensure source migrations and source keys are arrays.
    $source_migrations = (array) $source_migrations;
    $source_keys = (array) $source_values;

    // Instantiate each migration, and store back in the array.
    foreach ($source_migrations as $key => $source_migration) {
      $source_migrations[$key] = Migration::getInstance($source_migration);
    }

    $results = array();
    foreach ($source_keys as $source_key) {
      if (is_null($source_key)) {
        continue;
      }
      // Loop through each source migration, checking for an existing dest ID.
      foreach ($source_migrations as $source_migration) {
        // Break out of the loop as soon as a destination ID is found.
        if ($destids = $source_migration->getMap()->lookupDestinationID(array($source_key), $this)) {
          break;
        }
      }
      // If no destination ID was found, give each source migration a chance to
      // create a stub.
      if (!$destids) {
        foreach ($source_migrations as $source_migration) {
          // Break out of the loop if a stub was successfully created.
          if ($destids = $source_migration->createStubWrapper(array($source_key), $migration)) {
            break;
          }
        }
      }
      if ($destids) {
        // Assume that if the destination key is a single value, it
        // should be passed as such
        if (count($destids) == 1) {
          $results[] = reset($destids);
        }
        else {
          $results[] = $destids;
        }
      }
      // If no match found, apply the default value (if any)
      elseif (!is_null($default)) {
        $results[] = $default;
      }
    }
    if (is_array($source_values) || count($results) > 1) {
      return $results;
    }
    else {
      return $results[0];
    }
  }

  /**
   * Assign a non-existing value for current mapping.
   */
  protected function handleDedupe($dedupe, $original, $mapping) {
    $i = 1;
    $candidate = $original;
    while ($candidate_found = db_select($dedupe['table'], 't')
                      ->fields('t', array($dedupe['column']))
                      ->range(0, 1)
                      ->condition('t.' . $dedupe['column'], $candidate)
                      ->execute()
                      ->fetchField()) {
      // We already have the candidate value. Find a non-existing value.
      $i++;
      // @TODO: support custom replacement pattern instead of just append.
      $candidate = $original . '_' . $i;
    }
    if ($i > 1) {
      $message = t('Replacing !column !original with !candidate',
                 array('!column' => $dedupe['column'],
                       '!original' => $original,
                       '!candidate' => $candidate));
      $migration = Migration::currentMigration();
      $migration->saveMessage($message, Migration::MESSAGE_INFORMATIONAL);
    }
    return $candidate;
  }

  /**
   * If stub creation is enabled, try to create a stub and save the mapping.
   */
  protected function createStubWrapper(array $source_key, $migration) {
    if (method_exists($this, 'createStub')) {
      $destids = $this->createStub($migration);
      if ($destids) {
        // Fake a data row with the source key in it
        $map_source_key = $this->map->getSourceKey();
        $data_row = new stdClass;
        $i = 0;
        foreach ($map_source_key as $key => $definition) {
          $data_row->$key = $source_key[$i++];
        }
        $this->map->saveIDMapping($data_row, $destids, TRUE);
      }
    }
    else {
      $destids = NULL;
    }
    return $destids;
  }

  /**
   * Pass messages through to the map class
   *
   * @param string $message
   *  The message to record.
   * @param int $level
   *  Optional message severity (defaults to MESSAGE_ERROR).
   */
  public function saveMessage($message, $level = MigrationBase::MESSAGE_ERROR) {
    $output = $this->map->saveMessage($this->currentSourceKey, $message, $level);
  }

  /**
   * Set the specified row to be updated, if it exists.
   */
  public function setUpdate(array $source_key = NULL) {
    if (!$source_key) {
      $source_key = $this->currentSourceKey;
    }
    $this->map->setUpdate($source_key);
  }
}

/**
 * Convenience class - deriving from this rather than directory from Migration
 * ensures that a class will not be registered as a migration itself - it is
 * the implementor's responsibility to register each instance of a dynamic
 * migration class.
 */
abstract class DynamicMigration extends Migration {
  /**
   * Overrides default of FALSE
   */
  static public function isDynamic() {
    return TRUE;
  }
}
