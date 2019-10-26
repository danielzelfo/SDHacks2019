<?php
$myFile = "data.json";

include "../includes/info.php";


if(isset($_POST["submit"])) {
	
	
	$names = array(
		$ip_address => $_POST["name"]
	);

	//Get form data



	// Push user data to array
	$names = array_merge($arr_data["names"], $names);



	$formdata = array(
		"names" => $names
	);


	//Convert updated array to JSON
	$jsondata = json_encode($formdata, JSON_PRETTY_PRINT);

	//write json data into data.json file
	file_put_contents($myFile, $jsondata);

	$userName = $_POST["name"];
	
} else {
	if (array_key_exists($ip_address, $arr_data["names"]))
		$userName = $arr_data["names"][$ip_address];
	else
		header("location: ../");
}



echo "hello ".$userName;


?>



