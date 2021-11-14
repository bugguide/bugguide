<nav class="navbar filters-navbar">
  <button class="button is-tan menu-toggle" data-target="FilterOptions" aria-pressed="false">
    <span class="icon"><span class="fa fa-sliders" aria-hidden="true"></span></span>
    <span>Filters</span>
  </button>

  <div id="FilterOptions" class="navbar-menu">
    <?php print drupal_render($filters_form); ?>
  </div>
</nav>
