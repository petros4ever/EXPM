<?php

// Form submitted correctly pressing login button
if (isset($_POST["submit"])) {


	$username = $_POST["username"];
	$password = $_POST["password"];

	require_once 'Εισαγωγή_στην_ΒΔ.php';
// Error handling in login form

	if (empty($username) || empty($password))
	{
		echo "not all data has been inserted!";
		exit();
	}
	$sql="SELECT username FROM admin WHERE username=? and password=?";
	$stmt = mysqli_prepare($conn, $sql);

    if ($stmt === false) {
        die("Σφάλμα προετοιμασίας εντολής: " . mysqli_error($conn));
    }

    mysqli_stmt_bind_param($stmt, "ss", $username,$password);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_store_result($stmt);

    if (mysqli_stmt_num_rows($stmt) === 0) {
        echo "This data does not exist!";
			}
else {
	echo "<script>window.location.href = 'Αρχική_διαχειριστή.php';</script>";
	exit();
}
mysqli_stmt_close($stmt);
    mysqli_close($conn);
}
?>
