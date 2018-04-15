<?php
	//include("index.html");
	$expr = $_GET["iexpr"];
	system("c++_impl.exe $expr");
	echo "
	<script type = \"text/javascript\">
	document.getElementById(\"ans\").scrollIntoView();
	</script>
	";
?>
