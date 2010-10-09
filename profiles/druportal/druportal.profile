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

    // Enable Modules Necessary for SkyPortal core functionality
    'profile', 
    
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
    
    // Make admin role have permissions for module that may have been enabled
    // after adminrole
    require_once 'profiles/druportal/modules/adminrole/adminrole.module';
    adminrole_update_permissions();

    // Create the profile fields for members
    $sql = <<<EOL
INSERT INTO `profile_fields` (`fid`, `title`, `name`, `explanation`, `category`, `page`, `type`, `weight`, `required`, `register`, `visibility`, `autocomplete`, `options`) VALUES
(null, 'Firstname', 'profile_basics_firstname', '', 'Basics', '', 'textfield', -9, 0, 0, 2, 0, ''),
(null, 'Surname', 'profile_basics_surname', '', 'Basics', '', 'textfield', -8, 0, 0, 2, 0, ''),
(null, 'City', 'profile_basics_city', '', 'Basics', '', 'textfield', -7, 0, 0, 2, 0, ''),
(null, 'Homepage', 'profile_links_homepage', '', 'Links', '', 'url', 0, 0, 0, 2, 0, ''),
(null, 'Cool Links', 'profile_links_cool_1', '', 'Links', '', 'url', 0, 0, 0, 2, 0, ''),
(null, 'Other', 'profile_links_cool_2', '', 'Links', '', 'url', 0, 0, 0, 2, 0, ''),
(null, 'Birthdate', 'profile_basics_birthdate', '', 'Basics', '', 'date', -3, 0, 0, 2, 0, ''),
(null, 'State', 'profile_basics_state', '', 'Basics', '', 'textfield', -6, 0, 0, 2, 0, ''),
(null, 'Zip Code', 'profile_basics_zip', '', 'Basics', '', 'textfield', -5, 0, 0, 2, 0, ''),
(null, 'Country', 'profile_basics_country', '', 'Basics', '', 'textfield', -4, 0, 0, 2, 0, ''),
(null, 'Sex', 'profile_basics_sex', '', 'Basics', '', 'selection', -2, 0, 0, 2, 0, 'Male\r\nFemale'),
(null, 'Marital Status', 'profile_basics_marrital_status', '', 'Basics', '', 'textfield', -1, 0, 0, 2, 0, ''),
(null, 'Occupation', 'profile_basics_occupation', '', 'Basics', '', 'textfield', 0, 0, 0, 2, 0, ''),
(null, 'Gold', 'profile_basics_gold', '', 'Basics', '', 'textfield', 1, 0, 0, 4, 0, ''),
(null, 'Rep Points', 'profile_basics_rep', '', 'Basics', '', 'textfield', 2, 0, 0, 4, 0, ''),
(null, 'Title', 'profile_basics_title', '', 'Basics', '', 'textfield', -10, 0, 0, 4, 0, ''),
(null, 'MSN', 'profile_contact_msn', '', 'Contact Info', '', 'textfield', 0, 0, 0, 2, 0, ''),
(null, 'ICQ', 'profile_contact_icq', '', 'Contact Info', '', 'textfield', 0, 0, 0, 2, 0, ''),
(null, 'Yahoo IM', 'profile_contact_yahoo', '', 'Contact Info', '', 'textfield', 0, 0, 0, 2, 0, ''),
(null, 'AIM', 'profile_contact_aim', '', 'Contact Info', '', 'textfield', 0, 0, 0, 2, 0, ''),
(null, 'Favorite Person', 'profile_more_fav_person', '', 'More About Me', '', 'textarea', 0, 0, 0, 2, 0, ''),
(null, 'Favorite Food', 'profile_more_fav_food', '', 'More About Me', '', 'textarea', 0, 0, 0, 2, 0, ''),
(null, 'Hobbies', 'profile_more_hobbies', '', 'More About Me', '', 'textarea', 0, 0, 0, 2, 0, ''),
(null, 'Comments', 'profile_more_comments', '', 'More About Me', '', 'textarea', 0, 0, 0, 2, 0, '');
EOL;
    db_query($sql);

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
  $form['druportal_import_features']['forums'] = array(
    '#type' => 'checkbox',
    '#title' => 'Forums',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['downloads'] = array(
    '#type' => 'checkbox',
    '#title' => 'Downloads',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['pictures'] = array(
    '#type' => 'checkbox',
    '#title' => 'Pictures',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['articles'] = array(
    '#type' => 'checkbox',
    '#title' => 'Articles',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['classifieds'] = array(
    '#type' => 'checkbox',
    '#title' => 'Classifieds',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['links'] = array(
    '#type' => 'checkbox',
    '#title' => 'Links',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['calendar'] = array(
    '#type' => 'checkbox',
    '#title' => 'Calendar',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['blogs'] = array(
    '#type' => 'checkbox',
    '#title' => 'Blogs',
    '#default_value' => 0,
    '#disabled' => TRUE,
  );
  $form['druportal_import_features']['news'] = array(
    '#type' => 'checkbox',
    '#title' => 'News',
    '#default_value' => 0,
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
