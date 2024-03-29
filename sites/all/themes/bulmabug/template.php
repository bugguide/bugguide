<?php

// Make database name available so we can display it in footer during beta.
// TODO remove this in production.
function bulmabug_preprocess_page(&$vars) {
  $vars['current_database'] = $GLOBALS['databases']['default']['default']['database'];
}

/**
 * Implements theme_breadcrumb().
 *
 * From bulmabug base theme, but does not append current page title because the
 * current page title is often a wrong guess on what the specimen is.
 */
function bulmabug_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $lastitem = sizeof($breadcrumb);
    $currentpage = drupal_get_title();
    $output = '<nav aria-label="Breadcrumb"><ol>';
    $i = 1;
    foreach ($breadcrumb as $value) {
      if ($i != $lastitem){
        $output .= '<li>'. $value . '</li>';
        $i++;
      }
      else {
        $output .= '<li class="breadcrumb-last">'. $value .'</li>';
      }
    }
    //$output .='<li class="is-active"><a aria-current="page" href="">'. $currentpage .'</a></li>';
    $output .= '</ol></nav>';
    return $output;
  }
}

/**
 * Implements THEME_preprocess_views_view_table().
 *
 * Automatically add bulma CSS framework classes to all Views tables formats.
 */
function bulmabug_preprocess_views_view_table(&$vars) {
  $vars['classes_array'][] = 'table is-narrow is-striped is-fullwidth';
}

/**
 * Implements THEME_preprocess_comment().
 *
 * Override "Submitted by" to be "-Jane Doe, 12 June 2018 - 02:14 am"
 */
function bulmabug_preprocess_comment(&$variables) {
    $variables['submitted'] = '&ndash;&nbsp;' . t('!username, !datetime', array('!username' => $variables['author'], '!datetime' => format_date(strtotime($variables['created']), 'custom', 'j F, Y  -  h:i a')));
}

/**
 * Implements hook_preprocess_HOOK.
 */
function bulmabug_preprocess_item_list(&$vars) {
  if (!isset($vars['attributes']['class']) || !in_array('pager', $vars['attributes']['class']) || !isset($vars['items'])) {
    return;
  }

  // Replace the default pager link titles with hints that users can use their
  // keyboard to go to the previous or next page.
  foreach ($vars['items'] as &$item) {
    if (isset($item['class']) && in_array('pager-previous', $item['class'])) {
      $item['data'] = str_replace('Go to previous page', 'Go to previous page (or use your left-arrow key)', $item['data']);
      continue;
    }
    if (isset($item['class']) && in_array('pager-next', $item['class'])) {
      $item['data'] = str_replace('Go to next page', 'Go to next page (or use your right-arrow key)', $item['data']);
      continue;
    }
  }

  // Add a key event listener so users can use left and right arrows to navigate pagers.
  $event_listener = <<<'EOD'
      document.addEventListener("keyup", function(e) {
        // Ignore modifier keys.
        if (e.altKey || e.shiftKey || e.ctrlKey || e.metaKey) return;
        if (e.which == 37) {
          prev = document.querySelector(".pager>.pager-previous>a");
          if (prev) prev.click();
        } else if (e.which == 39) {
          next = document.querySelector(".pager>.pager-next>a");
          if (next) next.click();
        }
      });
EOD;

  drupal_add_js($event_listener, array(
      'type' => 'inline',
      'scope' => 'footer',
      'weight' => 0,
    ));
}
