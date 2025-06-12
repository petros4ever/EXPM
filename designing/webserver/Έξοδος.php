<?php
session_start();

// Καταστροφή όλων των δεδομένων της συνεδρίας
session_destroy();

// Ανακατεύθυνση στη σελίδα σύνδεσης
  echo "<script>window.location.href = 'Αρχική.php';</script>";
exit();
?>
