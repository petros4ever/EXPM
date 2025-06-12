<?php
session_start();
if (isset($_POST['delete_offer'])) {
  $c_name = $_SESSION["username"];
  $id=$_POST['id'];

// Error handling in signup form

require_once 'Εισαγωγή_στην_ΒΔ.php';
$sql="delete from offering where id=? and w_date is null and o_name is null";
$stmt = mysqli_prepare($conn, $sql);
     mysqli_stmt_bind_param($stmt, "i",$id);

     if (mysqli_stmt_execute($stmt)) {
         echo "<script>
             alert('deleted successfully');
             window.location.href = 'Αρχική_πολίτη.php';</script>";
         exit();
     } else {
         echo "Error: " . $sql . "<br>" . mysqli_error($conn);
     }

     mysqli_stmt_close($stmt);
 }

mysqli_close($conn);

?>
