<?php

// Form submitted correctly pressing submit button
if (isset($_POST['submit'])) {

	$username = $_POST['username'];
	$password = $_POST['password'];
$carname = $_POST['car_name'];
// Error handling in signup form

require_once 'Εισαγωγή_στην_ΒΔ.php';
if (empty($username) || empty($password) || empty($carname))
{
	echo "not all data has been recorded";
}
else {
	$sql="insert into rescuer(username,password,car_name) values('$username','$password','$carname')";
	if (mysqli_query($conn, $sql))
	{
			echo "<script>
	    alert('New record created successfully');
			window.location.href = 'Δημιουργία_λογαριασμού_διασώστη.php';</script>";
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
