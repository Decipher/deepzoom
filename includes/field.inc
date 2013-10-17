<?php
/**
 * @file
 * Field module integration.
 */

/**
 * Implements hook_field_formatter_info().
 */
function deepzoom_field_formatter_info() {
  $items = array();
  $config = deepzoom_config(FALSE);
  if ($config) {
    drupal_alter('deepzoom_field_formatter_info', $items);
  }
  return $items;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function deepzoom_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $function = "{$display['type']}_field_formatter_settings_summary";
  if (function_exists($function)) {
    return $function($settings);
  }
  return '';
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function deepzoom_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $function = "{$display['type']}_field_formatter_settings_form";
  if (function_exists($function)) {
    return $function($settings);
  }
  return array();
}

/**
 * Implements hook_field_formatter_view().
 */
function deepzoom_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $function = "{$display['type']}_field_formatter_view";
  if (function_exists($function)) {
    return $function($obj_type, $object, $field, $instance, $langcode, $items, $display);
  }
  return FALSE;
}
