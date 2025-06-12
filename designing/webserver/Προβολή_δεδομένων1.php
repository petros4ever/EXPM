<?php
include_once "Αρχική_διαχειριστή.php";
	require_once 'Εισαγωγή_στην_ΒΔ.php';
  $sql = "SELECT * FROM item";
$result = mysqli_query($conn, $sql);
echo "items in our database:"."<br>";
if (mysqli_num_rows($result) > 0) {
    while ($row = mysqli_fetch_assoc($result)) {
        echo "id: " . $row["id"] . " - name: " . $row["name"] ."-quantity:".$row["quantity"] ."<br>";
    }
} else {
    echo "0 results";
}
?>
