
<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>

<div class="card mb-3">
  <div class="card-content p-3">
    <div class="bg-link_roots mb-3">
      <a href="https://bugguide.net/node/view/3/bglink" title="Phylum">Placeholder&nbsp;(Placeholder)</a> » <a href="https://bugguide.net/node/view/878075/bglink" title="Subphylum">Placeholder&nbsp;(Placeholder)</a> » <a href="https://bugguide.net/node/view/52/bglink" title="Class">Placeholder&nbsp;(Placeholder)</a> » <a href="https://bugguide.net/node/view/60/bglink" title="Order">Placeholder&nbsp;(Placeholder)</a>
    </div>
    <h2 class="bg-link_title title is-5 mb-2"><?php print $fields['title']->content; ?></h2> 
    <div class="bg-link_body content">
      <?php print $fields['body']->content; ?>
    </div>
    <div class="bg-link_byline is-size-7">
      Contributed by <?php print $fields['name']->content; ?> on <?php print $fields['created']->content; ?>
    </div>
    <div class="bg-link_links">
      <div class="bg-link_links_link">
        <?php print $fields['view_node']->content; ?>
      </div>
      <div class="bg-link_links_link">
        <?php print $fields['field_bglink_link']->content; ?>
      </div>
      <div class="bg-link_links_link">
        <?php print $fields['comments_link']->content; ?>
      </div>
    </div>
  </div>
</div>



