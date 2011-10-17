<?php
/**
 * @file
 * Background Batch module integration.
 */

/**
 * Implements hook_deepzoom_processor_info() on behalf of
 * background_batch.module.
 */
function background_batch_deepzoom_processor_info() {
  if (function_exists('background_batch_process_batch')) {
    return array(
      'background_batch' => array(
        'process callback' => 'deepzoom_generate_deepzoom_background_batch',
      ),
    );
  }
}

/**
 * Deep Zoom processor - Background Batch.
 */
function deepzoom_generate_deepzoom_background_batch($images) {
  $return = array();

  $batch = array(
    'title' => t('Generating Deep Zoom files'),
    'operations' => array(),
  );
  foreach ($images as $md5 => $uri) {
    $return[$uri] = TRUE;
    if (!file_exists("public://deepzoom/{$md5}.dzi")) {
      $batch['operations'][] = array('deepzoom_generate_deepzoom_batch_process', array($uri, $md5));
      $return[$uri] = FALSE;
    }
  }

  if (count($batch['operations']) > 0 && user_access('generate deepzoom files'))  {
    batch_set($batch);
    background_batch_process_batch();
  }

  return $return;
}
