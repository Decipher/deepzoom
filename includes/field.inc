<?php
/**
 * @file
 * Field module integration.
 */

/**
 * Implements hook_field_formatter_info().
 */
function deepzoom_field_formatter_info() {
  return array(
    'deepzoom_deepzoom' => array(
      'label' => t('Deep Zoom'),
      'field types' => array('image'),
      'settings' => array(
        'deepzoom_processor' => 'batch',
        'deepzoom_image_style' => 'large'
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function deepzoom_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == 'deepzoom_deepzoom') {
    $summary .= t('DeepZoom processor: @processor', array('@processor' => $settings['deepzoom_processor'])) . '<br />';
    $summary .= t('Fallback image style: @image_style', array('@image_style' => $settings['deepzoom_image_style']));
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function deepzoom_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'deepzoom_deepzoom') {
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
  }

  return $element;
}

/**
 * Implements hook_field_formatter_view().
 */
function deepzoom_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $settings = $display['settings'];

  $images = array();
  foreach ($items as $item) {
    $images[md5_file($item['uri'])] = $item['uri'];
  }

  return count($images) ? theme('deepzoom', array('images' => $images, 'image_style' => $settings['deepzoom_image_style'], 'processor' => $settings['deepzoom_processor'])) : FALSE;
}
