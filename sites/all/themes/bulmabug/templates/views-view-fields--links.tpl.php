
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
      <?php print $fields['breadcrumbs']->content; ?>
    </div>
    <h2 class="bg-link_title title is-5 mb-2"><?php print $fields['title']->content; ?></h2>
    <div class="bg-link_body content">
      <?php print $fields['body']->content; ?>
    </div>
    <div class="bg-link_byline is-size-7">
      Contributed by <?php print $fields['name']->content; ?> on <?php print $fields['created']->content; ?>
    </div>

    <ul class="links inline flex-wrap">
      <li>
        <?php print $fields['view_node']->content; ?>
      </li>
      <li>
        <?php print $fields['field_bglink_link']->content; ?>
      </li>
      <?php if ((int) $fields['comment_count']->raw > 0): ?>
        <li>
          <?php print $fields['comment_count']->content; ?>
        </li>
      <?php endif; ?>
      <?php if ((int) $fields['new_comments']->raw > 0): ?>
        <li>
          <?php print $fields['new_comments']->content; ?>
        </li>
      <?php endif; ?>
      <li>
        <?php print $fields['comments_link']->content; ?>
      </li>
    </ul>
  </div>
</div>



