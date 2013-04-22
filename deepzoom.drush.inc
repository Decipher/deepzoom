<?php
/**
 * @file
 * Drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function deepzoom_drush_command() {
  $items = array();

  $items['deepzoom-library'] = array(
    'callback' => 'drush_deepzoom_library',
    'description' => dt('Download the desired Deepzoom library.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'library' => dt('Optional. The library to be downloaded (openseadragon, seadragon). If omitted Drush will use the OpenSeadragon library.'),
      'path' => dt('Optional. A path where to install the Deepzoom library. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('dzlib'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function deepzoom_drush_help($section) {
  switch ($section) {
    case 'drush:deepzoom-library':
      return dt('Download and install either the OpenSeadragon or Seadragon AJAX library, default location is sites/all/libraries.');
  }
}

/**
 * Drush command callback for Deepzoom library downloader.
 *
 * @param $library
 *   The Deepzoom library to be downloaded. Defaults to 'openseadragon'.
 * @param $path
 *   The path to download the library to. Defaults to 'sites/all/libraries'.
 */
function drush_deepzoom_library($library = 'openseadragon', $path = 'sites/all/libraries') {
  switch ($library) {
    case 'openseadragon':
      $file = 'https://github.com/openseadragon/site-build/raw/master/built-openseadragon/openseadragon.zip';
      $dirname = $library;
      break;

    case 'seadragon':
      $file = 'https://github.com/aseemk/seadragon-ajax/archive/v0.8.9.zip';
      $dirname = 'seadragon-ajax-0.8.9';
      break;

    default:
      drush_log(dt('The library @library is unknown.', array('@library' => $library)), 'error');
      return;
  }


  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the library file.
  if ($filepath = drush_download_file($file)) {
    $filename = basename($filepath);

    // Remove any existing library directory.
    if (is_dir($dirname) || is_dir($library)) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir($library, TRUE);
      drush_log(dt('An existing library was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the library file.
    drush_tarball_extract($filename);

    // Change the directory name to "colorbox" if needed.
    if ($dirname != $library) {
      drush_move_dir($dirname, $library, TRUE);
    }
  }

  if (is_dir($library)) {
    drush_log(dt('Deepzoom library has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Deepzoom library to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
