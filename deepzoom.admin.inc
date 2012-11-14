<?php
/**
 * @file
 */

/**
 * Deep Zoom configuration form.
 */
function deepzoom_configuration_form($form, &$form_state) {
  $config = variable_get('deepzoom_config', array());
  $engines = deepzoom_get_engines();

  $form['deepzoom_config'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="ajax-wrapper">',
    '#suffix' => '</div>',
  );

  $options = array();
  foreach ($engines as $key => $engine) {
    $options[$key] = $engine['name'];
  }
  $engine = NULL;
  if (isset($form_state['values']['deepzoom_config']['engine'])) {
    $engine = $form_state['values']['deepzoom_config']['engine'];
  }
  else {
    if (isset($config['engine'])) {
      $engine = $config['engine'];
    }
    else {
      $engine = key($options);
    }
  }
  $form['deepzoom_config']['engine'] = array(
    '#title' => t('Engine'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $engine,
    '#ajax' => array(
      'callback' => 'deepzoom_config_ajax',
      'wrapper' => 'ajax-wrapper',
    ),
  );

  // Get configuration defaults.
  $function = isset($engines[$engine]['callbacks']['defaults']) ? $engines[$engine]['callbacks']['defaults'] : 'deepzoom_engine_{$engine}_defaults';
  if (function_exists($function)) {
    $config = $function();
  }

  // Attach settings form.
  $function = isset($engines[$engine]['callbacks']['settings form']) ? $engines[$engine]['callbacks']['settings form'] : 'deepzoom_engine_{$engine}_settings_form';
  if (function_exists($function)) {
    $form['deepzoom_config'] += $function($config);
  }

  $form['#submit'][] = 'deepzoom_configuration_form_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for Deep Zoom configuration form.
 */
function deepzoom_configuration_form_submit($form, &$form_state) {
  $engines = deepzoom_get_engines();
  $engine = $form_state['values']['deepzoom_config']['engine'];

  // Attach submit callback.
  $function = isset($engines[$engine]['callbacks']['submit']) ? $engines[$engine]['callbacks']['submit'] : 'deepzoom_engine_{$engine}_submit';
  if (function_exists($function)) {
    $function($form, $form_state);
  }
}

/**
 * Ajax callback for Deep Zoom configuration form.
 */
function deepzoom_config_ajax($form, &$form_state) {
  return $form['deepzoom_config'];
}
