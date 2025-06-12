<?php
require_once 'Εισαγωγή_στην_ΒΔ.php';
// Form submitted correctly pressing submit button
	$lat = $_POST['lat'];
	$lng = $_POST['lng'];

	$sql="insert into vasi(x,y,time) values('$lat','$lng',now())";
	if ($conn->query($sql) === TRUE) {
	    echo "Coordinates saved successfully";
	} else {
	    echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();
?>
