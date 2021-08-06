<div class="content">
	<div class="bg-link_title-link">
		Visit: <a href="<?php print render($content['field_bg_link']); ?>"><?php print $title ?></a>
	</div>
	<?php print render($content['body']); ?>
</div>

<div class="bg-link_byline is-size-7">
  <span>Contributed by </span><?php print render($content['author']); ?><span> on </span><?php print render($content['post_date']); ?>
</div>
<div class="bg-link_updated is-size-7">
	<span>Last updated </span><?php print render($content['changed_date']); ?>
</div>

<?php print render($content['node_links']); ?>
<?php print $node_links; ?>

<?php print render($content['comments']); ?>

<details><pre><?php print_r($content); ?></pre></details>