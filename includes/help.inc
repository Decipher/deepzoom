<?php
/**
 * @file
 * Help module integration.
 */

/**
 * Implements hook_help().
 */
function deepzoom_help($path, $arg) {
  switch ($path) {
    case 'admin/help#deepzoom':
      $output = '<h3>' . t('About') . "</h3>\n"
              . "<p>\n"
              . '  ' . t('The Deep Zoom module provides the ability to create interactively viewable, high-resolution images using the Microsoft Deep Zoom file format and the Seadragon Ajax library, ala <a href="http://zoom.it">Zoom.it</a> but hosted 100% locally.') . "\n"
              . "</p>\n"
              . "<p>&nbsp;</p>\n"
              . '<h3>' . t('Offline processing') . "</h3>\n"
              . "<p>\n"
              . '  ' . t('Thanks to the sponsorship of <a href="http://oyh.org.au">Orygen YOUTH Health</a>, Deep Zoom images can be processed offline and uploaded to a File field as a Zip archive instead of having the image processed via the Drupal module.') . "\n"
              . "</p>\n"
              . "<p>\n"
              . '  ' . t('To do so, you will need to follow these instructions:') . "\n"
              . "</p>\n"
              . "<ol>\n"
              . '  <li>' . t('Download and install the <a href="http://www.microsoft.com/en-us/download/details.aspx?id=24819">Deep Zoom Composer</a> application for Windows:') . "</li>\n"
              . '  <li>' . t('Run the <strong>Deep Zoom Composer</strong> application.') . "</li>\n"
              . '  <li>' . t('Create a <strong>New Project...</strong>.') . "</li>\n"
              . '  <li>' . t('Import your image(s) via the <strong>Import</strong> tab.') . "</li>\n"
              . '  <li>' . t('Arrange your image(s) on the canvas via the <strong>Compose</strong> tab.') . "</li>\n"
              . "  <li>\n"
              . '    ' . t('Export your Deep Zoom image via the <strong>Export</strong> tab with the following settings:') . "\n"
              . "    <ul>\n"
              . '      <li>' . t('<strong>Output type:</strong> Seadragon Ajax') . "</li>\n"
              . "    </ul>\n"
              . "  </li>\n"
              . "  <li>\n"
              . '    ' . t('Locate your exported files and archive the contents of the <strong>GeneratedImages</strong> folder as a Zip file, so that your zip file should be similar to:') . "\n"
              . "    <blockquote>\n"
              . "      /dzc_output_files/*<br />\n"
              . "      /dzc_output.xml<br />\n"
              . "      /scene.xml<br />\n"
              . "      /SparesImageSceneGraph.xml\n"
              . "    </blockquote>\n"
              . "  </li>\n"
              . '  <li>' . t('Upload the Zip archive to a File field that uses the Deep Zoom field formatter.') . "</li>\n"
              . "</ol>\n"
              . "<p>&nbsp;</p>\n";
      return $output;
  }
}
