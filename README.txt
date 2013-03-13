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



Required Modules
--------------------------------------------------------------------------------

* Libraries API - http://drupal.org/project/libraries



Recommended Modules
--------------------------------------------------------------------------------

* Background Batch (via Background Process) - http://drupal.org/project/background_process



Installation
--------------------------------------------------------------------------------

1. Download the Seadragon Ajax library from
   https://github.com/aseemk/seadragon-ajax/zipball/v0.8.9 and extract it to
   your Libraries folder as 'seadragon', eg. '/sites/all/libraries/seadragon'.

   or

   Download the OpenSeadragon library from
   https://github.com/openseadragon/openseadragon/archive/master.zip and extract
   it to your Libraries folder as 'openseadragon', eg.
   '/sites/all/libraries/openseadragon'.

2. Install module as usual, see http://drupal.org/node/895232 for further
   information.



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
