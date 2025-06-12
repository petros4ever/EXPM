<?php

$serverName = "localhost";
$databaseUsername = "root";
$databasePassword = '';
$databaseName = "www";

$conn = mysqli_connect($serverName, $databaseUsername, $databasePassword, $databaseName);

if (!$conn) {
	die("Αποτυχία Σύνδεσης: " . mysqli_connect_error());
}
?>
