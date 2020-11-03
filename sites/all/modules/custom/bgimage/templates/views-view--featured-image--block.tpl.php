<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>

<?php
/**
  * During the Featured Image view has a filter that refers to a specific bgimage node
  * but that node is not present during development. Initialize an empty array instead
  * of emitting errors.
  */
?>
<?php if (!isset($view->style_plugin->rendered_fields)): ?>
  <?php $view->style_plugin->rendered_fields = array(); ?>
<?php endif; ?>

<section aria-label="Welcome Banner" class="hero is-primary" style="background-image: url(<?php foreach ($view->style_plugin->rendered_fields as $delta => $item): ?><?php print $item['uri']; ?><?php endforeach; ?>); background-size: cover; background-position: center;">
  <div class="hero-body">
    <div class="container">
      <div class="columns">
        <div class="column is-one-third-desktop is-half-tablet">
          <div class="card">
            <?php if ($title): ?>
              <header class="card-header">
                <p class="card-header-title">
                  <?php print $title; ?>
                </p>
              </header>
            <?php endif; ?>
              
            <div class="card-content">
              <div class="content">
                <?php if ($header): ?>
                  <div class="view-header">
                    <?php print $header; ?>
                  </div>
                <?php endif; ?>
              </div>
            </div>

            <footer class="card-footer">
              <?php if ($footer): ?>
                <?php print $footer; ?>
              <?php endif; ?>
            </footer>
          </div>
        </div>
      </div>
    </div>
  </div><!--
  <div class="hero-foot">
    <div class="container">
      <div class="tag mb-1">
        <?php // foreach ($view->style_plugin->rendered_fields as $delta => $item): ?>
          <?php // print $item['field_bgimage_copyright_owner']; ?>
        <?php // endforeach; ?>
      </div>
    </div>
  </div>-->
</section>