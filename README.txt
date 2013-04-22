The Deep Zoom module provides the ability to create interactively viewable
high-resolution images using the Microsoft Deep Zoom file format and the
Seadragon Ajax library, ala Zoom.it but hosted 100% locally.

Deep Zoom was written Stuart Clark and is maintained by Stuart Clark (deciphered)
and Brian Gilbert (realityloop) of Realityloop Pty Ltd.
- http://www.realityloop.com
- http://twitter.com/realityloop

Deep Zoom development was initially sponsored by the State Library of Victoria.
- http://www.slv.vic.gov.au



Features
--------------------------------------------------------------------------------

* Multiple display options:
  * Field formatters:
    * Image field formatter.
    * File field formatter.
  * Text format filter.
* Batch API based image processor.
* Drush downloader for required libraries.



Recommended Modules
--------------------------------------------------------------------------------

* Background Batch (via Background Process) - http://drupal.org/project/background_process
* Libraries API                             - http://drupal.org/project/libraries



Installation
--------------------------------------------------------------------------------

1. Download the OpenSeadragon library from
   https://github.com/openseadragon/site-build/raw/master/built-openseadragon/openseadragon.zip
   and extract it to your Libraries folder as 'openseadragon', eg.
   '/sites/all/libraries/openseadragon'.

   or

   Download the Seadragon Ajax library from
   https://github.com/aseemk/seadragon-ajax/archive/v0.8.9.zip and extract it to
   your Libraries folder as 'seadragon', eg. '/sites/all/libraries/seadragon'.


   Note: If you wish to keep the Seadragon or OpenSeadragon library in a
         directory other than the examples you will need to install the
         Libraries API module first.


  Note: If you have Drush you can also use the 'deepzoom-library' Drush command
        to download your library of choice. Type 'drush dzlib --help' for more
        information.


2. Install module as usual, see http://drupal.org/node/895232 for further
   information.



OpenSeadragon
--------------------------------------------------------------------------------

As of Deep Zoom 1.2, support for the OepnSeadragon has been introduced as a
completely open source alternative to the Microsoft Seadragon Ajax library.

Support is only minimal, but new functionality will be introduced in future
releases.

OpenSeadragon is the recommended library for use with the Deep Zoom module.



Offline processing
--------------------------------------------------------------------------------

Thanks to the sponsorship of Orygen YOUTH Health (http://oyh.org.au), Deep Zoom
images can be processed offline and uploaded to a File field as a Zip archive
instead of having the image processed via the Drupal module.

To do so, you will need to follow these instructions:


1. Download and install the 'Deep Zoom Composer' application for Windows:

    http://www.microsoft.com/en-us/download/details.aspx?id=24819

2. Run the 'Deep Zoom Composer' application.

3. Create a 'New Project...'.

4. Import your image(s) via the 'Import' tab.

5. Arrange your image(s) on the canvas via the 'Compose' tab.

6. Export your Deep Zoom image via the 'Export' tab with the following settings:

    - Output type: Seadragon Ajax

7. Locate your exported files and archive the contents of the 'GeneratedImages'
   folder as a Zip file, so that your zip file should be similar to:

    /dzc_output_files/*
    /dzc_output.xml
    /scene.xml
    /SparesImageSceneGraph.xml

8. Upload the Zip archive to a File field that uses the Deep Zoom field
   formatter.



Makefile entries
--------------------------------------------------------------------------------

For easy downloading of Deep Zoom and it's required modules and/or libraries,
you can use the following entries in your makefile:


  projects[deepzoom][subdir] = contrib
  projects[deepzoom][version] = 1.2

  projects[libraries][subdir] = contrib
  projects[libraries][version] = 2.0

  libraries[seadragon][download][type] = get
  libraries[seadragon][download][url] = https://github.com/aseemk/seadragon-ajax/zipball/v0.8.9

  libraries[openseadragon][download][type] = get
  libraries[openseadragon][download][url] = https://github.com/openseadragon/site-build/raw/34832de71fe659f7571320abc8bcc4b27e2e0833/built-openseadragon/openseadragon.zip
