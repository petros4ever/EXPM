<?php
session_start();
require_once 'Εισαγωγή_στην_ΒΔ.php';
// Form submitted correctly pressing submit button
$name=$_SESSION["username"];
	$lat = $_POST['lat'];
	$lng = $_POST['lng'];

	$sql="update rescuer set x=$lat ,y=$lng,time=now() where username='$name'";
	if ($conn->query($sql) === TRUE) {
	    echo "Coordinates saved successfully";
	} else {
	    echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();
?>
