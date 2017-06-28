#!/bin/bash

# Runs export for each order.
# Export will be tab-delimited files with a header, like so:
#
# Genus	Species	Family	Order	BugGuideID	URL	Common Name
# Cryptocercus	punctulatus	Cryptocercidae	Blattodea	574	http://bugguide.net/node/view/574	Brown-hooded Cockroach

REMOTE_ADDR=127.0.0.1 TREETOP=79 php -f ./mpg_export.php > Zygentoma.txt
REMOTE_ADDR=127.0.0.1 TREETOP=55 php -f ./mpg_export.php > Diptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=56 php -f ./mpg_export.php > Mecoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=57 php -f ./mpg_export.php > Lepidoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=59 php -f ./mpg_export.php > Hymenoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=60 php -f ./mpg_export.php > Coleoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=61 php -f ./mpg_export.php > Neuroptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=63 php -f ./mpg_export.php > Hemiptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=67 php -f ./mpg_export.php > Psocodea.txt
REMOTE_ADDR=127.0.0.1 TREETOP=73 php -f ./mpg_export.php > Orthoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=74 php -f ./mpg_export.php > Phasmida.txt
REMOTE_ADDR=127.0.0.1 TREETOP=76 php -f ./mpg_export.php > Plecoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=77 php -f ./mpg_export.php > Odonata.txt
REMOTE_ADDR=127.0.0.1 TREETOP=78 php -f ./mpg_export.php > Ephemeroptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=80 php -f ./mpg_export.php > Microcoryphia.txt
REMOTE_ADDR=127.0.0.1 TREETOP=2709 php -f ./mpg_export.php > Dermaptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=5233 php -f ./mpg_export.php > Trichoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=7040 php -f ./mpg_export.php > Siphonaptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=7754 php -f ./mpg_export.php > Thysanoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=9667 php -f ./mpg_export.php > Strepsiptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=16969 php -f ./mpg_export.php > Embiidina.txt
REMOTE_ADDR=127.0.0.1 TREETOP=233428 php -f ./mpg_export.php > Megaloptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=41371 php -f ./mpg_export.php > Zoraptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=233370 php -f ./mpg_export.php > Raphidioptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=244862 php -f ./mpg_export.php > Notoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=317568 php -f ./mpg_export.php > Protorthoptera.txt
REMOTE_ADDR=127.0.0.1 TREETOP=342386 php -f ./mpg_export.php > Blattodea.txt
REMOTE_ADDR=127.0.0.1 TREETOP=342391 php -f ./mpg_export.php > Mantodea.txt
