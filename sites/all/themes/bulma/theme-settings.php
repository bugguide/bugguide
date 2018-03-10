<?php
/**
 * Implements hook_form_system_theme_settings_alter()
 */
function bulma_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['bulma_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulma Theme Settings'),
    '#description' => t('Theme options for the bulma base theme'),
    );

  $form['bulma_settings']['container_width_navbar'] = array(
    '#type'          => 'select',
    '#title'         => t('Navbar Container Width'),
    '#options' => array(
      0 => t('Fixed'),
      1 => t('Fluid'),
      ),
    '#default_value' => theme_get_setting('container_width_navbar'),
    );

  $form['bulma_settings']['container_width_content'] = array(
    '#type'          => 'select',
    '#title'         => t('Content Container Width'),
    '#options' => array(
      0 => t('Fixed'),
      1 => t('Fluid'),
      ),
    '#default_value' => theme_get_setting('container_width_content'),
    );

  $form['bulma_settings']['container_width_footer'] = array(
    '#type'          => 'select',
    '#title'         => t('Footer Container Width'),
    '#options' => array(
      0 => t('Fixed'),
      1 => t('Fluid'),
      ),
    '#default_value' => theme_get_setting('container_width_footer'),
    );

  $form['bulma_settings']['divider'] = array(
    '#markup' => '<hr>'
    );

  $form['bulma_settings']['navbar1_classes'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Navbar 1 classes'),
    '#description'    => t('Additional classes for Navbar 1. See <a href="https://bulma.io/documentation/components/navbar/">bulma.io documentation</a>.'),
    '#default_value' => theme_get_setting('navbar1_classes'),
    );

  $form['bulma_settings']['navbar2_classes'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Navbar 2 classes'),
    '#description'    => t('Additional classes for Navbar 2. See <a href="https://bulma.io/documentation/components/navbar/">bulma.io documentation</a>.'),
    '#default_value' => theme_get_setting('navbar2_classes'),
    );

  $form['bulma_settings']['breadcrumb_classes'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Breadcrumb classes'),
    '#description'    => t('Additional classes for breadcrumbs. See <a href="https://bulma.io/documentation/components/breadcrumb/">bulma.io documentation</a>.'),
    '#default_value' => theme_get_setting('breadcrumb_classes'),
    );

  $form['bulma_settings']['divider'] = array(
    '#markup' => '<hr>',
    );

  $form['bulma_settings']['tabs_primary_classes'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Primary tabs classes'),
    '#description'    => t('Additional classes for primary tabs. See <a href="https://bulma.io/documentation/components/navbar/">bulma.io documentation</a>.'),
    '#default_value' => theme_get_setting('tabs_primary_classes'),
    );
}
