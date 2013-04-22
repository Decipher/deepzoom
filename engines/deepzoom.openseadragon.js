(function($) {
  Drupal.behaviors.deepzoom = {
    attach: function(context) {
      $('.deepzoom').each(function() {
        id = $(this).attr('id').split('-');
        viewer = new OpenSeadragon.Viewer({
          id: id.join('-'),
          prefixUrl: Drupal.settings.deepZoom.library + '/images/',
          tileSources: Drupal.settings.deepZoom.path + '/' + id[1] + '.dzi',
        });
      });
    }
  };
})(jQuery);
