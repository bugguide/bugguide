<div class="content">
  <div class="bg-link_title-link">
    Visit: <a href="<?php print $variables['field_bglink_link'][0]['url']; ?>"><?php print $variables['field_bglink_link'][0]['url']; ?></a>
  </div>

  <?php print render($content['body']); ?>

</div>

<div class="node-authoring-data">
  <div class="bg-link_byline is-size-7">
    <span>Contributed by </span><?php print render($content['author']); ?><span> on </span><?php print render($content['post_date']); ?>
  </div>
  <div class="bg-link_updated is-size-7">
    <span>Last updated </span><?php print render($content['changed_date']); ?>
  </div>
</div>

<?php print render($content['field_tags']); ?>

<?php print render($content['bgsubscriptions_subscriptions']); ?>

<?php print render($content['comments']); ?>
