<?php

/**
 * Page callbacks for bgapi module.
 */

/**
 * Ask for something in the tree, get back a JSON array of the tree structure:
 * https://beta.bugguide.net/bgapitree/291325
 * {"Phylum":"Arthropoda","Subphylum":"Hexapoda","Class":"Insecta","Order":"Hymenoptera","No Taxon":"Subgenus Acanthomyops","Superfamily":"Formicoidea","Family":"Formicidae","Subfamily":"Formicinae","Tribe":"Lasiini","Genus":"Lasius","Species":"interjectus"}
 */
function bgapi_get_tree($id) {
  $nid = (int) $id;
  if (!$nid) {
    return;
  }

  $node = node_load($nid);

  $json = array(
    'self' => 'https://bugguide.net/node/view/' . $nid,
  );

  $tree = bg_create_taxonomic_breadcrumb($node, '', $guidebc = 'Scientific name (Common name)', NULL, $json = TRUE);

  if (!$tree) {
    $error = array(
      'errors' => array(
        'status' => '400',
        'title' => 'Resource not in a taxonomic tree',
        'detail' => 'The resource you requested does not have a taxonomic tree associated with it.',
      ),
    );
    drupal_add_http_header('status', '400 Resource not in a taxonomic tree');
    return drupal_json_output($error);
  }

  //{"data":[{"id":"60","self":"https:\/\/beta.bugguide.net\/api\/v1.0\/bgpage\/60","name":"Beetles","scientific_name":"Coleoptera"}],"self":{"title":"Self","href":"https:\/\/beta.bugguide.net\/api\/v1.0\/bgpage\/60"}}

  $response = array(
    'data' => array(
      'id' => $nid,
      'self' => 'https://bugguide.net/node/view/' . $nid,
      'tree' => $tree,
    ),
  );
  return drupal_json_output($response);
}

/**
 * Ask for something in the tree, get back a vocab file of the tree structure:
 * https://beta.bugguide.net/bgapitree/291325
 * {"Phylum":"Arthropoda","Subphylum":"Hexapoda","Class":"Insecta","Order":"Hymenoptera","No Taxon":"Subgenus Acanthomyops","Superfamily":"Formicoidea","Family":"Formicidae","Subfamily":"Formicinae","Tribe":"Lasiini","Genus":"Lasius","Species":"interjectus"}
 */
function bgapi_get_tree_vocab($id) {
  $nid = (int) $id;
  if (!$nid) {
    return;
  }

  $node = node_load($nid);

  $json = array(
    'self' => 'https://bugguide.net/node/view/' . $nid,
  );

  $tree = bg_create_taxonomic_breadcrumb($node, '', $guidebc = 'Scientific name (Common name)', NULL, $json = TRUE);
  $output = '';

  if (isset($tree['Species']) && isset($tree['Genus'])) {
    $tree['Species'] = $tree['Genus'] . ' ' . $tree['Species'];
  }
  foreach ($tree as $k => $v) {
    $output .= str_replace(' ', '-', $k) . '_' . str_replace(' ', '-', $v) . "\r";
  }

  drupal_add_http_header('Content-Type: text/ascii; utf-8');
  print $output;
  module_invoke_all('exit');
}
