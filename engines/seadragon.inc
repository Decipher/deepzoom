<?php
/**
 * @file
 * Seadragon Ajax engine integration.
 */

/**
 * Implements deepzoom_engine_HOOK_info().
 */
function deepzoom_engine_seadragon_info(&$items) {
  $items['seadragon'] = array(
    'name' => t('Seadragon Ajax'),
    'callbacks' => array(
      'defaults' => 'deepzoom_engine_seadragon_defaults',
      'page alter' => 'deepzoom_engine_seadragon_page_alter',
      'settings form' => 'deepzoom_engine_seadragon_settings_form',
      'submit' => 'deepzoom_engine_seadragon_submit',
    ),
  );
}

/**
 * Defaults callback for Seadragon Ajax engine.
 */
function deepzoom_engine_seadragon_defaults() {
  $path = module_exists('libraries') ? libraries_get_path('seadragon') : 'sites/all/libraries/seadragon';
  $defaults = array(
    'debugMode' => FALSE,
    'animationTime' => 1.5,
    'blendTime' => 0.5,
    'alwaysBlend' => FALSE,
    'autoHideControls' => TRUE,
    'immediateRender' => FALSE,
    'wrapHorizontal' => FALSE,
    'wrapVertical' => FALSE,
    'wrapOverlays' => FALSE,
    'transformOverlays' => FALSE,
    'minZoomImageRatio' => 0.8,
    'maxZoomPixelRatio' => 2,
    'visibilityRatio' => 0.5,
    'springStiffness' => 5.0,
    'imageLoaderLimit' => 2,
    'clickTimeThreshold' => 200,
    'clickDistThreshold' => 5,
    'zoomPerClick' => 2,
    'zoomPerScroll' => 1.2,
    'zoomPerSecond' => 2,
    'proxyUrl' => NULL,
    'imagePath' => base_path() . $path . '/img/',
    'tile_size' => 254,
    'tile_overlap' => 1,
  );
  return array_merge($defaults, variable_get('deepzoom_config', $defaults));
}

/**
 * Page alter callback for Seadragon Ajax engine.
 */
function deepzoom_engine_seadragon_page_alter($vars) {
  $path = module_exists('libraries') ? libraries_get_path('seadragon') : 'sites/all/libraries/seadragon';

  drupal_add_js(drupal_get_path('module', 'deepzoom') . '/engines/deepzoom.seadragon.js');
  drupal_add_js($path . '/seadragon-min.js');
  drupal_add_js(array('deepZoom' => array(
    'path' => file_create_url('public://deepzoom')
  )), 'setting');

  $config = 'public://deepzoom/deepzoom_config.js';
  if (!file_exists($config)) {
    deepzoom_engine_seadragon_submit();
  }
  drupal_add_js($config);
}

/**
 * Settings form callback for Seadragon Ajax engine.
 */
function deepzoom_engine_seadragon_settings_form(&$vars) {
  $form = array();
  $config = $vars['config'];

  $form['debugMode'] = array(
    '#title' => t('Debug mode'),
    '#type' => 'checkbox',
    '#default_value' => $config['debugMode'],
    '#description' => t('Whether messages should be logged and fail-fast behavior should be provided.'),
  );

  $form['animationTime'] = array(
    '#title' => t('Animation time'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['animationTime'],
    '#description' => t('The amount of time in seconds that animations should last.'),
  );

  $form['blendTime'] = array(
    '#title' => t('Blend time'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['blendTime'],
    '#description' => t('The amount of time in seconds that new tiles take to blend from transparent to opaque.'),
  );

  $form['alwaysBlend'] = array(
    '#title' => t('Always blend'),
    '#type' => 'checkbox',
    '#default_value' => $config['alwaysBlend'],
    '#description' => t('Whether tiles should always blend in and out, not just when they\'re first loaded.'),
  );

  $form['autoHideControls'] = array(
    '#title' => t('Auto hide controls'),
    '#type' => 'checkbox',
    '#default_value' => $config['autoHideControls'],
    '#description' => t('Whether controls should get automatically hidden when the user\'s mouse is off the viewer and the image has stopped animating.'),
  );

  $form['immediateRender'] = array(
    '#title' => t('Immediate render'),
    '#type' => 'checkbox',
    '#default_value' => $config['immediateRender'],
    '#description' => t('Whether the most appropriate tiles should always be rendered first, before any lower-res tiles are rendered. This loses the "sharpening" effect and instead creates a very visible "tiling" effect.'),
  );

  $form['wrapHorizontal'] = array(
    '#title' => t('Wrap horizontal'),
    '#type' => 'checkbox',
    '#default_value' => $config['wrapHorizontal'],
    '#description' =>
      t('Whether tiles should be "wrapped" horizontally, so that there are no left or right edges.') . '<br />' .
      '<strong>' . t('NOTE: this is an experimental API and is not guaranteed to work. The API is also very likely to change in the future. Use at your own risk!') . '</strong>',
  );

  $form['wrapVertical'] = array(
    '#title' => t('Wrap vertical'),
    '#type' => 'checkbox',
    '#default_value' => $config['wrapVertical'],
    '#description' =>
      t('Whether tiles should be "wrapped" vertically, so that there are no top or bottom edges.') . '<br />' .
      '<strong>' . t('NOTE: this is an experimental API and is not guaranteed to work. The API is also very likely to change in the future. Use at your own risk!') . '</strong>',
  );

  $form['wrapOverlays'] = array(
    '#title' => t('Wrap overlays'),
    '#type' => 'checkbox',
    '#default_value' => $config['wrapOverlays'],
    '#description' =>
      t('Whether overlays should be continually re-positioned to match any horizontal or vertical wrapping. This has no effect if neither wrapHorizontal nor wrapVertical are set.') . '<br />' .
      '<strong>' . t('NOTE: this is an experimental API and is not guaranteed to work. The API is also very likely to change in the future. Use at your own risk!') . '</strong>',
  );

  $form['transformOverlays'] = array(
    '#title' => t('Transform overlays'),
    '#type' => 'checkbox',
    '#default_value' => $config['transformOverlays'],
    '#description' =>
      t('Whether overlays should be scaled using !link rather than regular block sizing, in browsers that support it. This smoothly scales overlays and their content, including text, but the results may not appear the same in other browsers.', array('!link' => l(t('CSS transforms'), 'http://www.w3.org/TR/css3-2d-transforms/'))) . '<br />' .
      '<strong>' . t('NOTE: this is an experimental API and is not guaranteed to work. The API is also very likely to change in the future. Use at your own risk!') . '</strong>',
  );

  $form['minZoomImageRatio'] = array(
    '#title' => t('Minimum zoom image ratio'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['minZoomImageRatio'],
    '#description' => t('The minimum image ratio (image size to viewer size) in both dimensions that can result from zooming out.'),
  );

  $form['maxZoomPixelRatio'] = array(
    '#title' => t('Maximum zoom pixel ratio'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['maxZoomPixelRatio'],
    '#description' => t('The maximum pixel ratio (screen pixel to content pixel) that can result from zooming in.'),
  );

  $form['visibilityRatio'] = array(
    '#title' => t('Visibility ratio'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['visibilityRatio'],
    '#description' => t('The minimum portion of the viewport that must show visible content in both dimensions.'),
  );

  $form['springStiffness'] = array(
    '#title' => t('Spring stiffness'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['springStiffness'],
    '#description' => t('Determines how sharply the springs used for animations move.'),
  );

  $form['imageLoaderLimit'] = array(
    '#title' => t('Image loader limit'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['imageLoaderLimit'],
    '#description' => t('The maximum number of concurrent image downloads that can be performed by each viewer.'),
  );

  $form['clickTimeThreshold'] = array(
    '#title' => t('Click time threshold'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['clickTimeThreshold'],
    '#description' => t('The maximum number of milliseconds that can pass between a mousedown and a mouseup for the action to still be considered a "quick" click.'),
  );

  $form['clickDistThreshold'] = array(
    '#title' => t('Click distance threshold'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['clickDistThreshold'],
    '#description' => t('The maximum number of pixels the mouse can move between a mousedown and a mouseup for the action to still be considered a "quick" click.'),
  );

  $form['zoomPerClick'] = array(
    '#title' => t('Zoom per click'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['zoomPerClick'],
    '#description' => t('The factor by which images should zoom when clicked on.'),
  );

  $form['zoomPerScroll'] = array(
    '#title' => t('Zoom per scroll'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['zoomPerScroll'],
    '#description' => t('The factor by which images should zoom when scrolled over.'),
  );

  $form['zoomPerSecond'] = array(
    '#title' => t('Zoom per second'),
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => $config['zoomPerSecond'],
    '#description' => t('The factor by which images should zoom over each second when the zoom buttons are held down.'),
  );

  $form['proxyUrl'] = array(
    '#title' => t('Proxy URL'),
    '#type' => 'textfield',
    '#default_value' => $config['proxyUrl'],
    '#description' => t('The URL to prefix before any AJAX requests to overcome browser cross-site restrictions. The URL should be of the form "some/proxy.aspx?site=", so that the target site URL is passed as a GET parameter to the proxy. This URL can be absolute or relative, but must be on the same domain as the HTML page. If relative, it must be relative to the HTML page.'),
  );

  $form['imagePath'] = array(
    '#title' => t('Image path'),
    '#type' => 'textfield',
    '#default_value' => $config['imagePath'],
    '#description' => t('The path for all UI images. This can be absolute or relative. If relative, it must be relative to the HTML page. A change to this value will only affect new viewers.'),
  );

  $form['tile_size'] = array(
    '#title' => t('tile size'),
    '#type' => 'textfield',
    '#default_value' => $config['tile_size'],
    '#description' => t('tile size setting.'),
  );

  $form['tile_overlap'] = array(
    '#title' => t('tile overlap'),
    '#type' => 'textfield',
    '#default_value' => $config['tile_overlap'],
    '#description' => t('tile overlap setting.'),
  );

  return $form;
}

/**
 * Submit callback for Seadragon Ajax engine.
 */
function deepzoom_engine_seadragon_submit($vars = array()) {
  $directory = 'public://deepzoom';
  if (file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    $data = '';
    if (!empty($vars)) {
      $config = $vars['form_state']['values']['deepzoom_config'];
    }
    else {
      $config = deepzoom_engine_seadragon_defaults();
    }
    foreach ($config as $key => $value) {
      $data .= "Seadragon.Config.{$key} = " . drupal_json_encode($value) . ";\r\n";
    }
    file_save_data($data, "{$directory}/deepzoom_config.js", FILE_EXISTS_REPLACE);
    drupal_flush_all_caches();
  }
}
