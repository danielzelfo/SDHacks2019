<?php
if (!empty($_SERVER['HTTP_CLIENT_IP'])){
    $ip_address = $_SERVER['HTTP_CLIENT_IP'];
}elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR']))  {
    $ip_address = $_SERVER['HTTP_X_FORWARDED_FOR'];
}else{
    $ip_address = $_SERVER['REMOTE_ADDR'];
}


//Get data from existing json file

try {
	$jsondata = file_get_contents($myFile);

	// converts json data into array
	$arr_data = json_decode($jsondata, true);

} catch (Exception $e) {
	echo 'Caught exception: ', $e->getMessage(), "\n";
}

?>