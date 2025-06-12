<?php
include_once "Αρχική_διασώστη.php";
require_once 'Εισαγωγή_στην_ΒΔ.php';

$c_name = $_SESSION["username"];
$sql = "SELECT * FROM task where r_name='$c_name' and o_i is not null or r_i is not null";
$result = mysqli_query($conn, $sql);
// Get the result set
// Fetch the results as an associative array
while ($row = $result->fetch_assoc()) {
    // Process each row as needed
    // $row contains the data from the current row
    // For example, you can access $row['column_name'] to get the value of a specific column
    echo "task:"."</br>";
    echo "id: " . $row["id"] . " - r_name: " . $row["r_name"] ." -r_i:".$row["r_i"] ." -o_i: ".$row["o_i"]."<br>";
    // Add a complete button for each row
        echo '<form method="post" action="Εκφόρτωση.php">';
        echo '<input type="hidden" name="id" value="' . $row["id"] . '">';
        echo '<input type="hidden" name="r_i" value="' . $row["r_i"] . '">';
        echo '<input type="hidden" name="o_i" value="' . $row["o_i"] . '">';
        echo '<input type="submit" name="delete" value="delete">';
          echo '<input type="submit" name="complete" value="complete">';
        echo '</form>';

        echo "<br>";
}
if ($result->num_rows === 0) {
    echo "No task.";
}



      $conn->close();
?>
