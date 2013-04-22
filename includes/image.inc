<?php
/**
 * @file
 * Image module integration.
 */

/**
 * Implements hook_deepzoom_image_alter() on behalf of image.module.
 */
function image_deepzoom_theme_alter(&$items) {
  // This theme function is deprecated and will be removed in a future release
  // in favour of 'deepzoom_image'.
  $items['deepzoom'] = array(
    'variables' => array(
      'images' => array(),
      'image_style' => 'large',
      'processor' => 'batch',
    ),
  );

  $items['deepzoom_image'] = array(
    'variables' => array(
      'images' => array(),
      'image_style' => 'large',
      'processor' => 'batch',
    ),
  );
}

/**
 * Implememnts hook_deepzoom_field_formatter_info_alter() on behalf of
 * image.module.
 */
function image_deepzoom_field_formatter_info_alter(&$items) {
  $items['deepzoom_image'] = array(
    'label' => t('Deep Zoom'),
    'field types' => array('image'),
    'settings' => array(
      'deepzoom_processor' => 'batch',
      'deepzoom_image_style' => 'large',
      'engine_settings' => array(),
    ),
  );
}

/**
 * Field formatter settings summary callback for Deep Zoom Image formatter.
 */
function deepzoom_image_field_formatter_settings_summary($settings) {
  $summary = t('Deep Zoom processor: @processor', array('@processor' => $settings['deepzoom_processor'])) . '<br />';
  $summary .= t('Fallback image style: @image_style', array('@image_style' => $settings['deepzoom_image_style']));

  $config = deepzoom_config();
  $engines = deepzoom_get_engines();
  $engine = $config['engine'];

  // Engine specific summary.
  $vars = array('summary' => $summary, 'settings' => $settings);
  deepzoom_invoke('formatter summary', $vars);

  return $vars['summary'];
}

/**
 * Field formatter settings form callback for Deep Zoom Image formatter.
 */
function deepzoom_image_field_formatter_settings_form($settings) {
  $element = array();

  $info = module_invoke_all('deepzoom_processor_info');
  $element['deepzoom_processor'] = array(
    '#title' => t('Processor'),
    '#type' => 'select',
    '#default_value' => $settings['deepzoom_processor'],
    '#options' => drupal_map_assoc(array_keys($info)),
    '#required' => TRUE,
  );

  $element['deepzoom_image_style'] = array(
    '#title' => t('Fallback image style'),
    '#type' => 'select',
    '#default_value' => $settings['deepzoom_image_style'],
    '#options' => array(),
    '#required' => TRUE,
  );
  foreach (array_keys(image_styles()) as $image_style) {
    $element['deepzoom_image_style']['#options'][$image_style] = $image_style;
  }

  // Engine specific settings.
  $vars = array('element' => $element, 'settings' => $settings);
  deepzoom_invoke('formatter settings', $vars);

  return $vars['element'];
}

/**
 * Field formatter view callback for Deep Zoom Image formatter.
 */
function deepzoom_image_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $settings = $display['settings'];

  $images = array();
  foreach ($items as $item) {
    $images[md5_file($item['uri'])] = $item['uri'];
  }

  if (count($images)) {
    return theme('deepzoom_image', array(
      'images' => $images,
      'image_style' => $settings['deepzoom_image_style'],
      'processor' => $settings['deepzoom_processor']
    ));
  }
  return FALSE;
}

/**
 * Theme function; Deep Zoom.
 *
 * This theme function is deprecated and will be removed in a future release
 * in favour of 'deepzoom_image'.
 */
function theme_deepzoom($variables) {
  watchdog('deepzoom', "theme('deepzoom') has been deprecated and will be removed in a future release in favour of theme('deepzoom_image').");
  return theme('deepzoom_image', $variables);
}

/**
 * Theme function; Deep Zoom Image.
 */
function theme_deepzoom_image($variables) {
  $elements = array();

  $images = is_array($variables['images'])
    ? $variables['images']
    : array(md5_file($variables['images']) => $variables['images']);
  $status = deepzoom_generate_deepzoom($images, $variables['processor']);

  foreach ($images as $md5 => $uri) {
    if ($status[$uri]) {
      $elements[] = array(
        '#theme' => 'deepzoom_wrapper',
        '#md5' => $md5,
      );
    }

    // Fallback image.
    else {
      $elements[] = array(
        '#theme' => 'image_style',
        '#path' => str_replace(DRUPAL_ROOT, '', $uri),
        '#style_name' => $variables['image_style'],
      );
    }
  }

  // Nothing to return;
  if (!isset($elements[0])) {
    return FALSE;
  }

  return $elements;
}


