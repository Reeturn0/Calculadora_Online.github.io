<?php

	require_once("index.html");
	
	
	$var_values = rtrim($_POST["ivar_values"], ',');
	
	
	$f = fopen("ivar_values.txt", 'w');
	fwrite($f, $var_values);
	fclose($f);
	
	
	system("c++_impl.exe");
	
	
	echo "
	<script>
	document.getElementById(\"ans\").scrollIntoView();
	</script>
	";
	
?>
