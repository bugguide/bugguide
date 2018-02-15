<div class="megapanels" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
		
	<?php if (!empty($content['top_full'])): ?>
		<div class="megapanels-wrapper megapanels-wrapper_full_top">
			<div class="megapanels-full megapanels-full_top">
				<div class="megapanels-pane_full">
					<?php print $content['top_full']; ?>
				</div>
			</div>
		</div>
	<?php endif; ?>
	
	<div class="megapanels-wrapper megapanels-wrapper_top">
		<div class="megapanels-row megapanels-row_top">
			<?php if (!empty($content['top_grow_first'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_top_grow_first">
					<?php print $content['top_grow_first']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['top_1'])): ?>
				<div class="megapanels-pane megapanels-pane_top_1">
					<?php print $content['top_1']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['top_2'])): ?>
				<div class="megapanels-pane megapanels-pane_top_2">
					<?php print $content['top_2']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['top_3'])): ?>
				<div class="megapanels-pane megapanels-pane_top_3">
					<?php print $content['top_3']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['top_4'])): ?>
				<div class="megapanels-pane megapanels-pane_top_4">
					<?php print $content['top_4']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['top_grow_last'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_top_grow_last">
					<?php print $content['top_grow_last']; ?>
				</div>
			<?php endif; ?>
		</div>
	</div>

	<div class="megapanels-wrapper megapanels-wrapper_middle">
		<div class="megapanels-row megapanels-row_middle">
			<?php if (!empty($content['middle_grow_first'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_middle_grow_first">
					<?php print $content['middle_grow_first']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['middle_1'])): ?>
				<div class="megapanels-pane megapanels-pane_middle_1">
					<?php print $content['middle_1']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['middle_2'])): ?>
				<div class="megapanels-pane megapanels-pane_middle_2">
					<?php print $content['middle_2']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['middle_3'])): ?>
				<div class="megapanels-pane megapanels-pane_middle_3">
					<?php print $content['middle_3']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['middle_4'])): ?>
				<div class="megapanels-pane megapanels-pane_middle_4">
					<?php print $content['middle_4']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['middle_grow_last'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_middle_grow_last">
					<?php print $content['middle_grow_last']; ?>
				</div>
			<?php endif; ?>
		</div>
	</div>

	<div class="megapanels-wrapper megapanels-wrapper_bottom">
		<div class="megapanels-row megapanels-row_bottom">
			<?php if (!empty($content['bottom_grow_first'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_bottom_grow_first">
					<?php print $content['bottom_grow_first']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['bottom_1'])): ?>
				<div class="megapanels-pane megapanels-pane_bottom_1 ">
					<?php print $content['bottom_1']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['bottom_2'])): ?>
				<div class="megapanels-pane megapanels-pane_bottom_2 ">
					<?php print $content['bottom_2']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['bottom_3'])): ?>
				<div class="megapanels-pane megapanels-pane_bottom_3 ">
					<?php print $content['bottom_3']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['bottom_4'])): ?>
				<div class="megapanels-pane megapanels-pane_bottom_4 ">
					<?php print $content['bottom_4']; ?>
				</div>
			<?php endif; ?>

			<?php if (!empty($content['bottom_grow_last'])): ?>
				<div class="megapanels-pane megapanels-pane_grow megapanels-pane_bottom_grow_last">
					<?php print $content['bottom_grow_last']; ?>
				</div>
			<?php endif; ?>
		</div>
	</div>

	<?php if (!empty($content['bottom_full'])): ?>
		<div class="megapanels_wrapper">
			<div class="megapanels-full megapanels-full_bottom">
				<div class="megapanels-pane_full">
					<?php print $content['bottom_full']; ?>
				</div>
			</div>
		</div>
	<?php endif; ?>
		
</div>
