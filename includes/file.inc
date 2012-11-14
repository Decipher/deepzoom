<?php
/**
 * @file
 * File module integration.
 */

/**
 * Implememnts hook_deepzoom_field_formatter_info_alter() on behalf of
 * file.module.
 */
function file_deepzoom_field_formatter_info_alter(&$items) {
  $items['deepzoom_file'] = array(
    'label' => t('Deep Zoom'),
    'field types' => array('file'),
  );
}

/**
 * Field formatter view callback for Deep Zoom File formatter.
 */
function deepzoom_file_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $elements = array();

  foreach ($items as $item) {
    $pathinfo = pathinfo($item['uri']);
    if ($pathinfo['extension'] !== 'zip') {
      if (user_access('administer deepzoom') || user_access('generate deepzoom files')) {
        drupal_set_message(t('The Deep Zoom file field formatter only works with .zip files.'), 'error');
      }
      watchdog('deepzoom', 'The Deep Zoom file field formatter only works with .zip files.', array(), WATCHDOG_ERROR);
      continue;
    }

    $md5 = md5_file($item['uri']);

    // Check if Deep Zoom file needs to be processed.
    if (!file_exists("public://deepzoom/{$md5}.dzi")) {
      $path = drupal_realpath($item['uri']);

      $zip = new ZipArchive;
      $res = $zip->open($path);
      if ($res === TRUE) {
        $zip->extractTo('temporary://deepzoom');
        $zip->close();

        $directories = file_scan_directory('temporary://deepzoom', '/\.*?_files/', array('recurse' => FALSE));
        foreach ($directories as $directory) {
          if (is_dir($directory->uri)) {
            $name = substr($directory->name, 0, strpos($directory->name, '_files'));

            if (file_exists("temporary://deepzoom/{$name}.xml")) {
              $files = file_scan_directory($directory->uri, '/\.*/');
              foreach ($files as $file) {
                if (is_file($file->uri)) {
                  $destination = str_replace($directory->uri, "public://deepzoom/{$md5}_files", $file->uri);
                  $pathinfo = pathinfo($destination);
                  file_prepare_directory($pathinfo['dirname'], FILE_CREATE_DIRECTORY);
                  file_unmanaged_move($file->uri, $destination, FILE_EXISTS_REPLACE);
                }
              }

              // Move DZI file into place.
              file_unmanaged_move("temporary://deepzoom/{$name}.xml", "public://deepzoom/{$md5}.dzi", FILE_EXISTS_REPLACE);

              break;
            }
          }
        }

        // Clean up temporary files.
        file_unmanaged_delete_recursive('temporary://deepzoom');
      }
    }

    // Display Deep Zoom wrapper.
    if (file_exists("public://deepzoom/{$md5}.dzi")) {
      $elements[] = array(
        '#theme' => 'deepzoom_wrapper',
        '#md5' => $md5,
      );
    }

    else {
      if (user_access('administer deepzoom') || user_access('generate deepzoom files')) {
        drupal_set_message(t('An error occured processing %file via the Deep Zoom file field formatter.', array(
          '%file' => $item['uri'],
        )), 'error');
      }
      watchdog('deepzoom', 'An error occured processing %file via the Deep Zoom file field formatter.', array('%file' => $item['uri']), WATCHDOG_ERROR);
    }
  }

  return $elements;
}
