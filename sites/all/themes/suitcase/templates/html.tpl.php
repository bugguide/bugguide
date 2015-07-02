<?php print $doctype; ?>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf->version . $rdf->namespaces; ?>>
<head<?php print $rdf->profile; ?>>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>  
  <?php print $styles; ?>
  <?php print $scripts; ?>
<!--  [if lt IE 9]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
<!--  <script >/* html5shiv */ (function(){var t='abbr article aside audio bdi canvas data datalist details figcaption figure footer header hgroup mark meter nav output progress section summary time video'.split(' ');for(var i=t.length;i--;)document.createElement(t[i])})();</script>-->
</head>
<body<?php print $attributes;?>>
	<!--[if lt IE 9]><div class="iecomp"><![endif]-->
  		<?php print $page_top; ?>
  		<?php print $page; ?>
  		<?php print $page_bottom; ?>
	<!--[if lt IE 9]></div><![endif]-->
</body>
</html>