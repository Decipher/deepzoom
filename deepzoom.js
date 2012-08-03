(function($) {
  Drupal.behaviors.deepzoom = {
    attach: function(context) {
      Seadragon.Utils.addEvent(window, 'load', function() {
        $('.deepzoom').each(function() {
          id = $(this).attr('id').split('-');
          viewer = new Seadragon.Viewer(id.join('-'));
          viewer.openDzi(Drupal.settings.deepZoom.path + '/' + id[1] + '.dzi');
        });
      });
    }
  };
})(jQuery);
