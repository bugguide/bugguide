(function (window, $) {
  $(function() {
    // Get all "menu-toggle" elements
    var $navbarBurgers = Array.prototype.slice.call(document.querySelectorAll('.menu-toggle'), 0);

    // Check if there are any navbar burgers
    if ($navbarBurgers.length > 0) {

      // Add a click event on each of them
      $navbarBurgers.forEach(function ($el) {
        $el.addEventListener('click', function () {

          // Get the target from the "data-target" attribute
          var target = $el.dataset.target;
          var $target = document.getElementById(target);

          // Toggle the class on both the "navbar-burger" and the "navbar-menu"
          $el.classList.toggle('is-active');
          var pressed = ($el.getAttribute("aria-pressed") === "true");
          $el.setAttribute("aria-pressed", !pressed);
          $target.classList.toggle('is-active');

        });
      });
    }
  });
})(window, jQuery);