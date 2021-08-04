<?php

/**
 * Page callbacks for the bglink module.
 */

/**
 * Redirects to a form to add a link for a bgpage.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bglink_add_link($nid) {
  drupal_goto('node/add/bglink/' . $nid);
}
