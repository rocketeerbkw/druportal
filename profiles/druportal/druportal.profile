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
    // Enable core modules
    'dblog', 'help', 'taxonomy', 'search',

    // Druportal Included Modules
    'install_profile_api', 'admin_menu', 'adminrole', 'content', 'views',
    'vertical_tabs', 'features', 'token',

    // Enable Modules Necessary for SkyPortal core functionality
    'profile', 'scheduler', 'privatemsg', 'druportal_announcements',

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

  // Enable Install Profile API
  install_include(druportal_profile_modules());

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
    druportal_profile_add_fields();

    // Set $task to next task so the installer UI will be correct.
    //$task = 'druportal-import';
    //drupal_set_title(st('Import Data'));

    //// Ask what info they want to import
    //return drupal_get_form('druportal_import_select', $url);
    $task = 'profile-finished';
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

function druportal_profile_add_fields() {
  $fields = array(
    array(
      'title' => 'Firstname',
      'name' => 'profile_basics_firstname',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -9,
      'visibility' => 2,
    ),
    array(
      'title' => 'Surname',
      'name' => 'profile_basics_surname',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -8,
      'visibility' => 2,
    ),
    array(
      'title' => 'City',
      'name' => 'profile_basics_city',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -7,
      'visibility' => 2,
    ),
    array(
      'title' => 'Homepage',
      'name' => 'profile_links_homepage',
      'category' => 'Links',
      'page' => '',
      'type' => 'url',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Cool Links',
      'name' => 'profile_links_cool_1',
      'category' => 'Links',
      'page' => '',
      'type' => 'url',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Other',
      'name' => 'profile_links_cool_2',
      'category' => 'Links',
      'page' => '',
      'type' => 'url',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Birthdate',
      'name' => 'profile_basics_birthdate',
      'category' => 'Basics',
      'page' => '',
      'type' => 'date',
      'weight' => -3,
      'visibility' => 2,
    ),
    array(
      'title' => 'State',
      'name' => 'profile_basics_state',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -6,
      'visibility' => 2,
    ),
    array(
      'title' => 'Zip Code',
      'name' => 'profile_basics_zip',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -5,
      'visibility' => 2,
    ),
    array(
      'title' => 'Country',
      'name' => 'profile_basics_country',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -4,
      'visibility' => 2,
    ),
    array(
      'title' => 'Sex',
      'name' => 'profile_basics_sex',
      'category' => 'Basics',
      'page' => '',
      'type' => 'selection',
      'weight' => -2,
      'visibility' => 2,
      'options' => array('Male', 'Female'),
    ),
    array(
      'title' => 'Marital Status',
      'name' => 'profile_basics_marrital_status',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -1,
      'visibility' => 2,
    ),
    array(
      'title' => 'Occupation',
      'name' => 'profile_basics_occupation',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Gold',
      'name' => 'profile_basics_gold',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => 1,
      'visibility' => 4,
    ),
    array(
      'title' => 'Rep Points',
      'name' => 'profile_basics_rep',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => 2,
      'visibility' => 4,
    ),
    array(
      'title' => 'Title',
      'name' => 'profile_basics_title',
      'category' => 'Basics',
      'page' => '',
      'type' => 'textfield',
      'weight' => -10,
      'visibility' => 4,
    ),
    array(
      'title' => 'MSN',
      'name' => 'profile_contact_msn',
      'category' => 'Contact Info',
      'page' => '',
      'type' => 'textfield',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'ICQ',
      'name' => 'profile_contact_icq',
      'category' => 'Contact Info',
      'page' => '',
      'type' => 'textfield',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Yahoo IM',
      'name' => 'profile_contact_yahoo',
      'category' => 'Contact Info',
      'page' => '',
      'type' => 'textfield',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'AIM',
      'name' => 'profile_contact_aim',
      'category' => 'Contact Info',
      'page' => '',
      'type' => 'textfield',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Favorite Person',
      'name' => 'profile_more_fav_person',
      'category' => 'More About Me',
      'page' => '',
      'type' => 'textarea',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Favorite Food',
      'name' => 'profile_more_fav_food',
      'category' => 'More About Me',
      'page' => '',
      'type' => 'textarea',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Hobbies',
      'name' => 'profile_more_hobbies',
      'category' => 'More About Me',
      'page' => '',
      'type' => 'textarea',
      'weight' => 0,
      'visibility' => 2,
    ),
    array(
      'title' => 'Comments',
      'name' => 'profile_more_comments',
      'category' => 'More About Me',
      'page' => '',
      'type' => 'textarea',
      'weight' => 0,
      'visibility' => 2,
    ),
  );

  foreach ($fields as $field) {
    install_profile_field_add($field);
  }
}
