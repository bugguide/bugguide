<?php

/**
 * Script to rebuild data for forum topics in forum_index.
 *
 * @see forum_update_7001().
 *
 * @see bugguide_migration's migrateto7.
 */
 
$select = db_select('node', 'n');
$forum_alias = $select
  ->join('forum', 'f', 'n.vid = f.vid');
$ncs_alias = $select
  ->join('node_comment_statistics', 'ncs', 'n.nid = ncs.nid');
$select
  ->fields('n', array(
  'nid',
  'title',
  'sticky',
  'created',
))
  ->fields($forum_alias, array(
  'tid',
))
  ->fields($ncs_alias, array(
  'last_comment_timestamp',
  'comment_count',
));
db_insert('forum_index')
  ->fields(array(
  'nid',
  'title',
  'sticky',
  'created',
  'tid',
  'last_comment_timestamp',
  'comment_count',
))
  ->from($select)
  ->execute();

// forum_update_7011()
$select = db_select('node', 'n')
    ->fields('n', array(
    'nid',
  ))
    ->condition('status', 0);
  db_delete('forum_index')
    ->condition('nid', $select, 'IN')
    ->execute();