<?php

/**
 * Return a prefix for directory creation. Given an md5
 * like ab8ef7... it returns ab8/ef7/
 *
 * @param string $s
 * @return string
 */
function bgimage_get_prefix($s) {
  return substr($s, 0, 3) . '/' . substr($s, 3, 3) . '/';
}

function char_to_base36($char) {
	$base36_charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	$decimal = ord($char);
	$remainder = ($decimal % 36);
	$decimal   = ($decimal - $remainder) / 36; 
	return substr($base36_charset, $decimal, 1) . 
		substr($base36_charset, $remainder, 1);
}

function base36_to_char($string) { 
	$base36_charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	return chr((strpos($base36_charset, substr($string, 0, 1)) * 36) +
		strpos($base36_charset, substr($string, 1, 1)));
}

function base36_encode($string) {
	$len = strlen($string);
        $base36 = '';
	for ($i = 0; $i < $len; $i++) {
		$base36 .= char_to_base36(substr($string, $i, 1));
	}
	return $base36;
}

function base36_decode($base36) {
	$len = strlen($base36);
        $string = '';
	for ($i = 0; $i < $len; $i += 2) {
		$string .= base36_to_char(substr($base36, $i, 2));
	}
	return $string;
}

function image_obfuscate($s) {
	$base36_charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	$base36_map     = "6PJYFCIBDMQRUVHZE28X409KTG537SNOLAW1";
	$xor = chr(crc32($s) % 256);
	$s = $xor . $s;
	for ($i = 1; $i < strlen($s); $i++)
		$xor .= chr(ord(substr($s, $i, 1)) ^ ord(substr($xor, $i - 1, 1)));
	$s = base36_encode($xor);
	$s = strrev(strtr($s, $base36_map, $base36_charset));
	return $s;
}

function image_deobfuscate($s) {
	$base36_charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	$base36_map     = "6PJYFCIBDMQRUVHZE28X409KTG537SNOLAW1";
	$s = strrev(strtr($s, $base36_charset, $base36_map));
	$s = base36_decode($s);
        $xor = '';
	for ($i = 1; $i < strlen($s); $i++)
		$xor .= chr(ord(substr($s, $i, 1)) ^ ord(substr($s, $i - 1, 1)));
	return $xor;
}
