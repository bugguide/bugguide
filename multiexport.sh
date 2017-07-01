#!/bin/bash

# Runs export for each order.
# Export will be tab-delimited files with a header, like so:
#
# Genus	Species	Family	Order	BugGuideID	URL	Common Name
# Cryptocercus	punctulatus	Cryptocercidae	Blattodea	574	http://bugguide.net/node/view/574	Brown-hooded Cockroach

REMOTE_ADDR=127.0.0.1 TREETOP=57 HODGES=1 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Lepidoptera_hodges.txt
REMOTE_ADDR=127.0.0.1 TREETOP=79 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Zygentoma.txt
REMOTE_ADDR=127.0.0.1 TREETOP=55 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Diptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=56 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Mecoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=57 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Lepidoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=59 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Hymenoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=60 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Coleoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=61 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Neuroptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=63 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Hemiptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=67 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Psocodea.txt
REMOTE_ADDR=127.0.0.1 TREETOP=73 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Orthoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=74 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Phasmida.txt
REMOTE_ADDR=127.0.0.1 TREETOP=76 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Plecoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=77 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Odonata.txt
REMOTE_ADDR=127.0.0.1 TREETOP=78 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Ephemeroptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=80 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Microcoryphia.txt
REMOTE_ADDR=127.0.0.1 TREETOP=2709 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Dermaptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=5233 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Trichoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=7040 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Siphonaptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=7754 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Thysanoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=9667 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Strepsiptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=16969 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Embiidina.txt
REMOTE_ADDR=127.0.0.1 TREETOP=233428 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Megaloptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=41371 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Zoraptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=233370 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Raphidioptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=244862 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Notoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=317568 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Protorthoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=342386 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Blattodea.txt
REMOTE_ADDR=127.0.0.1 TREETOP=342391 php -f ./mpg_export.php > /var/www/html/beta.bugguide.net/bugguide/bgapi/taxonomy/Mantodea.txt
