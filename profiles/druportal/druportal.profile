<?php

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles, e.g., 'language' => 'fr'.
 */
function druportal_profile_details() {
  return array(
    'name' => 'Druportal (Customized for SkyPortal to Drupal migrations)',
    'description' => 'Select this profile to import your SkyPortal data and setup functionality similar to SkyPortal',
  );
}

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * The following required core modules are always enabled:
 * 'block', 'filter', 'node', 'system', 'user'.
 *
 * @return
 *  An array of modules to be enabled.
 */
function druportal_profile_modules() {
  return array(
    // Enable optional core modules.
    'dblog', 'help', 'taxonomy', 'search',
    
    // Druportal Included Modules
    'admin_menu', 'adminrole', 'content', 'views',
  );
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function druportal_profile_task_list() {
  return array(
    'druportal-import' => st('Import Data'),
  );
}

/**
 * Perform final installation tasks for this installation profile.
 */
function druportal_profile_tasks(&$task, $url) {
  
  // $task is set to 'profile' the first time this function is called.
  if ($task == 'profile') {
    
    // Set up all the things a default installation profile has.
    require_once 'profiles/default/default.profile';
    default_profile_tasks($task, $url);

    // Add SkyPortal equivalent roles.
    //db_query("INSERT INTO {role} (name) VALUES ('%s')", 'site administrator');

    // Set $task to next task so the installer UI will be correct.
    $task = 'druportal-import';
    drupal_set_title(st('Import Data'));
    
    // Ask what info they want to import
    return drupal_get_form('druportal_import_select', $url);
  }

  if ($task == 'druportal-import') {
    
    // Get form data that was submitted from 'profile'
    // This is what features should we import data for
    
    // Kick off batch api to do the importing
    

    // Set $task to next task so the installer UI will be correct.
    $task = 'druportal-import-complete';
    drupal_set_title(st('Import Complete'));
    $output = '<p>Your data has been imported.</p>';
    // Build a 'Continue' link that goes to the next task.
    $output .= '<p>'. l(st('Continue'), $url) .'</p>';
    return $output;
  }

  if ($task == 'druportal-import-complete') {
    // Change to our custom theme.
    /*
    $themes = system_theme_data();
    $theme = 'druportal_frostysky';
    if (isset($themes[$theme])) {
      system_initialize_theme_blocks($theme);
      db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND
        name = '%s'", $theme);
      variable_set('theme_default', $theme);
      menu_rebuild();
      drupal_rebuild_theme_registry();
    }
    */

    // Return control to the installer.
    $task = 'profile-finished';
  }
}

/**
 * Define form to ask user what to import.
 *
 * @param $form_state
 *   Keyed array containing the state of the form.
 * @param $url
 *   URL of current installer page, provided by installer.
 */
function druportal_import_select($form_state, $url) {
  $form['#action'] = $url;
  $form['#redirect'] = FALSE;
  
  $form['druportal_import_features'] = array(
    '#type' => 'fieldset',
    '#title' => 'Features to Import',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form['druportal_import_features']['config'] = array(
    '#type' => 'checkbox',
    '#title' => 'Config',
    '#default_value' => 1,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['groups'] = array(
    '#type' => 'checkbox',
    '#title' => 'Groups',
    '#default_value' => 1,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['members'] = array(
    '#type' => 'checkbox',
    '#title' => 'Members',
    '#default_value' => 1,
    '#disabled' => TRUE,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Save and Continue'),
  );
  return $form;
}

/**
 * Handle form submission for university_department_info form.
 */
function druportal_import_select_submit($form, &$form_state) {
  // Look for CSV files in sites/default/files
}