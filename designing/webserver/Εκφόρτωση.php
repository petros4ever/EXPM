<?php
session_start();
if (isset($_POST['delete']))
{
  $c_name = $_SESSION["username"];
  $id=$_POST['id'];
  $r_i=$_POST['r_i'];
  $o_i=$_POST['o_i'];
  require_once 'Εισαγωγή_στην_ΒΔ.php';
if($o_i!==null && $r_i==null)
{
  $sql1="update offering set w_date=null where id='$o_i'";
  if (mysqli_query($conn, $sql1)) {
    $sql12="delete from task  where id='$id'";
    if (mysqli_query($conn, $sql12)) {
         echo "<script>
             alert('New record created successfully');
             window.location.href = 'Αρχική_διασώστη.php';
         </script>";
         exit();
     }
   }else {
         echo "Error updating record: " . mysqli_error($conn);
     }
}

elseif($o_i==null && $r_i!==null)
{
  $sql2="update request set w_date=null where id='$r_i'";
  if (mysqli_query($conn, $sql2)) {
    $sql22="delete from task  where id='$id'";
    if (mysqli_query($conn, $sql22)) {
         echo "<script>
             alert('New record created successfully');
             window.location.href = 'Αρχική_διασώστη.php';
         </script>";
         exit();
     }
   }else {
         echo "Error updating record: " . mysqli_error($conn);
     }
}
  }
if (isset($_POST['complete']))
{
  $c_name = $_SESSION["username"];
  $id=$_POST['id'];
  $r_i=$_POST['r_i'];
  $o_i=$_POST['o_i'];
  require_once 'Εισαγωγή_στην_ΒΔ.php';
  if($o_i!==null && $r_i==null)
  {
    $sql="select off_quantity,i_name from offering where id='$o_i'";
    $result = mysqli_query($conn, $sql);
    while ($row=$result->fetch_assoc()) {
      $o_q=$row['off_quantity'];
      $i_name=$row['i_name'];
      $sql3="update item set quantity=quantity+$o_q where name='$i_name'";
      if (mysqli_query($conn, $sql3)) {
        $sql32="delete from task  where id='$id'";
        if (mysqli_query($conn, $sql32)) {
             echo "<script>
                 alert('New record created successfully');
                 window.location.href = 'Αρχική_διασώστη.php';
             </script>";
             exit();
         }
       }else {
             echo "Error updating record: " . mysqli_error($conn);
         }
    }
  }
  elseif($o_i==null && $r_i!==null)
  {
    $sql4="select req_quantity,i_name from request where id='$r_i'";
    $result = mysqli_query($conn, $sql4);
    while ($row=$result->fetch_assoc()) {
      $r_q=$row['req_quantity'];
      $i_name=$row['i_name'];
      $sql5="update item set quantity=quantity-$r_q where name='$i_name'";
      if (mysqli_query($conn, $sql5)) {
        $sql52="delete from task  where id='$id'";
        if (mysqli_query($conn, $sql52)) {
             echo "<script>
                 alert('New record created successfully');
                 window.location.href = 'Αρχική_διασώστη.php';
             </script>";
             exit();
         }
       }else {
             echo "Error updating record: " . mysqli_error($conn);
         }
    }

  }
}

mysqli_close($conn);
 ?>
