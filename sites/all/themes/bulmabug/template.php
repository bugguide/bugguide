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
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $lastitem = sizeof($breadcrumb);
    $currentpage = drupal_get_title();
    $output .= '<ul>';
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
    //$output .='<li class="is-active"><a href="">'. $currentpage .'</a></li>';
    $output .= '</ul>';
    return $output;
  }
}

