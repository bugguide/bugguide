<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?> clearfix">

<div class="megapanels" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
    
  <?php if (!empty($top_full)): ?>
    <div class="megapanels-wrapper megapanels-wrapper_full_top">
      <div class="megapanels-full megapanels-full_top">
        <div class="megapanels-pane_full">
          <?php print $top_full; ?>
        </div>
      </div>
    </div>
  <?php endif; ?>
  
  <div class="megapanels-wrapper megapanels-wrapper_top">
    <div class="megapanels-row megapanels-row_top">
      <?php if (!empty($top_grow_first)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_top_grow_first">
          <?php print $top_grow_first; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($top_1)): ?>
        <div class="megapanels-pane megapanels-pane_top_1">
          <?php print $top_1; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($top_2)): ?>
        <div class="megapanels-pane megapanels-pane_top_2">
          <?php print $top_2; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($top_3)): ?>
        <div class="megapanels-pane megapanels-pane_top_3">
          <?php print $top_3; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($top_4)): ?>
        <div class="megapanels-pane megapanels-pane_top_4">
          <?php print $top_4; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($top_grow_last)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_top_grow_last">
          <?php print $top_grow_last; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>

  <div class="megapanels-wrapper megapanels-wrapper_middle">
    <div class="megapanels-row megapanels-row_middle">
      <?php if (!empty($middle_grow_first)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_middle_grow_first">
          <?php print $middle_grow_first; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($middle_1)): ?>
        <div class="megapanels-pane megapanels-pane_middle_1">
          <?php print $middle_1; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($middle_2)): ?>
        <div class="megapanels-pane megapanels-pane_middle_2">
          <?php print $middle_2; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($middle_3)): ?>
        <div class="megapanels-pane megapanels-pane_middle_3">
          <?php print $middle_3; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($middle_4)): ?>
        <div class="megapanels-pane megapanels-pane_middle_4">
          <?php print $middle_4; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($middle_grow_last)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_middle_grow_last">
          <?php print $middle_grow_last; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>

  <div class="megapanels-wrapper megapanels-wrapper_bottom">
    <div class="megapanels-row megapanels-row_bottom">
      <?php if (!empty($bottom_grow_first)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_bottom_grow_first">
          <?php print $bottom_grow_first; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($bottom_1)): ?>
        <div class="megapanels-pane megapanels-pane_bottom_1 ">
          <?php print $bottom_1; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($bottom_2)): ?>
        <div class="megapanels-pane megapanels-pane_bottom_2 ">
          <?php print $bottom_2; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($bottom_3)): ?>
        <div class="megapanels-pane megapanels-pane_bottom_3 ">
          <?php print $bottom_3; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($bottom_4)): ?>
        <div class="megapanels-pane megapanels-pane_bottom_4 ">
          <?php print $bottom_4; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($bottom_grow_last)): ?>
        <div class="megapanels-pane megapanels-pane_grow megapanels-pane_bottom_grow_last">
          <?php print $bottom_grow_last; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>

  <?php if (!empty($bottom_full)): ?>
    <div class="megapanels_wrapper">
      <div class="megapanels-full megapanels-full_bottom">
        <div class="megapanels-pane_full">
          <?php print $bottom_full; ?>
        </div>
      </div>
    </div>
  <?php endif; ?>
    
</div>




