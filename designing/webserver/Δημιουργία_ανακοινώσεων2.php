<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $announcement = $_POST['announcement'];
require_once 'Εισαγωγή_στην_ΒΔ.php';
    // Εισαγωγή ανακοίνωσης στη βάση δεδομένων
    $sql = "INSERT INTO announcements (announcement,time) VALUES ('$announcement',now())";
    if ($conn->query($sql) === TRUE) {
        echo "<script>
  	    alert('New record created successfully');
  			window.location.href = 'Δημιουργία_ανακοινώσεων.php';</script>";
        exit();
    } else {
        echo "Σφάλμα κατά την καταχώρηση της ανακοίνωσης: " . $conn->error;
    }
}
mysqli_close($conn);
?>
