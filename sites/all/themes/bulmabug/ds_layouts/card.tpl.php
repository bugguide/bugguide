<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?> clearfix">

<div class="card h-100">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (!empty($header)): ?>
    <header class="card-header">
      <?php print $header; ?>
    </header>
  <?php endif; ?>

  <?php if (!empty($image)): ?>
    <header class="card-image">
      <figure class="image is-4by3">
        <?php print $image; ?>
      </figure>
    </header>
  <?php endif; ?>

  <?php if (!empty($body)): ?>
    <div class="card-content">
      <?php print $body; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($footer)): ?>
    <footer class="card-footer">
      <?php print $footer; ?>
    </footer>
  <?php endif; ?>

</div>
</<?php print $layout_wrapper ?>>
