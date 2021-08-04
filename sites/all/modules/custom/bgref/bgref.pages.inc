<?php

/**
 * Page callbacks for the bgref module.
 */

/**
 * Redirects to a form to add a book reference for a bgpage.
 *
 * @param int $nid
 *   The nid of the bgpage node.
 */
function bgref_add_ref($nid) {
  drupal_goto('node/add/book-reference/' . $nid);
}
