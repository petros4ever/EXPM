<?php

// Form submitted correctly pressing submit button
if (isset($_POST['submit'])) {

	$username = $_POST['username'];
	$password = $_POST['password'];
	$name = $_POST['name'];
	$telephone=$_POST["telephone"];
	$x=$_POST["x"];
	$y=$_POST["y"];

// Error handling in signup form

require_once 'Εισαγωγή_στην_ΒΔ.php';
if (empty($username) || empty($password) || empty($name) || empty($telephone) || empty($x)|| empty($y))
{
	echo "not all data has been recorded";
}
else {
	$sql="insert into civ(username,password,name,telephone,x,y) values('$username','$password','$name','$telephone','$x','$y')";
	if (mysqli_query($conn, $sql))
	{
		echo "<script>
    alert('New record created successfully');
		window.location.href = 'Αρχική_πολίτη.php';</script>";
			exit();
	}
	else
			{
						echo "Error: " . $sql . "<br>" . mysqli_error($conn);
			 }
}

	}
mysqli_close($conn);
?>
