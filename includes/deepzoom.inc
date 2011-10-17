<?php
/**
 * @file
 * DeepZoom module integration.
 */

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
