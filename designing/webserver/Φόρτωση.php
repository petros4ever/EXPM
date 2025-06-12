<?php
session_start();
if (isset($_POST['insert_O'])) {
  $c_name = $_SESSION["username"];
  $id=$_POST['id'];

// Error handling in signup form

require_once 'Εισαγωγή_στην_ΒΔ.php';
$sql="insert into task(r_name,o_i) values('" . $_SESSION['username'] . "','$id')  ";
if (mysqli_query($conn, $sql))
{
  $update_sql="update offering set w_date=now() where id=$id";
  if (mysqli_query($conn, $update_sql)) {
         echo "<script>
             alert('New record created successfully');
             window.location.href = 'Αρχική_διασώστη.php';
         </script>";
         exit();
     } else {
         echo "Error updating record: " . mysqli_error($conn);
     }
}
else
    {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
     }
}


mysqli_close($conn);

?>
