<?php
$myFile = "live/data.json";
include "includes/info.php";

if (array_key_exists($ip_address, $arr_data["names"]))
	header("location: live/");
?>

<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Home Page</title>
</head>
	
<body>
	
	<form action="live/" method="post">
		<label for="name">Name:</label>
		<input id="name" type="text" name="name"><br>
		<input name="submit" type="submit">
	</form>
	
</body>
</html>