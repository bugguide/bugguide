/**
 * @todo
 */

(function($) {
    /**
     * @todo
     */
    Drupal.behaviors.suitcaseFacet = {
        attach: function (context) {
            $('body', context).once('suitcaseFacet', function() {
                $('.zone-content section.block').addClass('js-suitcase-facet');
                var touched = false;

                $('.js-suitcase-facet .block-title').each(function() {
                    $(this).append('<span class="caret"></span>');
                }).bind('click touchend', function(e) {
                    if(touched) {e.preventDefault();touched=false;return;}
                    $(this).parent().find('.content').toggle();
                    touched = (e.type == 'touchend');
                });

                if($(window).width() < 980) {
                    $('.js-suitcase-facet .content').toggle();
                }
            });
        }
    };
})(jQuery);
