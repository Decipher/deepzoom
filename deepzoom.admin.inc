<?php
/**
 * @file
 */

/**
 * Deep Zoom configuration form.
 */
function deepzoom_configuration_form($form, &$form_state) {
  $config = deepzoom_config();
  if ($config) {
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
    $vars = array();
    $config = deepzoom_invoke('defaults', $vars, $engine);

    // Attach settings form.
    $vars = array('config' => $config);
    $return = deepzoom_invoke('settings form', $vars, $engine);
    if (is_array($return)) {
      $form['deepzoom_config'] += deepzoom_invoke('settings form', $vars, $engine);
    }

    $form['#submit'][] = 'deepzoom_configuration_form_submit';

    return system_settings_form($form);
  }
  return '';
}

/**
 * Submit handler for Deep Zoom configuration form.
 */
function deepzoom_configuration_form_submit($form, &$form_state) {
  $engines = deepzoom_get_engines();
  $engine = $form_state['values']['deepzoom_config']['engine'];

  // Attach submit callback.
  $vars = array('form' => $form, 'form_state' => $form_state);
  deepzoom_invoke('submit', $vars);
}

/**
 * Ajax callback for Deep Zoom configuration form.
 */
function deepzoom_config_ajax($form, &$form_state) {
  return $form['deepzoom_config'];
}
