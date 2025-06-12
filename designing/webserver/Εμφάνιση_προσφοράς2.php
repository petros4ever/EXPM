<?php
include_once "Αρχική_πολίτη.php";
require_once 'Εισαγωγή_στην_ΒΔ.php';

$c_name = $_SESSION["username"];
$sql = "SELECT * FROM offering WHERE c_name=? ORDER BY reg_date DESC";
$stmt = $conn->prepare($sql);

// Bind the parameter
$stmt->bind_param("s", $c_name);

// Execute the query
$stmt->execute();

// Get the result set
$result = $stmt->get_result();
// Fetch the results as an associative array
while ($row = $result->fetch_assoc()) {
    // Process each row as needed
    // $row contains the data from the current row
    // For example, you can access $row['column_name'] to get the value of a specific column
    echo "i offer:"."</br>";
    echo "item_name: " . $row["i_name"] . " - quantity: " . $row["off_quantity"] ." -reg_date:".$row["reg_date"] ." -w_date: ".$row["w_date"]." -o_name:".$row["o_name"]."<br>";
    // Add a delete button for each row
        echo '<form method="post" action="Διαγραφή_προσφοράς2.php">';
        echo '<input type="hidden" name="id" value="' . $row["id"] . '">';
        echo '<input type="submit" name="delete_offer" value="Delete">';
        echo '</form>';

        echo "<br>";
}
if ($result->num_rows === 0) {
    echo "No results found.";
}

$stmt->close();

      $conn->close();
?>
