<?php
require_once 'Εισαγωγή_στην_ΒΔ.php';
$name=$_SESSION["username"];
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
      $sql = "SELECT * FROM vasi  ORDER BY time DESC limit 1";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
$markers = array();
      while ($row = $result->fetch_assoc()) {
        $markers[] = array(
       'x' => $row['x'],
       'y' => $row['y'],
       'time'   => $row['time'],
   );
      }
      $sql = "SELECT * FROM rescuer  where username='$name' ORDER BY time DESC limit 1";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
    $markers3 = array();
      while ($row = $result->fetch_assoc()) {
        $markers3[] = array(
       'username' => $row['username'],
       'car_name' => $row['car_name'],
       'x' => $row['x'],
       'y' => $row['y'],
       'time'   => $row['time'],
    );
      }
      $sql = "SELECT request.c_name,request.c_tel,request.reg_date,request.i_name,request.req_quantity,civ.x,civ.y FROM request inner join civ on civ.username=request.c_name where w_date is null";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
      $markers1 = array();
      while ($row = $result->fetch_assoc()) {
        $markers1[] = array(
       'c_name' => $row['c_name'],
       'c_tel' => $row['c_tel'],
       'reg_date'   => $row['reg_date'],
       'i_name'   => $row['i_name'],
       'req_quantity'   => $row['req_quantity'],
       'x'   => $row['x'],
       'y'   => $row['y'],
      );
      }
      $sql = "SELECT request.c_name,request.c_tel,request.reg_date,request.i_name,request.req_quantity,request.w_date,civ.x,civ.y FROM request inner join civ on civ.username=request.c_name where w_date is not null";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
      $markers4 = array();
      while ($row = $result->fetch_assoc()) {
        $markers4[] = array(
       'c_name' => $row['c_name'],
       'c_tel' => $row['c_tel'],
       'w_date' => $row['w_date'],
       'reg_date'   => $row['reg_date'],
       'i_name'   => $row['i_name'],
       'req_quantity'   => $row['req_quantity'],
       'x'   => $row['x'],
       'y'   => $row['y'],
      );
      }
      $sql="SELECT offering.c_name,offering.c_tel,offering.reg_date,offering.i_name,offering.off_quantity,civ.x,civ.y FROM offering inner join civ on civ.username=offering.c_name where w_date is null";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
      $markers2 = array();
      while ($row = $result->fetch_assoc()) {
        $markers2[] = array(
       'c_name' => $row['c_name'],
       'c_tel' => $row['c_tel'],
       'reg_date'   => $row['reg_date'],
       'i_name'   => $row['i_name'],
       'off_quantity'   => $row['off_quantity'],
       'x'   => $row['x'],
       'y'   => $row['y'],
      );
      }
      $sql="SELECT offering.c_name,offering.c_tel,offering.reg_date,offering.i_name,offering.off_quantity,offering.w_date,civ.x,civ.y FROM offering inner join civ on civ.username=offering.c_name where w_date is not null";
      $result = $conn->query($sql);
      if ($result === false) {
          die("Query failed: " . $conn->error);
      }
      // Initialize an array to store marker data
      $markers5 = array();
      while ($row = $result->fetch_assoc()) {
        $markers5[] = array(
       'c_name' => $row['c_name'],
       'c_tel' => $row['c_tel'],
       'reg_date'   => $row['reg_date'],
       'w_date'   => $row['w_date'],
       'i_name'   => $row['i_name'],
       'off_quantity'   => $row['off_quantity'],
       'x'   => $row['x'],
       'y'   => $row['y'],
      );
      }
      // Κλείσιμο σύνδεσης με τη βάση δεδομένων
      $conn->close();

?>

<!DOCTYPE html>
<html lang="en">
<head>
	<base target="_top">
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Quick Start - Leaflet</title>
	<link rel="stylesheet" href="https://unpkg.com/leaflet@1.3.0/dist/leaflet.css" />
	<link rel="stylesheet" href="https://opengeo.tech/maps/leaflet-search/src/leaflet-search.css" />
	<script src="https://unpkg.com/leaflet@1.3.0/dist/leaflet.js"></script>
	<script src="https://opengeo.tech/maps/leaflet-search/src/leaflet-search.js"></script>
	<script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
	<style>
		html, body {
			height: 100%;
			margin: 0;
		}
		.leaflet-container {
			height: 400px;
			width: 600px;
			max-width: 100%;
			max-height: 100%;
		}
    .marker{
      background-color: purple;
      width: 20px;
      height: 20px;
    }
    .marker1{
      background-color: green;
      width: 20px;
      height: 20px;
    }
    .marker2{
      background-color: blue;
      width: 20px;
      height: 20px;
    }
    .marker3{
      background-color: red; 
      width: 20px;
      height: 20px;
    }
	</style>
</head>
<body>
  <div id="map" style="width: 600px; height: 400px;"></div>
  <button onclick="toggleMarkers()">Toggle Markers where are requests and not defined from resquer</button>
  <button onclick="toggleMarkers1()">Toggle Markers where are offered and not defined from resquer</button>
  <button onclick="toggleMarkers2()">Toggle Markers where are requests defined from resquer</button>
  <button onclick="toggleMarkers3()">Toggle Markers where are offered and  defined from resquer</button>
<script>
	var map = L.map('map').setView([38.24905,21.73823], 18);
	const tiles = L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
		maxZoom: 19,
		attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
	}).addTo(map);
  <?php foreach ($markers as $marker): ?>
    L.marker([<?php echo $marker['x']; ?>, <?php echo $marker['y']; ?>],{
      icon: L.divIcon({
          className: 'leaflet-div-icon',
          html: '<div class="marker3"></div>',
          iconSize: [20, 20]})}).addTo(map)
        .bindPopup('x: <?php echo $marker['x']; ?><br>y: <?php echo $marker['y']; ?><br>time: <?php echo $marker['time']; ?>');
<?php endforeach; ?>
var markersGroup = L.layerGroup();
<?php foreach ($markers1 as $marker1): ?>
  var marker1=L.marker([<?php echo $marker1['x']; ?>, <?php echo $marker1['y']; ?>],{
    icon: L.divIcon({
        className: 'leaflet-div-icon',
        html: '<div class="marker"></div>',
        iconSize: [20, 20]})}).addTo(map)
      .bindPopup('x: <?php echo $marker1['x']; ?><br>y: <?php echo $marker1['y']; ?><br>c_name: <?php echo $marker1['c_name']; ?><br>c_tel: <?php echo $marker1['c_tel']; ?><br>reg_date: <?php echo $marker1['reg_date']; ?><br>i_name: <?php echo $marker1['i_name']; ?><br>req_quantity: <?php echo $marker1['req_quantity']; ?>');
 markersGroup.addLayer(marker1);
<?php endforeach; ?>
var markersGroup1=L.layerGroup();
<?php foreach ($markers2 as $marker2): ?>
  var marker2=L.marker([<?php echo $marker2['x']; ?>, <?php echo $marker2['y']; ?>]).addTo(map)
      .bindPopup('x: <?php echo $marker2['x']; ?><br>y: <?php echo $marker2['y']; ?><br>c_name: <?php echo $marker2['c_name']; ?><br>c_tel: <?php echo $marker2['c_tel']; ?><br>reg_date: <?php echo $marker2['reg_date']; ?><br>i_name: <?php echo $marker2['i_name']; ?><br>off_quantity: <?php echo $marker2['off_quantity']; ?>');
 markersGroup1.addLayer(marker2);
<?php endforeach; ?>
<?php foreach ($markers3 as $marker3): ?>
  var marker3=L.marker([<?php echo $marker3['x']; ?>, <?php echo $marker3['y']; ?>],{
    icon: L.divIcon({
        className: 'leaflet-div-icon',
        html: '<div class="marker2"></div>',
        iconSize: [20, 20]})}).addTo(map)
      .bindPopup('x: <?php echo $marker3['x']; ?><br>y: <?php echo $marker3['y']; ?><br>username: <?php echo $marker3['username']; ?><br>car_name: <?php echo $marker3['car_name']; ?><br>time: <?php echo $marker3['time']; ?>');
<?php endforeach; ?>
var markersGroup2 = L.layerGroup();
<?php foreach ($markers4 as $marker4): ?>
  var marker4=L.marker([<?php echo $marker4['x']; ?>, <?php echo $marker4['y']; ?>],{
    icon: L.divIcon({
        className: 'leaflet-div-icon',
        html: '<div class="marker1"></div>',
        iconSize: [20, 20]})}).addTo(map)
      .bindPopup('x: <?php echo $marker4['x']; ?><br>y: <?php echo $marker4['y']; ?><br>c_name: <?php echo $marker4['c_name']; ?><br>c_tel: <?php echo $marker4['c_tel']; ?><br>reg_date: <?php echo $marker4['reg_date']; ?><br>i_name: <?php echo $marker4['i_name']; ?><br>req_quantity: <?php echo $marker4['req_quantity']; ?><br>w_date: <?php echo $marker4['w_date']; ?>');
 markersGroup2.addLayer(marker4);
<?php endforeach; ?>
var markersGroup3=L.layerGroup();
<?php foreach ($markers5 as $marker5): ?>
  var marker5=L.marker([<?php echo $marker5['x']; ?>, <?php echo $marker5['y']; ?>]).addTo(map)
      .bindPopup('x: <?php echo $marker5['x']; ?><br>y: <?php echo $marker5['y']; ?><br>c_name: <?php echo $marker5['c_name']; ?><br>c_tel: <?php echo $marker5['c_tel']; ?><br>reg_date: <?php echo $marker5['reg_date']; ?><br>i_name: <?php echo $marker5['i_name']; ?><br>off_quantity: <?php echo $marker5['off_quantity']; ?><br>w_date: <?php echo $marker5['w_date']; ?>');
 markersGroup3.addLayer(marker5);
<?php endforeach; ?>
markersGroup.addTo(map);
markersGroup1.addTo(map);
markersGroup2.addTo(map);
markersGroup3.addTo(map);
 function toggleMarkers() {
   markersGroup.eachLayer(function(layer) {
     layer.setOpacity(layer.options.opacity === 0 ? 1 : 0);
   });
 }
 function toggleMarkers1() {
   markersGroup1.eachLayer(function(layer) {
     layer.setOpacity(layer.options.opacity === 0 ? 1 : 0);
   });
 }
 function toggleMarkers2() {
   markersGroup2.eachLayer(function(layer) {
     layer.setOpacity(layer.options.opacity === 0 ? 1 : 0);
   });
 }
 function toggleMarkers3() {
   markersGroup3.eachLayer(function(layer) {
     layer.setOpacity(layer.options.opacity === 0 ? 1 : 0);
   });
 }
  </script>
  <div>

  </div>
</body>
</html>
