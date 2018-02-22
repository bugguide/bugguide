<?php

/**
 * Sets the position of the forum link after frass.
 */

$frass_menu_id = db_query('SELECT mlid
  FROM {menu_links}
  WHERE link_path = :path', array(':path' => 'node/9410/bgimage'))->fetchField();

$forum_menu_id = db_query('SELECT mlid
  FROM {menu_links}
  WHERE link_path = :path', array(':path' => 'forum'))->fetchField();

$frass_menu = menu_link_load($frass_menu_id);
$forum_menu = menu_link_load($forum_menu_id);

$forum_menu['weight'] = $frass_menu['weight'] + 1;
menu_link_save($forum_menu);
