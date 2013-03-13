<?php
/**
 * @file
 * OpenSeadragon engine integration.
 */

/**
 * Implements deepzoom_engine_HOOK_info().
 */
function deepzoom_engine_openseadragon_info(&$items) {
  $items['openseadragon'] = array(
    'name' => t('openseadragon Ajax'),
    'callbacks' => array(
      'defaults' => 'deepzoom_engine_openseadragon_defaults',
      'page alter' => 'deepzoom_engine_openseadragon_page_alter',
      'settings form' => 'deepzoom_engine_openseadragon_settings_form',
      'submit' => 'deepzoom_engine_openseadragon_submit',
    ),
  );
}

/**
 * Defaults callback for openseadragon Ajax engine.
 */
function deepzoom_engine_openseadragon_defaults() {
  $defaults = array(
    'tile_size' => 254,
  );
  return array_merge($defaults, variable_get('deepzoom_config', $defaults));
}

/**
 * Page alter callback for openseadragon Ajax engine.
 */
function deepzoom_engine_openseadragon_page_alter($variables) {
  global $base_url;

  drupal_add_js(drupal_get_path('module', 'deepzoom') . '/engines/deepzoom.openseadragon.js');
  drupal_add_js(libraries_get_path('openseadragon') . '/openseadragon.js');

  $path = str_replace($base_url, '', file_create_url('public://deepzoom'));
  drupal_add_js(array('deepZoom' => array(
    'path' => $path
  )), 'setting');
}

/**
 * Settings form callback for openseadragon Ajax engine.
 */
function deepzoom_engine_openseadragon_settings_form($config) {
  $form = array();

  $form['tile_size'] = array(
    '#title' => t('tile size'),
    '#type' => 'textfield',
    '#default_value' => $config['tile_size'],
    '#description' => t('tile size setting.'),
  );

  return $form;
}

/**
 * Submit callback for openseadragon Ajax engine.
 */
function deepzoom_engine_openseadragon_submit($form = array(), $form_state = array()) {

}
