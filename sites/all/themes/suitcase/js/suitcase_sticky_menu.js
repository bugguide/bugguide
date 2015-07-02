/**
 * @todo
 */

(function($) {
    /**
     * @todo
     */
    Drupal.behaviors.suitcaseStickyMenu = {
        attach: function (context) {
            $('body', context).once('suitcaseStickyMenu', function() {
                var $menu = $('#zone-menu'),
                    admin_menu_height = ($('#admin-menu').length) ? $('#admin-menu').height() : 0,
                    menu_offset_top = (admin_menu_height > 0) ? $menu.offset().top - admin_menu_height : $menu.offset().top,
                    menu_offset_left = $menu.offset().left,
                    MIN_WINDOW_WIDTH = 740,
                    sticky_class = 'sticky-top',
                    classNotSticky = true;

                $(window).resize(function() {
                    admin_menu_height = ($('#admin-menu').length) ? $('#admin-menu').height() : 0;
                    menu_offset_top = (admin_menu_height > 0) ? $menu.offset().top - admin_menu_height : $menu.offset().top;
                    menu_offset_left = $menu.offset().left;
                    if($(this).width() < MIN_WINDOW_WIDTH) {
                        resetStickyMenuPosition();
                    }
                });

                $(window).bind('scroll', function(e) {
                    updateStickyMenuPosition();
                }).bind('touchmove', function(e) {
                    updateStickyMenuPosition();
                }).bind('touchend', function(e) {
                    updateStickyMenuPosition();
                });

                $(document).bind('focus', 'select, input, textarea', function(e) {
                    updateStickyMenuPosition();
                })

                function updateStickyMenuPosition() {
                    if($(this).width() < MIN_WINDOW_WIDTH) {
                        resetStickyMenuPosition();
                    } else {
                        var scrollTop = $(window).scrollTop();

                        if(scrollTop > menu_offset_top) {
                            if(classNotSticky) {
                                $('#zone-menu-wrapper').css('height', $('#zone-menu-wrapper').height());
                                $menu.addClass(sticky_class).css({ 'top': admin_menu_height, 'padding-left': menu_offset_left});
                                classNotSticky = false;
                            }
                        }
                        else {
                            resetStickyMenuPosition();
                            classNotSticky = true;
                        }
                    }
                }

                function resetStickyMenuPosition() {
                    $menu.removeClass(sticky_class).css({'top': '', 'padding-left': ''});
                    $('#zone-menu-wrapper').css('height', '');
                }
            });
        }
    };
})(jQuery);