<?php

/**
 * Implements hook_preprocess_html().
 *
 * Backports the following changes made to Drupal 8:
 * - #1077566: Convert html.tpl.php to HTML5.
 */

function bulma_preprocess_html(&$variables) {
  // Initializes attributes which are specific to the html and body elements.
  $variables['html_attributes_array'] = array();
  $variables['body_attributes_array'] = array();

  // HTML element attributes.
  $variables['html_attributes_array']['lang'] = $GLOBALS['language']->language;
  $variables['html_attributes_array']['dir'] = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

  // Update RDF Namespacing.
  if (module_exists('rdf')) {
    // Adds RDF namespace prefix bindings in the form of an RDFa 1.1 prefix
    // attribute inside the html element.
    $prefixes = array();
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $vars['html_attributes_array']['prefix'][] = $prefix . ': ' . $uri . "\n";
    }
  }

  // Add viewport meta tag.
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
    ),
  );
  drupal_add_html_head($viewport, 'viewport');

  // Add FontAwesome
  drupal_add_css('https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css', array('type' => 'external'));
}

function bulma_css_alter(&$css) {
  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.theme.css']);
}

function bulma_preprocess_page(&$vars) {
  $vars['container_width_navbar'] = theme_get_setting('container_width_navbar');
  $vars['container_width_content'] = theme_get_setting('container_width_content');
  $vars['container_width_footer'] = theme_get_setting('container_width_footer');

  $vars['navbar1_classes'] = theme_get_setting('navbar1_classes');
  $vars['navbar2_classes'] = theme_get_setting('navbar2_classes');

  $vars['breadcrumb_classes'] = theme_get_setting('breadcrumb_classes');

  $vars['tabs_primary_classes'] = theme_get_setting('tabs_primary_classes');

  // Menu?
  $main_menu = menu_tree_output(menu_tree_all_data(variable_get('menu_main_links_source', 'main-menu'), NULL, 2));

  // Custom wrapper for 1st menu level.
  $main_menu['#theme_wrappers'] = array('menu_tree__main_menu_primary');

  $vars['page']['main_menu'] = $main_menu;
}

function bulma_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $lastitem = sizeof($breadcrumb);
    $currentpage = drupal_get_title();
    $output .= '<nav aria-label="Breadcrumb"><ol>';
    $i = 1;
    foreach ($breadcrumb as $value) {
      if ($i != $lastitem) {
        $output .= '<li>'. $value . '</li>';
        $i++;
      }
      else {
        $output .= '<li class="breadcrumb-last">'. $value .'</li>';
      }
    }
    $output .='<li class="is-active"><a aria-current="page" href="">'. $currentpage .'</a></li>';
    $output .= '</ol></nav>';
    return $output;
  }
}

function bulma_menu_tree__main_menu_primary($variables) {
  return '<ul class="navbar-links">' . $variables['tree'] . '</ul>';
}

function bulma_menu_tree__main_menu($variables) {
  return '<ul>' . $variables['tree'] . '</ul>';
}

function bulma_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'user_login':
    case 'user_login_block':
      
      $form['#attributes']['class'][] = 'card';

      $form['name']['#attributes']['class'][] = 'input mb-3';
      $form['name']['#attributes']['placeholder'] = t('Login');
      $form['name']['#description'] = NULL;
      $form['name']['#prefix'] = '<div class="card-content">';
      $form['pass']['#attributes']['placeholder'] = t('Password');
      $form['pass']['#description'] = NULL;
      $form['pass']['#attributes']['class'][] = 'input mb-3';

      $form['links'] = NULL;

      $form['actions']['#attributes']['class'][] = '';
      $form['actions']['submit']['#attributes']['class'][] = 'button is-primary mr-1';
      $form['actions']['register']['#markup'] = '<a class="button mr-1" href="/user/register">' . t('Register') . '</a>';
      $form['actions']['request_pass']['#markup'] = '<div></div><a class="button is-text" href="/user/password">' . t('Request new password') . '</a>';
      $form['actions']['#suffix'] = '</div>';
      break;

    case 'user_pass':
      $form['#attributes']['class'][] = 'card card-form';
      $form['user_icon']['#markup'] = '<div class="user-icon text-align-center"><i class="material-icons text-disabled">vpn_key</i></div>';
      $form['user_icon']['#weight'] = -15;
      $form['name']['#title'] = NULL;
      $form['name']['#attributes']['placeholder'] = t('Login or E-mail');
      $form['actions']['#attributes']['class'][] = 'card-item card-actions divider-top';
      $form['actions']['submit']['#attributes']['class'][] = 'btn-accent';
      break;

    case 'user_register_form':
      $form['#attributes']['class'][] = 'card card-form';
      $form['user_icon']['#markup'] = '<div class="user-icon text-align-center"><i class="material-icons text-disabled">account_circle</i></div>';
      $form['user_icon']['#weight'] = -15;
      $form['account']['name']['#title'] = NULL;
      $form['account']['name']['#attributes']['placeholder'] = t('Login');
      $form['account']['mail']['#title'] = NULL;
      $form['account']['mail']['#attributes']['placeholder'] = t('E-mail');
      $form['actions']['#attributes']['class'][] = 'card-item card-actions divider-top';
      $form['actions']['submit']['#attributes']['class'][] = 'btn-accent';
      break;

    case 'search_block_form':
      $form['search_block_form']['#attributes']['placeholder'] = t('Search');
      $form['search_block_form']['#attributes']['class'][] = 'input is-auto';
      $form['actions']['submit']['#attributes']['class'][] = 'button is-primary';
      break;
  }
}

function bulma_menu_local_tasks(&$variables) {
  $output = '';
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="primary">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}
