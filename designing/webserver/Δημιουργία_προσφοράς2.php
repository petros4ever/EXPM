<?php
session_start();
if (isset($_POST['submit'])) {

	$name = $_POST['name'];
	$quantity=$_POST["quantity"];

// Error handling in signup form

require_once 'Εισαγωγή_στην_ΒΔ.php';
if (empty($name) || empty($quantity))
{
	echo "not all data has been recorded";
}
else {
  // Εκτέλεσε την SQL επερώτηση για να ανακτήσεις το τηλέφωνο
  $sql = "SELECT telephone FROM civ WHERE username = '{$_SESSION["username"]}'";
  $result = mysqli_query($conn, $sql);

  // Έλεγξε αν υπάρχει αποτέλεσμα
  if ($result) {
      // Αν υπάρχει, ανάκτησε το τηλέφωνο
      $row = mysqli_fetch_assoc($result);
      $_SESSION["telephone"] = $row["telephone"];
  } else {
      // Αν υπάρξει κάποιο σφάλμα στην επερώτηση, μπορείς να το χειριστείς κατάλληλα
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
  }
	$sql="insert into offering(c_name,c_tel,reg_date,i_name,off_quantity) values('" . $_SESSION['username'] . "', '" . $_SESSION['telephone'] . "', now(), '$name', '$quantity')";
	if (mysqli_query($conn, $sql))
	{
		echo "<script>
    alert('New record created successfully');
		window.location.href = 'Αρχική_πολίτη.php';</script>";
			exit();
	}
	else
			{
						echo "Error: " . $sql . "<br>" . mysqli_error($conn);
			 }
}

	}
mysqli_close($conn);


?>
