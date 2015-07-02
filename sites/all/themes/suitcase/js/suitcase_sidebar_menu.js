/**
 * @todo
 */

(function($) {
    /**
     * @todo
     */
    Drupal.behaviors.suitcaseSidebarMenu = {
        attach: function (context) {
            $('body', context).once('suitcaseSidebarMenu', function() {
                var isTouchedAlready = false,
                    $sidebar_button = $('nav.navigation ul li a:contains(≡)'),
                    sidebar_offset = 300,
                    $sidebarmenu = $('#zone-side-menu-wrapper'),
                    $page = $('#page'),
                    top;
                $sidebarmenu.addClass('sidebar-close');
                $page.addClass('page-close');
                $sidebar_button
                .bind('click touchend', function(e) {
                    if(isTouchedAlready) {isTouchedAlready = false;return;}
                    toggleMenu();
                    isTouchedAlready = (e.type == 'touchend');
                })
                .show()
                .removeAttr('href')
                .css('font-weight', 'bold')
                .css('font-size', '1.5em');

                function toggleMenu() {
                    $sidebarmenu.toggleClass('sidebar-close').toggleClass('sidebar-open');
                    if(parseFloat($('#zone-content').css('margin-left')) < sidebar_offset) {
                        if($page.hasClass('page-close')) {
                            $page.addClass('page-open').removeClass('page-close').css('transition', '0.2s').css('left', sidebar_offset);
                        } else {
                            $page.addClass('page-close').removeClass('page-open').css('transition', '0.2s').css('left', 0);
                        }
                    }
                }

                function HideMenu() {
                    $('body:not(#zone-side-menu-wrapper)').unbind('click touchstart');
                }

                function setSideMenuCloseButtonPosition() {
                    $('#side-menu-close-button').css('top', $('#admin-menu').height());
                }

                function setSideMenuWrapperPaddingTop() {
                    $('#zone-side-menu-wrapper').css('padding-top', $('#admin-menu').height());
                }

                if($('#admin-menu')) {
                    top = $('#admin-menu').height() + 5;
                    setSideMenuWrapperPaddingTop();
                } else {
                    top = 5;
                }

                $(window).resize(function() {
                    if(parseInt($('#zone-side-menu-wrapper').css('left')) == 0) {
                        //HideMenu(sidebar_offset);
                        setSideMenuWrapperPaddingTop();
                        setSideMenuCloseButtonPosition();
                    }
                });

                // Close Button
                $sidebarmenu.append('<img src="' + Drupal.settings.basePath + 'sites/all/themes/suitcase/images/close-button-white.png" id="side-menu-close-button" style="top: ' + top + 'px">');
                $('#side-menu-close-button').bind('click touchend',function(e) {
                    if(isTouchedAlready){isTouchedAlready=false;return;}
                    HideMenu();
                    toggleMenu();
                    isTouchedAlready = (e.type == 'touchend');
                });
            });
        }
    };
})(jQuery);