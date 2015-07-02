	<script >
	/* Grid gutter fix for IE7 */ 
	(function(b){if((' '+b.body.parentNode.className+' ').indexOf(' lt-ie8 ')==-1)return;var d=b.createStyleSheet();var e=function(s){var a=b.all,l=[],i,j;d.addRule(s,'k:v');for(j=a.length;j--;)a[j].currentStyle.k&&l.push(a[j]);d.removeRule(0);return l};var g=e('.grid');for(var i=g.length;i--;)g[i].style.width=g[i].offsetWidth-20})(document);</script>



	<script >
	/* Responsive design */ 
	(function(f){if(!f.querySelector||!f.addEventListener)return;var g='add',cc='contains',cr='remove',ct='toggle',sa='active',sb='off-canvas-bar',sn='off-canvas-nav',ss='off-canvas-search',ed='preventDefault',q=function(a,b){return(b||f).querySelectorAll(a)},c=function(a,b,c){b=b||cr;c=c||f.body;a=' '+a+' ';var d=' '+c.className.trim()+' ';var e=d.indexOf(a)!=-1;if(b==cc)return e;else if(!e&&(b==ct||b==g))c.className=d+a;else if(e&&(b==ct||b==cr))c.className=d.replace(a,' ')},h=function(b,c,d){for(var e=q(b),i=e.length;i--;){if(e[i].tagName!='A'||e[i].getAttribute('href')=='#'){if(!d)e[i].addEventListener('click',function(a){a[ed]()},0);e[i].addEventListener('ontouchstart'in window?'touchstart':'mousedown',c,0)}}},m=q('.isu-dark-ribbon .wd-ribbon-menu-stack .wd-ribbon-menu'),md=function(){for(var i=m.length;i--;)c(sa,cr,m[i])};h('.isu-responsive-toggles .nav-toggle',function(a){md();c(sb);c(ss);c(sn,ct);a[ed]()});h('.isu-responsive-toggles .search-toggle',function(a){md();c(sb);c(ss,ct);c(sn);a[ed]()});h('.isu-dark-ribbon .wd-ribbon-menu-header',function(a){var b=q('.wd-ribbon-menu',this.parentNode)[0];if(c(sa,cc,b)){c(sa,cr,b);c(sb)}else{md();c(sa,g,b);c(sb,g);c(ss)}a[ed]()});h('.isu-content',function(a){if(c(sn,cc))a[ed]();c(sn)},true)})(document)</script>
