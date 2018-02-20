<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="page" class="page-wrapper">
  <header>

    <div class="navbar <?php print $navbar1_classes; ?>">
      <div class="container <?php if ($container_width_navbar == 1): ?>is-fluid<?php endif; ?>">
        <div class="navbar-brand navbar-start">

          <?php if ($logo): ?>
            <a class="navbar-item" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
          <?php endif; ?>

          <?php // @TODO add Site Name ?>

          <?php if ($page['brand']): ?>
            <div class="navbar-item">
              <?php print render($page['brand']); ?>
            </div>
            <?php endif; ?>

            <div class="navbar-burger burger" data-target="MainMenu">
            <span></span><span></span><span></span>
          </div>
        </div>

        <div class="navbar-menu navbar-end">
          <?php if ($page['slogan']): ?>
            <div class="navbar-item">
              <?php print render($page['slogan']) ?>
            </div>
          <?php endif; ?>

          <?php if ($site_slogan) : ?>
            <div class="navbar-item">
              <p><?php print $site_slogan; ?></p>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </div>

    <nav class="navbar <?php print $navbar2_classes; ?>" role="navigation">
      <div class="container <?php if ($container_width_navbar == 1): ?>is-fluid<?php endif; ?>">
        <div id="MainMenu" class="navbar-menu">

          <?php print render($page['main_menu']);  ?>

        </div>

        <?php if ($page['navbar']): ?>
          <div class="navbar-item">
            <?php print render($page['navbar']) ?>
          </div>
        <?php endif; ?>
      </div>
    </nav>
  </header>

  <?php if ($breadcrumb): ?>
    <div class="container <?php if ($container_width_content == 1): ?>is-fluid<?php endif; ?>">
      <nav id="breadcrumb" class="breadcrumb <?php print $breadcrumb_classes; ?>" aria-label="breadcrumbs">
        <?php print $breadcrumb; ?>
      </nav>
    </div>
  <?php endif; ?>

  <?php if ($page['featured']) : ?>
        <div>
          <?php print render($page['featured']); ?>
        </div>
      <?php endif;?>

  <section class="section pt-1" role="main">

      <?php if ($messages) : ?>
        <div class="container <?php if ($container_width_content == 1): ?>is-fluid<?php endif; ?>">
          <div>
            <?php print $messages; ?>
          </div>
        </div>
      <?php endif;?>

      <div class="container <?php if ($container_width_content == 1): ?>is-fluid<?php endif; ?>">

        <div class="columns mt-0">

          <?php if ($page['sidebar_first']) :?>
            <aside class="column is-one-quarter">
              <?php print render($page['sidebar_first']) ?>
            </aside>
          <?php endif;?>

          <div class="column">
            <a id="main-content"></a>

            <?php print render($title_prefix); ?>
            <?php if ($title): ?>
              <h1 class="title">
                <?php print $title; ?>
              </h1>
            <?php endif; ?>

            <?php print render($title_suffix); ?>
            <?php if ($tabs): ?>
              <div class="tabs <?php print $tabs_primary_classes; ?>">
                <?php print render($tabs); ?>
              </div>
            <?php endif; ?>

            <?php if ($action_links): ?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
            <?php endif; ?>

            <?php print render($page['content']); ?>
            <?php print $feed_icons; ?>

          </div>

           <?php if ($page['sidebar_second']) :?>
            <aside class="column is-one-quarter">
              <?php print render($page['sidebar_second']) ?>
            </aside>
          <?php endif;?>

        </div>
      </div>

  </section>

  <footer class="footer" role="contentinfo">
    <div class="container <?php if ($container_width_footer == 1): ?>is-fluid<?php endif; ?>">
      <div class="columns">
        <?php if ($page['footer_first']) : ?>
          <div class="column">
            <?php print render($page['footer_first']) ?>
          </div>
        <?php endif;?>
        <?php if ($page['footer_second']) : ?>
          <div class="column">
            <?php print render($page['footer_second']) ?>
          </div>
        <?php endif;?>
        <?php if ($page['footer_third']) : ?>
          <div class="column">
            <?php print render($page['footer_third']) ?>
          </div>
        <?php endif;?>
        <?php if ($page['footer_fourth']) : ?>
          <div class="column">
            <?php print render($page['footer_fourth']) ?>
          </div>
        <?php endif;?>
      </div>
    </div>
  </footer>
</div>
