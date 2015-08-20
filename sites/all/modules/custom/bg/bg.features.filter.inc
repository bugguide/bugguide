<?php
/**
 * @file
 * bg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function bg_filter_default_formats() {
  $formats = array();

  // Exported format: Filtered HTML.
  $formats[1] = array(
    'format' => 1,
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'bg_cite' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'bg_list' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'xbbcode' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'autoclose' => 0,
          'override' => 0,
          'tags' => array(
            '_enabled' => array(
              'abbr' => 'abbr',
              'acronym' => 'acronym',
              'b' => 'b',
              'center' => 'center',
              'code' => 'code',
              'color' => 'color',
              'define' => 'define',
              'font' => 'font',
              'h1' => 'h1',
              'h2' => 'h2',
              'h3' => 'h3',
              'h4' => 'h4',
              'h5' => 'h5',
              'h6' => 'h6',
              'hr' => 'hr',
              'i' => 'i',
              'img' => 'img',
              'justify' => 'justify',
              'left' => 'left',
              'list' => 'list',
              'node' => 'node',
              'php' => 'php',
              'quote' => 'quote',
              'right' => 'right',
              's' => 's',
              'size' => 'size',
              'sub' => 'sub',
              'sup' => 'sup',
              'u' => 'u',
              'url' => 'url',
              'wikipedia' => 'wikipedia',
              'youtube' => 'youtube',
            ),
            'abbr' => array(
              'module' => 'xbbcode_basic',
            ),
            'acronym' => array(
              'module' => 'xbbcode_basic',
            ),
            'b' => array(
              'module' => 'xbbcode_basic',
            ),
            'center' => array(
              'module' => 'xbbcode_basic',
            ),
            'code' => array(
              'module' => 'xbbcode_basic',
            ),
            'color' => array(
              'module' => 'xbbcode_basic',
            ),
            'define' => array(
              'module' => 'xbbcode_basic',
            ),
            'font' => array(
              'module' => 'xbbcode_basic',
            ),
            'h1' => array(
              'module' => 'xbbcode_basic',
            ),
            'h2' => array(
              'module' => 'xbbcode_basic',
            ),
            'h3' => array(
              'module' => 'xbbcode_basic',
            ),
            'h4' => array(
              'module' => 'xbbcode_basic',
            ),
            'h5' => array(
              'module' => 'xbbcode_basic',
            ),
            'h6' => array(
              'module' => 'xbbcode_basic',
            ),
            'hr' => array(
              'module' => 'xbbcode_basic',
            ),
            'i' => array(
              'module' => 'xbbcode_basic',
            ),
            'img' => array(
              'module' => 'xbbcode_basic',
            ),
            'justify' => array(
              'module' => 'xbbcode_basic',
            ),
            'left' => array(
              'module' => 'xbbcode_basic',
            ),
            'list' => array(
              'module' => 'xbbcode_basic',
            ),
            'node' => array(
              'module' => 'xbbcode_basic',
            ),
            'php' => array(
              'module' => 'xbbcode_basic',
            ),
            'quote' => array(
              'module' => 'xbbcode_basic',
            ),
            'right' => array(
              'module' => 'xbbcode_basic',
            ),
            's' => array(
              'module' => 'xbbcode_basic',
            ),
            'size' => array(
              'module' => 'xbbcode_basic',
            ),
            'sub' => array(
              'module' => 'xbbcode_basic',
            ),
            'sup' => array(
              'module' => 'xbbcode_basic',
            ),
            'u' => array(
              'module' => 'xbbcode_basic',
            ),
            'url' => array(
              'module' => 'xbbcode_basic',
            ),
            'wikipedia' => array(
              'module' => 'xbbcode_basic',
            ),
            'youtube' => array(
              'module' => 'xbbcode_basic',
            ),
          ),
        ),
      ),
      'filter_html' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <br> <em> <strong> <cite> <code> <ul> <ol> <li> <div> <dl> <dt> <dd> <b> <i> <p> <span> <strike> <img>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: BBCode.
  $formats['xbbcode'] = array(
    'format' => 'xbbcode',
    'name' => 'BBCode',
    'cache' => 1,
    'status' => 1,
    'weight' => -6,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'xbbcode' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'autoclose' => FALSE,
          'override' => FALSE,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
