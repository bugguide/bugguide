<?php

// This script seeds initial nodes into a fresh BugGuide installation.
// BugGuide needs this because it is based on a tree structure. We initialize the
// following Guide Pages so we have a small tree; actually two trees.
//
// node/3 (Arthropoda)    no parent (top of tree)
//   node/4 (Chelicerata) parent: 3
//     node/5 (Arachnida) parent: 3,4
//
// node/6 (ID Request)    no parent (top of tree)

// Sanity check.
if (!drupal_is_cli()) {
  echo "Restricted to the command line.";
  exit();
}

// Node 1
$node = new stdClass();  // Create a new node object
$node->type = 'page';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

$node->title = 'About';
$node->body[$node->language][0]['value'] = "Are you fascinated, like us, by the intricate lives of insects and spiders?
Are you looking for information on an insect or spider that you found?
Do you enjoy sharing with others your knowledge of insects and spiders?
Do you have images of insects and spiders that you want to share with the world?

If any of those apply to you, you should feel right at home on this web site. If none of those apply, take a look around and you just might change your mind.

<B>Looking to identify something you found?</B>

If you are here to identify something you found, first visit <a href='node/view/5'>the guide</a>. If you don't find it there and you have an image of it, you may wish to register and request an identification by posting your image in the <a href='node/view/6/bgimage'>ID request</a> section.

<B>North American Focus</B>

This web site primarily covers bugs occurring in America North of Mexico. As most of us have resources limited to that part of the world, we cannot easily 'fact check' contributions for fauna outside that area. We would rather attempt to do a great job for our part of the world than do a mediocre job for the whole world. Any contributions for fauna outside of North America will probably be removed. We hope to expand BugGuide to other areas in the future.
 
<B>Want to help grow this website?</B>

No single person could possibly do justice to covering even a small fraction of all the insects and spiders. For this web site to be successful, we need your help, and there are many ways you can contribute.

After registering, you can help by submitting your comments. If you were left wondering why an obvious question you had was not answered, post a comment with your question in the appropriate section of the guide and contributors will try to provide the answer for future visitors. If you can expand the knowledgebase here by identifying specimens or by sharing observations or research, feel free to do so.

If you have images, particularly of things not already included in the guide, you may submit them for inclusion in the guide. Just register and add your image in the most appropriate section of the guide. This both benefits others who may be able to identify something from your image and provides exposure for your image. You decide how your image may be used, and you might even be contacted by someone interested in licensing your image.

<B>Why register?</B>

You are required to register in order to comment, participate in the forums, and to submit images, links, and books to the guide. Registration allows you to specify how your submitted content may be licensed and permits visitors to identify you and find out how you wish to be contacted about licensing of your submitted content (images in particular). Lastly, registering allows you to be notified by email whenever content you subscribe to changes. Cookies must be enabled in your web browser for login to work.

<B>Keeping up with changes to the guide</B>

If you are a frequent visitor, you might want to check out the <a href='node'>recent additions</a> to the guide. After registering, you may also manage subscriptions that will notify you by email whenever pages you are interested in change.

<B>Finally, why 'bugs'?</B>

Yes, we know. Not all insects are '<a href='/node/view/64'>true bugs</a>'. Spiders certainly are not. But consider the first definition of <a href='http://www.cogsci.princeton.edu/cgi-bin/webwn2.0?stage=1&amp;word=bug' target='blank'>bug</a> from <a href='http://www.cogsci.princeton.edu/~wn/' target='blank'>WordNet</a>:

1. bug -- general term for any insect or similar creeping or crawling invertebrate

We think you'll agree that insects, spiders, and other things you'll find on this web site fit that definition. Besides, BugGuide.Net is short and catchy!";

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 0;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

// Save the node
node_save($node);

// Node 2
$node = new stdClass();  // Create a new node object
$node->type = 'page';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

$node->title = 'Test page';
$node->body[$node->language][0]['value'] = 'Test page';

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 0;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

// Save the node
node_save($node);

// Node 3 - Base node of taxonomy tree
$node = new stdClass();  // Create a new node object
$node->type = 'bgpage';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

print_r($node);

$node->title = 'Arthropoda';
$node->body[$node->language][0]['value'] = 'The arthropoda.';
$node->field_common_name[$node->language][0]['value'] = 'Arthropods';
$node->field_scientific_name[$node->language][0]['value'] = 'Arthropoda';
$node->field_etymology[$node->language][0]['value'] = 'from the Greek [i]arthron[/i] (&alpha;&rho;&theta;&rho;&omicron;&nu;)- "joint" + [i]podos[/i] (&pi;&omicron;&delta;&omicron;&sigmaf;)- "of foot, leg"; refers to the jointed legs of all members in the phylum';
$node->field_counts[$node->language][0]['value'] = 'Worldwide:[Cite:1028573][cite:2524,546]
+15 classes';

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 1;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

$node->field_taxon[$node->language][0]['value'] = "1100";

// Save the node
node_save($node);
$node = node_load(3);
//print_r($node);

// Node 4 - Child of Arthropoda
$node = new stdClass();  // Create a new node object
$node->type = 'bgpage';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

$node->title = 'Chelicerata';
$node->body[$node->language][0]['value'] = 'The Chelicerata.';
$node->field_scientific_name[$node->language][0]['value'] = 'Chelicerata';

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 1;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

$node->field_taxon[$node->language][0]['value'] = "1200";
$node->field_parent[$node->language][0]['value'] = "3";
// Save the node
node_save($node);

// Node 5 - Child of Chelicerata
$node = new stdClass();  // Create a new node object
$node->type = 'bgpage';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

$node->title = 'Arachnida';
$node->body[$node->language][0]['value'] = 'The Arachnida.';
$node->field_scientific_name[$node->language][0]['value'] = 'Arachnida';
$node->field_common_name[$node->language][0]['value'] = 'Arachnids';

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 1;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

$node->field_taxon[$node->language][0]['value'] = "1400";
$node->field_parent[$node->language][0]['value'] = "3,4";
// Save the node
node_save($node);

// Node 6 - ID Request
$node = new stdClass();  // Create a new node object
$node->type = 'bgpage';  // Content type
$node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
node_object_prepare($node);  //Set some default values

$node->title = 'ID Request';
$node->body[$node->language][0]['value'] = '';

$node->status = 1;   // (1 or 0): published or unpublished
$node->promote = 0;  // (1 or 0): promoted to front page or not
$node->sticky = 0;  // (1 or 0): sticky at top of lists or not
$node->comment = 1;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
// Add author of the node
$node->uid = 1;

$node->field_taxon[$node->language][0]['value'] = "1400";
$node->field_parent[$node->language][0]['value'] = "";
// Save the node
node_save($node);
