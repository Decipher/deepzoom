<?php
/**
 * @file
 * System module integration.
 */

/**
 * Deep Zoom processor - Memory.
 *
 * @TODO - Add this in future release.
 */
function deepzoom_generate_deepzoom_memory($images) {
  return FALSE;
}

/**
 * Deep Zoom processor - Batch API.
 */
function deepzoom_generate_deepzoom_batch($images) {
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
    batch_process();
  }

  return $return;
}

/**
 * Deep Zoom processor - Batch API process callback.
 */
function deepzoom_generate_deepzoom_batch_process($uri, $md5, &$context) {
 if (empty($context['sandbox'])) {
    $context['sandbox']['image'] = deepzoom_generate_image_info($uri, $md5);
    $context['sandbox']['config'] = deepzoom_config();
    $context['sandbox']['level'] = 0;
    $context['sandbox']['column'] = 0;
    $context['sandbox']['row'] = 0;
    $context['sandbox']['level_progress'] = 0;
    $context['sandbox']['total_progress'] = 0;
  }

  $count = 0;
  $max = 10;
  while ($count < $max && $context['sandbox']['total_progress'] < $context['sandbox']['image']['count']) {
    $level_dir = "public://deepzoom/{$context['sandbox']['image']['md5']}_files/{$context['sandbox']['level']}";

    // Setup level directory and temporary image.
    if ($context['sandbox']['level_progress'] == 0) {
      if (file_prepare_directory($level_dir, FILE_CREATE_DIRECTORY)) {
        $image = image_load($uri);
        image_effect_apply($image, array(
          'effect callback' => 'image_resize_effect',
          'data' => array(
            'width' => $context['sandbox']['image']['levels'][$context['sandbox']['level']]['width'],
            'height' => $context['sandbox']['image']['levels'][$context['sandbox']['level']]['height'],
          ),
        ));
        image_save($image, "{$level_dir}/._temp.{$context['sandbox']['image']['extension']}");
      }
    }

    // Tile processing.
    // @TODO - Make a seperate function for this.
    if (!file_exists("{$level_dir}/{$context['sandbox']['column']}_{$context['sandbox']['row']}.{$context['sandbox']['image']['extension']}")) {
      $offset_x = $context['sandbox']['column'] == 0 ? 0 : $context['sandbox']['config']['tile_overlap'];
      $offset_y = $context['sandbox']['row'] == 0 ? 0 : $context['sandbox']['config']['tile_overlap'];
      $x = ($context['sandbox']['column'] * $context['sandbox']['config']['tile_size']) - $offset_x;
      $y = ($context['sandbox']['row'] * $context['sandbox']['config']['tile_size']) - $offset_y;

      $width = $context['sandbox']['config']['tile_size'] + ($context['sandbox']['column'] == 0 ? 1 : 2) * $context['sandbox']['config']['tile_overlap'];
      $height = $context['sandbox']['config']['tile_size'] + ($context['sandbox']['row'] == 0 ? 1 : 2) * $context['sandbox']['config']['tile_overlap'];
      $crop_width = min($width, $context['sandbox']['image']['levels'][$context['sandbox']['level']]['width'] - $x);
      $crop_height = min($height, $context['sandbox']['image']['levels'][$context['sandbox']['level']]['height'] - $y);

      $temp_image = image_load("{$level_dir}/._temp.{$context['sandbox']['image']['extension']}");
      image_effect_apply($temp_image, array(
        'effect callback' => 'image_crop_effect',
        'data' => array(
          'anchor' => "{$x}-{$y}",
          'width' => $crop_width,
          'height' => $crop_height,
        ),
      ));
      image_save($temp_image, "{$level_dir}/{$context['sandbox']['column']}_{$context['sandbox']['row']}.{$context['sandbox']['image']['extension']}");
      unset($temp_image);
    }

    // Increment counters.
    $count++;
    $context['sandbox']['level_progress']++;
    $context['sandbox']['total_progress']++;

    // Incrememnt rows and columns.
    $context['sandbox']['row']++;
    if ($context['sandbox']['row'] >= $context['sandbox']['image']['levels'][$context['sandbox']['level']]['rows']) {
      $context['sandbox']['row'] = 0;
      $context['sandbox']['column']++;
    }

    // Rollover level counter and cleanup.
    if ($context['sandbox']['level_progress'] >= $context['sandbox']['image']['levels'][$context['sandbox']['level']]['count']) {
      file_unmanaged_delete("{$level_dir}/._temp.{$context['sandbox']['image']['extension']}");

      $context['sandbox']['row'] = 0;
      $context['sandbox']['column'] = 0;
      $context['sandbox']['level_progress'] = 0;
      $context['sandbox']['level']++;
    }
  }

  // Set progress percentage.
  if ($context['sandbox']['total_progress'] != $context['sandbox']['image']['count']) {
    $context['finished'] = $context['sandbox']['total_progress'] / $context['sandbox']['image']['count'];
  }

  // Finish and generate DZI file.
  else {
    file_unmanaged_save_data(theme('deepzoom_dzi', array(
      'size' => $context['sandbox']['config']['tile_size'],
      'overlap' => $context['sandbox']['config']['tile_overlap'],
      'format' => $context['sandbox']['image']['extension'],
      'width' => $context['sandbox']['image']['width'],
      'height' => $context['sandbox']['image']['height'],
    )), "public://deepzoom/{$context['sandbox']['image']['md5']}.dzi", FILE_EXISTS_REPLACE);
  }
}
