(function($) {
  Drupal.behaviors.deepzoom = {
    attach: function(context) {
      $('.deepzoom').each(function() {
        id = $(this).attr('id').split('-');
        viewer = new OpenSeadragon.Viewer({
          id: id.join('-'),
          prefixUrl: '/sites/dz.ld/libraries/openseadragon/images/',
          tileSources: '/sites/dz.ld/files/deepzoom/' + id[1] + '.dzi',
        });
      });
    }
  };
})(jQuery);
