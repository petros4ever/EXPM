<?php
include_once "Αρχική_διασώστη.php";
require_once 'Εισαγωγή_στην_ΒΔ.php';

$c_name = $_SESSION["username"];
$sql = "SELECT * FROM offering where w_date is null ORDER BY reg_date DESC";
$result = mysqli_query($conn, $sql);
// Get the result set
// Fetch the results as an associative array
while ($row = $result->fetch_assoc()) {
    // Process each row as needed
    // $row contains the data from the current row
    // For example, you can access $row['column_name'] to get the value of a specific column
    echo "offer:"."</br>";
    echo "item_name: " . $row["i_name"] . " - quantity: " . $row["off_quantity"] ." -reg_date:".$row["reg_date"] ." -w_date: ".$row["w_date"]." -o_name:".$row["o_name"]."<br>";
    // Add a insert button for each row
        echo '<form method="post" action="Φόρτωση.php">';
        echo '<input type="hidden" name="id" value="' . $row["id"] . '">';
        echo '<input type="submit" name="insert_O" value="insert">';
        echo '</form>';

        echo "<br>";
}
if ($result->num_rows === 0) {
    echo "No offers found.";
}
$sql = "SELECT * FROM request where w_date is null ORDER BY reg_date DESC";
$result = mysqli_query($conn, $sql);
// Get the result set
// Fetch the results as an associative array
while ($row = $result->fetch_assoc()) {
    // Process each row as needed
    // $row contains the data from the current row
    // For example, you can access $row['column_name'] to get the value of a specific column
    echo "request:"."</br>";
    echo "item_name: " . $row["i_name"] . " - quantity: " . $row["req_quantity"] ." -reg_date:".$row["reg_date"] ." -w_date: ".$row["w_date"]." -o_name:".$row["o_name"]."<br>";
    // Add a insert button for each row
        echo '<form method="post" action="Φόρτωση2.php">';
        echo '<input type="hidden" name="id" value="' . $row["id"] . '">';
        echo '<input type="submit" name="insert_R" value="insert">';
        echo '</form>';

        echo "<br>";
}
if ($result->num_rows === 0) {
    echo "No requests found.";
}



      $conn->close();
?>
