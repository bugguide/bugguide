<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?> clearfix">
<div class="box mb-2">
  <div class="media">

    <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
    <?php endif; ?>

    <?php if (!empty($left)): ?>
      <div class="media-left">
        <?php print $left; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($body)): ?>
      <div class="media-content">
        <?php print $body; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($right)): ?>
      <div class="media-right">
        <?php print $right; ?>
      </div>
    <?php endif; ?>

  </div>
</div>
</<?php print $layout_wrapper ?>>

