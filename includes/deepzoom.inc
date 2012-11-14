<?php
/**
 * @file
 * DeepZoom module integration.
 */

/**
 * Implements hook_deepzoom_engine_info() on behalf of deepzoom.module.
 */
function deepzoom_deepzoom_engine_info() {
  $items = array();
  foreach (array_keys(libraries_get_libraries()) as $library) {
    if (file_exists($file = drupal_get_path('module', 'deepzoom') . "/engines/{$library}.inc")) {
      require_once $file;
      if (function_exists($function = "deepzoom_engine_{$library}_info")) {
        $function($items);
      }
    }
  }
  return $items;
}

/**
 * Implements hook_deepzoom_processor_info() on behalf of deepzoom.module.
 */
function deepzoom_deepzoom_processor_info() {
  return array(
    //'memory' => array(
    //  'process callback' => 'deepzoom_generate_deepzoom_memory',
    //),
    'batch' => array(
      'process callback' => 'deepzoom_generate_deepzoom_batch',
    ),
  );
}
