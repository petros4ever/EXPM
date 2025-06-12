<?php
include_once "Αρχική_πολίτη.php";
?>
<html>
<head>
  <h1>Ανακοινώσεις</h1>
</head>
</html>
<?php
require_once 'Εισαγωγή_στην_ΒΔ.php';
$sql = "SELECT * FROM announcements order by time desc";
$result = $conn->query($sql);

// Εμφάνιση των ανακοινώσεων
while ($row = $result->fetch_assoc()) {
  echo "<div class='announcement-box'>";
    echo "<p>" . $row['announcement'] . "</p>";
}

// Κλείσιμο σύνδεσης με τη βάση δεδομένων
$conn->close();
?>
