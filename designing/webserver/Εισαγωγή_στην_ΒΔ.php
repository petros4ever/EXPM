<?php

$serverName = "localhost";
$databaseUsername = "root";
$databasePassword = 'p3T0$_#10o%reDU4@ll';
$databaseName = "www";

$conn = mysqli_connect($serverName, $databaseUsername, $databasePassword, $databaseName);

if (!$conn) {
	die("Αποτυχία Σύνδεσης: " . mysqli_connect_error());
}
?>
