<?php

	require_once("index.html");

	
	$expr = $_POST["iexpr"];
	
	
	$f = fopen("itrig_mode.txt", 'w');
	fwrite($f, $_POST["itrig_mode"]);
	fclose($f);
	
	
	$f = fopen("iexpr.txt", 'w');
	fwrite($f, $expr);
	fclose($f);
	
	
	$var_names = shell_exec("get_var_names.exe $expr");
	
	
	if (!strlen($var_names))
	{
		require_once('numeric_impl.php');
	}
	
	else
	{
		$f = fopen("ivar_names.txt", 'w');
		fwrite($f, $var_names);
		fclose($f);
		
		
		$variables_arr = str_getcsv($var_names);
		
		
		// Prompt function
		function prompt_variables($prompt_msg)
		{
			echo("
			<script>
			var answer = prompt('" . $prompt_msg . " :='); 
			(document.getElementById('_ivar_values')).value += answer + ',';
			</script>");
		}
		
		
		foreach ( $variables_arr as  $varname )
		{
			prompt_variables($varname);
		}
		
		
		echo("
		<script>
		(document.getElementById('_submit_var_values')).click();
		</script>");
	}
?>
