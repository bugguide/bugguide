<?php

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