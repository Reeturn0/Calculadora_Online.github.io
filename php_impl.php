<?php
	include("index.html");
	$expr = $_POST["iexpr"];
	
	system("c++_impl.exe $expr");

	echo "
	<script>
	document.getElementById(\"ans\").scrollIntoView();
	</script>
	";
?>

