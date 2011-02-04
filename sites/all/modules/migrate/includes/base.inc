<?php
// $Id: base.inc,v 1.1.2.30 2010/12/22 01:25:42 mikeryan Exp $

/**
 * @file
 * Defines the base class for migration processes.
 */

/**
 * The base class for all objects representing distinct steps in a migration
 * process. Most commonly these will be Migration objects which actually import
 * data from a source into a Drupal destination, but by deriving classes directly
 * from MigrationBase one can have other sorts of tasks (e.g., enabling/disabling
 * of modules) occur during the migration process.
 */
abstract class MigrationBase {
  /**
   * Singleton-lite implementation - callers should call static getInstance() so
   * only one copy of a given Migration class is instantiated.
   *
   * @var array
   *  List of migration objects keys by class name.
   */
  protected static $migrations = array();

  protected static $currentMigration;
  public static function currentMigration() {
    return self::$currentMigration;
  }

  /**
   * The machine name of this Migration object, derived by removing the 'Migration'
   * suffix from the class name. Used to construct default map/message table names,
   * displayed in drush migrate-status, key to migrate_status table...
   *
   * @var string
   */
  protected $machineName;
  public function getMachineName() {
    return $this->machineName;
  }

  /**
   * Detailed information describing the migration.
   *
   * @var string
   */
  protected $description;
  public function getDescription() {
    return $this->description;
  }

  /**
   * Save options passed to current operation
   * @var array
   */
  protected $options;
  public function getOption($option_name) {
    if (isset($this->options[$option_name])) {
      return $this->options[$option_name];
    }
    else {
      return NULL;
    }
  }

  /**
   * Indicates that we are processing a rollback or import - used to avoid
   * excess writes in endProcess()
   *
   * @var boolean
   */
  protected $processing = FALSE;

  /**
   * Are we importing, rolling back, or doing nothing?
   *
   * @var enum
   */
  protected $status = MigrationBase::STATUS_IDLE;

  /**
   * When the current operation started.
   * @var int
   */
  protected $starttime;

  /**
   * Whether to maintain a history of migration processes in migrate_log
   *
   * @var boolean
   */
  protected $logHistory = TRUE;

  /**
   * Primary key of the current history record (inserted at the beginning of
   * a process, to be updated at the end)
   *
   * @var int
   */
  protected $logID;

  /**
   * Number of "items" processed in the current migration process (whatever that
   * means for the type of process)
   *
   * @var int
   */
  protected $total_processed = 0;

  /**
   * List of other Migration classes which should be imported before this one.
   * E.g., a comment migration class would typically have node and user migrations
   * as dependencies.
   *
   * @var array
   */
  protected $dependencies = array(), $softDependencies = array();
  public function getHardDependencies() {
    return $this->dependencies;
  }
  public function getSoftDependencies() {
    return $this->softDependencies;
  }
  public function getDependencies() {
    return array_merge($this->dependencies, $this->softDependencies);
  }

  /**
   * Name of a function for displaying feedback. It must take the message to display
   * as its first argument, and a (string) message type as its second argument
   * (see drush_log()).
   * @var string
   */
  protected $outputFunction;

  /**
   * The fraction of the memory limit at which an operation will be interrupted.
   * Can be overridden by a Migration subclass if one would like to push the
   * envelope. Defaults to 85%.
   *
   * @var float
   */
  protected $memoryThreshold = 0.85;

  /**
   * The PHP memory_limit expressed in bytes.
   *
   * @var int
   */
  protected $memoryLimit;

  /**
   * The fraction of the time limit at which an operation will be interrupted.
   * Can be overridden by a Migration subclass if one would like to push the
   * envelope. Defaults to 90%.
   *
   * @var float
   */
  protected $timeThreshold = 0.90;

  /**
   * The PHP max_execution_time.
   *
   * @var int
   */
  protected $timeLimit;

  /**
   * MigrateTeamMember objects representing people involved with this
   * migration.
   *
   * @var array
   */
  protected $team = array();
  public function getTeam() {
    return $this->team;
  }

  /**
   * If provided, an URL for an issue tracking system containing :id where
   * the issue number will go (e.g., 'http://example.com/project/ticket/:id').
   *
   * @var string
   */
  protected $issuePattern;
  public function getIssuePattern() {
    return $this->issuePattern;
  }

  /**
   * If we set an error handler (during import), remember the previous one so
   * it can be restored.
   *
   * @var callback
   */
  protected $previousErrorHandler = NULL;

  /**
   * Disabling a migration prevents it from running with --all, or individually
   * without --force
   *
   * @var boolean
   */
  protected $enabled = TRUE;
  public function getEnabled() {
    return $this->enabled;
  }

  /**
   * Codes representing the result of a rollback or import process.
   */
  const RESULT_COMPLETED = 1;   // All records have been processed
  const RESULT_INCOMPLETE = 2;  // The process has interrupted itself (e.g., the
                                // memory limit is approaching)
  const RESULT_STOPPED = 3;     // The process was stopped externally (e.g., via
                                // drush migrate-stop)
  const RESULT_FAILED = 4;      // The process had a fatal error
  const RESULT_SKIPPED = 5;     // Dependencies are unfulfilled - skip the process
  const RESULT_DISABLED = 6;    // This migration is disabled, skipping

  /**
   * Codes representing the current status of a migration, and stored in the
   * migrate_status table.
   */
  const STATUS_IDLE = 0;
  const STATUS_IMPORTING = 1;
  const STATUS_ROLLING_BACK = 2;
  const STATUS_STOPPING = 3;

  /**
   * Message types to be passed to saveMessage() and saved in message tables.
   * MESSAGE_INFORMATIONAL represents a condition that did not prevent the operation
   * from succeeding - all others represent different severities of conditions
   * resulting in a source record not being imported.
   */
  const MESSAGE_ERROR = 1;
  const MESSAGE_WARNING = 2;
  const MESSAGE_NOTICE = 3;
  const MESSAGE_INFORMATIONAL = 4;

  /**
   * Get human readable name for a message constant.
   *
   * @return string
   *  Name.
   */
  public function getMessageLevelName($constant) {
    $map = array(
      MigrationBase::MESSAGE_ERROR => t('Error'),
      MigrationBase::MESSAGE_WARNING => t('Warning'),
      MigrationBase::MESSAGE_NOTICE => t('Notice'),
      MigrationBase::MESSAGE_INFORMATIONAL => t('Informational'),
    );
    return $map[$constant];
  }

  /**
   * General initialization of a MigrationBase object.
   */
  public function __construct() {
    $this->machineName = $this->generateMachineName();

    // Record the memory limit in bytes
    $limit = trim(ini_get('memory_limit'));
    $last = strtolower($limit[strlen($limit)-1]);
    switch ($last) {
      case 'g':
        $limit *= 1024;
      case 'm':
        $limit *= 1024;
      case 'k':
        $limit *= 1024;
        break;
      default:
        throw new Exception(t('Invalid PHP memory_limit !limit',
          array('!limit' => $limit)));
    }
    $this->memoryLimit = $limit;

    // Record the time limit
    $this->timeLimit = ini_get('max_execution_time');

    // Default the outputFunction based on context
    if (function_exists('drush_log')) {
      $this->outputFunction = 'drush_log';
    }
    else {
      $this->outputFunction = 'drupal_set_message';
    }

    // Make sure we clear our semaphores in case of abrupt exit
    register_shutdown_function(array($this, 'endProcess'));
  }

  /**
   * Register a new migration process in the migrate_status table. This will
   * generally be used in two contexts - by the class detection code for
   * static (one instance per class) migrations, and by the module implementing
   * dynamic (parameterized class) migrations.
   *
   * @param string $class_name
   * @param string $machine_name
   * @param array $arguments
   */
  static public function registerMigration($class_name, $machine_name = NULL, array $arguments = array()) {
    if (!$machine_name) {
      $machine_name = self::machineFromClass($class_name);
    }

    // See if this migration is already registered
    $migration_row = db_select('migrate_status', 'ms')
                     ->fields('ms', array('class_name', 'arguments'))
                     ->condition('machine_name', $machine_name)
                     ->execute()
                     ->fetchObject();
    if (!$migration_row) {
      db_insert('migrate_status')
        ->fields(array(
          'machine_name' => $machine_name,
          'class_name' => $class_name,
          'arguments' => serialize($arguments),
        ))
        ->execute();
    }
    else {
      // TODO: What, if anything, should we do if the pre-existing class_name or
      // arguments don't match?
    }
  }

  /**
   * Deregister a migration - remove all traces of it from the database (without
   * touching any content which was created by this migration).
   *
   * @param string $machine_name
   */
  static public function deregisterMigration($machine_name) {
    $rows_deleted = db_delete('migrate_status')
                    ->condition('machine_name', $machine_name)
                    ->execute();
  }

  /**
   * By default, the migration machine name is the class name (with the
   * Migration suffix, if present, stripped).
   */
  protected function generateMachineName() {
    $class_name = get_class($this);
    return self::machineFromClass($class_name);
  }

  protected static function machineFromClass($class_name) {
    if (preg_match('/Migration$/', $class_name)) {
      $machine_name = substr($class_name, 0, strlen($class_name) - strlen('Migration'));
    }
    else {
      $machine_name = $class_name;
    }
    return $machine_name;
  }

  /**
   * Return the single instance of the given migration.
   *
   * @param string $machine_name
   */
  static public function getInstance($machine_name, $class_name = NULL, array $arguments = array()) {
    // Otherwise might miss cache hit on case difference
    $machine_name = strtolower($machine_name);
    if (!isset(self::$migrations[$machine_name])) {
      // Skip the query if our caller already made it
      if (!$class_name) {
        // See if we know about this migration
        $row = db_select('migrate_status', 'ms')
                 ->fields('ms', array('class_name', 'arguments'))
                 ->condition('machine_name', $machine_name)
                 ->execute()
                 ->fetchObject();
        if ($row) {
          $class_name = $row->class_name;
          $arguments = unserialize($row->arguments);
        }
        else {
          // Can't find a migration with this name
          self::$migrations[$machine_name] = NULL;
        }
      }
      self::$migrations[$machine_name] = new $class_name($arguments);
    }
    return self::$migrations[$machine_name];
  }

  /**
   * Identifies whether this migration is "dynamic" (that is, allows multiple
   * instances distinguished by differing parameters). A dynamic class should
   * override this with a return value of TRUE.
   */
  static public function isDynamic() {
    return FALSE;
  }

  /**
   * Default to printing messages, but derived classes are expected to save
   * messages indexed by current source ID.
   *
   * @param string $message
   *  The message to record.
   * @param int $level
   *  Optional message severity (defaults to MESSAGE_ERROR).
   */
  public function saveMessage($message, $level = MigrationBase::MESSAGE_ERROR) {
    $this->showMessage($message, $level);
  }

  /**
   * Output the given message appropriately (drush_print/drupal_set_message/etc.)
   *
   * @param string $message
   *  The message to output.
   * @param int $level
   *  Optional message severity (defaults to MESSAGE_ERROR).
   */
  public function showMessage($message, $level = MigrationBase::MESSAGE_ERROR) {
    call_user_func($this->outputFunction, $message, $level);
  }

  /**
   * Custom PHP error handler.
   * TODO: Redundant with hook_watchdog?
   *
   * @param $error_level
   *   The level of the error raised.
   * @param $message
   *   The error message.
   * @param $filename
   *   The filename that the error was raised in.
   * @param $line
   *   The line number the error was raised at.
   * @param $context
   *   An array that points to the active symbol table at the point the error occurred.
   */
  public function errorHandler($error_level, $message, $filename, $line, $context) {
    if ($error_level & error_reporting()) {
      $message .= "\n" . t('File !file, line !line',
        array('!line' => $line, '!file' => $filename));
      // Record notices and continue
      if ($error_level == E_NOTICE || $error_level == E_USER_NOTICE) {
        $this->saveMessage($message . "(file: $filename, line $line)", MigrationBase::MESSAGE_INFORMATIONAL);
      }
      // Simply ignore strict and deprecated errors
      // Note DEPRECATED constants introduced in PHP 5.3
      elseif (!($error_level == E_STRICT || $error_level == 8192 ||
                $error_level == 16384)) {
        throw new MigrateException($message, MigrationBase::MESSAGE_ERROR);
      }
    }
  }

  /**
   * Database logging callback - called when there's a database error. We
   * log non-critical stuff, and throw an exception otherwise
   * TODO: Eliminate in favor of hook_watchdog()?
   *
   * @param string $type
   *  Ignored
   * @param string $message
   *  Message to display or throw, potentially with t() placeholders
   * @param array $variables
   *  Variables to substitute into $message
   * @param unknown_type $severity
   *  Watchdog severity level
   * @param $link
   *  ???
   */
  public function loggingCallback($type, $message, $variables = array(),
          $severity = WATCHDOG_NOTICE, $link = NULL) {
    if ($severity == WATCHDOG_NOTICE || $severity == WATCHDOG_INFO ||
        $severity == WATCHDOG_DEBUG) {
      $this->saveMessage(t($message, $variables), MigrationBase::MESSAGE_INFORMATIONAL);
    }
    else {
      throw new MigrateException(t($message, $variables), MigrationBase::MESSAGE_ERROR);
    }
  }

  /**
   * Check the current status of a migration.
   * @return int
   *  One of the MigrationBase::STATUS_* constants
   */
  public function getStatus() {
    $status = db_select('migrate_status', 'ms')
              ->fields('ms', array('status'))
              ->condition('machine_name', $this->machineName)
              ->execute()
              ->fetchField();
    if (!isset($status)) {
      $status = MigrationBase::STATUS_IDLE;
    }
    return $status;
  }

  /**
   * Retrieve the last time an import operation completed successfully.
   * @return string
   *  Date/time string, formatted... How? Default DB server format?
   */
  public function getLastImported() {
    $last_imported = db_select('migrate_log', 'ml')
              ->fields('ml', array('endtime'))
              ->condition('machine_name', $this->machineName)
              ->isNotNull('endtime')
              ->orderBy('endtime', 'DESC')
              ->execute()
              ->fetchField();
    if ($last_imported) {
      $last_imported = date('Y-m-d H:i:s', $last_imported/1000);
    }
    else {
      $last_imported = '';
    }
    return $last_imported;
  }

  /**
   * Fetch the current highwater mark for updated content.
   *
   * @return string
   *  The highwater mark.
   */
  public function getHighwater() {
    $highwater = db_select('migrate_status', 'ms')
              ->fields('ms', array('highwater'))
              ->condition('machine_name', $this->machineName)
              ->execute()
              ->fetchField();
    return $highwater;
  }

  /**
   * Save the highwater mark for this migration (but not when using an idlist).
   *
   * @param mixed $highwater
   *  Highwater mark to save
   * @param boolean $force
   *  If TRUE, save even if it's lower than the previous value.
   */
  protected function saveHighwater($highwater, $force = FALSE) {
    if (!isset($this->options['idlist'])) {
      $query = db_update('migrate_status')
               ->fields(array('highwater' => $highwater))
               ->condition('machine_name', $this->machineName);
      if (!$force) {
        $query->condition('highwater', $highwater, '<');
      }
      $query->execute();
    }
  }

  /**
   * Retrieve the last throughput for current Migration (items / minute).
   * @return integer
   */
  public function getLastThroughput() {
    $last_throughput = 0;
    $row = db_select('migrate_log', 'ml')
              ->fields('ml', array('starttime', 'endtime', 'numprocessed'))
              ->condition('machine_name', $this->machineName)
              ->condition('process_type', 1)
              ->isNotNull('endtime')
              ->orderBy('starttime', 'DESC')
              ->execute()
              ->fetchObject();
    if ($row) {
      $elapsed = ($row->endtime - $row->starttime)/1000;
      if ($elapsed > 0) {
        $last_throughput = round(($row->numprocessed / $elapsed) * 60);
      }
    }
    return $last_throughput;
  }

  /**
   * Reports whether this migration process is complete. For a Migration, for
   * example, this would be whether all available source rows have been processed.
   * Other MigrationBase classes will need to return TRUE/FALSE appropriately.
   */
  abstract public function isComplete();

  /**
   * Reports whether all (hard) dependencies have completed migration
   * TODO: Support rollback (reverse dependencies)
   */
  protected function dependenciesComplete() {
    foreach ($this->dependencies as $dependency) {
      $migration = MigrationBase::getInstance($dependency);
      if (!$migration->isComplete()) {
        return FALSE;
      }
    }
    return TRUE;
  }

  /**
   * Begin a process, ensuring only one process can be active
   * at once on a given migration.
   *
   * @param int $newStatus
   *  MigrationBase::STATUS_IMPORTING or MigrationBase::STATUS_ROLLING_BACK
   */
  protected function beginProcess($newStatus) {
    // So hook_watchdog() knows what migration (if any) is running
    self::$currentMigration = $this;

    // Try to make the semaphore handling atomic (depends on DB support)
    $transaction = db_transaction();

    $this->starttime = microtime(TRUE);

    // Check to make sure there's no process already running for this migration
    $status = $this->getStatus();
    if ($status != MigrationBase::STATUS_IDLE) {
      throw new MigrateException(t('There is already an active process on !machine_name',
        array('!machine_name' => $this->machineName)));
    }

    $this->processing = TRUE;
    $this->status = $newStatus;
    db_merge('migrate_status')
      ->key(array('machine_name' => $this->machineName))
      ->fields(array('class_name' => get_class($this), 'status' => $newStatus))
      ->execute();

    // Set an error handler for imports
    if ($newStatus == MigrationBase::STATUS_IMPORTING) {
      $this->previousErrorHandler = set_error_handler(array($this, 'errorHandler'));
    }

    // Save the initial history record
    if ($this->logHistory) {
      $this->logID = db_insert('migrate_log')
                     ->fields(array(
                       'machine_name' => $this->machineName,
                       'process_type' => $newStatus,
                       'starttime' => microtime(TRUE) * 1000,
                       'initialHighwater' => $this->getHighwater(),
                       ))
                     ->execute();
    }

    // And capture anything the DB tries to log to the watchdog
    // TODO: Broken by http://drupal.org/node/711108 - what to do?
    //Database::setLoggingCallback(array($this, 'loggingCallback'), WATCHDOG_NOTICE, WATCHDOG_ERROR);
  }

  /**
   * End a rollback or import process, releasing the semaphore. Note that it must
   * be public to be callable as the shutdown function.
   */
  public function endProcess() {
    if ($this->previousErrorHandler) {
      set_error_handler($this->previousErrorHandler);
      $this->previousErrorHandler = NULL;
    }
    if ($this->processing) {
      $this->status = MigrationBase::STATUS_IDLE;
      $fields = array('class_name' => get_class($this), 'status' => MigrationBase::STATUS_IDLE);
      db_merge('migrate_status')
        ->key(array('machine_name' => $this->machineName))
        ->fields($fields)
        ->execute();

      // Complete the log record
      if ($this->logHistory) {
        db_merge('migrate_log')
          ->key(array('mlid' => $this->logID))
          ->fields(array(
            'endtime' => microtime(TRUE) * 1000,
            'finalhighwater' => $this->getHighwater(),
            'numprocessed' => $this->total_processed,
          ))
          ->execute();
      }

      $this->processing = FALSE;
    }
    self::$currentMigration = NULL;
  }

  /**
   * Signal that any current import or rollback process should end itself at
   * the earliest opportunity
   */
  public function stopProcess() {
    // Do not change the status of an idle migration
    db_update('migrate_status')
      ->fields(array('status' => MigrationBase::STATUS_STOPPING))
      ->condition('machine_name', $this->machineName)
      ->condition('status', MigrationBase::STATUS_IDLE, '<>')
      ->execute();
  }

  /**
   * Reset the status of the migration to IDLE (to be used when the status
   * gets stuck, e.g. if a process core-dumped)
   */
  public function resetStatus() {
    // Do not change the status of an already-idle migration
    db_update('migrate_status')
      ->fields(array('status' => MigrationBase::STATUS_IDLE))
      ->condition('machine_name', $this->machineName)
      ->condition('status', MigrationBase::STATUS_IDLE, '<>')
      ->execute();
  }

  /**
   * Perform an operation during the rollback phase.
   *
   * @param array $options
   *  List of options provided (usually from a drush command). Specific to
   *  the derived class.
   */
  public function processRollback(array $options = array()) {
    if ($this->enabled) {
      $return = MigrationBase::RESULT_COMPLETED;
      if (method_exists($this, 'rollback')) {
        $this->options = $options;
        // TODO: Validate dependencies (migrations depending on us have no imported rows)
    /*    if (!isset($options['force'])) {
          if (!$this->dependenciesComplete()) {
            return Migration::RESULT_SKIPPED;
          }
        }*/
        $this->beginProcess(MigrationBase::STATUS_ROLLING_BACK);
        try {
          $return = $this->rollback();
        }
        catch (Exception $exception) {
          // If something bad happened, make sure we clear the semaphore
          $this->endProcess();
          throw $exception;
        }
        $this->endProcess();
      }
    }
    else {
      $return = MigrationBase::RESULT_DISABLED;
    }
    return $return;
  }

  /**
   * Perform an operation during the import phase
   *
   * @param array $options
   *  List of options provided (usually from a drush command). Specific to
   *  the derived class.
   */
  public function processImport(array $options = array()) {
    if ($this->enabled) {
      $return = MigrationBase::RESULT_COMPLETED;
      if (method_exists($this, 'import')) {
        $this->options = $options;
        if (!isset($options['force'])) {
          if (!$this->dependenciesComplete()) {
            return MigrationBase::RESULT_SKIPPED;
          }
        }
        $this->beginProcess(MigrationBase::STATUS_IMPORTING);
        try {
          $return = $this->import();
        }
        catch (Exception $exception) {
          // If something bad happened, make sure we clear the semaphore
          $this->endProcess();
          throw $exception;
        }

        if ($return == MigrationBase::RESULT_COMPLETED && isset($this->total_successes)) {
          $overallThroughput = round(60*$this->total_successes / (microtime(TRUE) - $this->starttime));
        }
        else {
          $overallThroughput = 0;
        }
        $this->endProcess($overallThroughput);
      }
    }
    else {
      $return = MigrationBase::RESULT_DISABLED;
    }
    return $return;
  }

  /**
   * A derived migration class does the actual rollback or import work in these
   * methods - we cannot declare them abstract because some classes may define
   * only one.
   *
   * abstract protected function rollback();
   * abstract protected function import();
   */

  /**
   * Test whether we've exceeded the desired memory threshold. If so, output a message.
   *
   * @return boolean
   *  TRUE if the threshold is exceeded, FALSE if not.
   */
  protected function memoryExceeded() {
    $usage = memory_get_usage();
    $pct_memory = $usage/$this->memoryLimit;
    if ($pct_memory > $this->memoryThreshold) {
      $this->showMessage(
        t('Memory usage is !usage (!pct% of limit !limit), resetting statics',
          array('!pct' => round($pct_memory*100),
                '!usage' => format_size($usage),
                '!limit' => format_size($this->memoryLimit))),
        'warning');
      // First, try resetting Drupal's static storage - this frequently releases
      // plenty of memory to continue
      drupal_static_reset();
      $usage = memory_get_usage();
      $pct_memory = $usage/$this->memoryLimit;
      // Use a lower threshold - we don't want to be in a situation where we keep
      // coming back here and trimming a tiny amount
      if ($pct_memory > (.90 * $this->memoryThreshold)) {
        $this->showMessage(
          t('Memory usage is now !usage (!pct% of limit !limit), not enough reclaimed, starting new batch',
            array('!pct' => round($pct_memory*100),
                  '!usage' => format_size($usage),
                  '!limit' => format_size($this->memoryLimit))),
          'warning');
        return TRUE;
      }
      else {
        $this->showMessage(
          t('Memory usage is now !usage (!pct% of limit !limit), reclaimed enough, continuing',
            array('!pct' => round($pct_memory*100),
                  '!usage' => format_size($usage),
                  '!limit' => format_size($this->memoryLimit))),
          'warning');
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  /**
   * Test whether we've exceeded the desired time threshold. If so, output a message.
   *
   * @return boolean
   *  TRUE if the threshold is exceeded, FALSE if not.
   */
  protected function timeExceeded() {
    if ($this->timeLimit == 0) {
      return FALSE;
    }
    $time_elapsed = time() - REQUEST_TIME;
    $pct_time = $time_elapsed / $this->timeLimit;
    if ($pct_time > $this->timeThreshold) {
      $this->showMessage(
        t('Time limit approaching, starting new batch',
          array('!pct' => round($pct_time*100),
                '!usage' => format_size($time_elapsed),
                '!limit' => format_size($this->timeLimit))),
        'warning');
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Convert an incoming string (which may be a UNIX timestamp, or an arbitrarily-formatted
   * date/time string) to a UNIX timestamp.
   *
   * @param string $value
   */
  static public function timestamp($value) {
    // Default empty values to now
    if (empty($value)) {
      return time();
    }

    // Does it look like it's already a timestamp? Just return it
    if (is_numeric($value)) {
      return $value;
    }

    $time = strtotime($value);
    if ($time == FALSE) {
      // Handles form YYYY-MM-DD HH:MM:SS.garbage
      if (drupal_strlen($value) > 19) {
        $time = strtotime(drupal_substr($value, 0, 19));
      }
    }
    return $time;
  }
}