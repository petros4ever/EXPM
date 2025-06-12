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
	</style>
</head>
<body>
  <div id="map" style="width: 600px; height: 400px;"></div>
	<button onclick="saveCoordinates()">Save Coordinates</button>
<script>
	var map = L.map('map').setView([38.24905,21.73823], 18);
	const tiles = L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
		maxZoom: 19,
		attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
	}).addTo(map);
	let marker;
	// Λειτουργία για αποθήκευση των συντεταγμένων
function saveCoordinates(lat, lng) {
    var data = { lat: lat, lng: lng };

    // Χρήση του AJAX για αποστολή των δεδομένων στον διακομιστή
    $.ajax({
        type: "POST",
        url: "Χάρτης6.php", // Συμπληρώστε το όνομα του αρχείου διακομιστή
        data: data,
        success: function(response) {
            console.log("Coordinates saved successfully");
        },
        error: function(error) {
            console.error("Error saving coordinates", error);
        }
    });
}

// Προσθέτουμε event listener για τον χάρτη
map.on('click', function(e) {
    var latLng = e.latlng;

    // Αν δεν υπάρχει ο marker, δημιουργούμε έναν
    if (!marker) {
        marker = L.marker(latLng, { draggable: true }).addTo(map);

        // Προσθέτουμε event listener για την μετακίνηση του marker
        marker.on('dragend', function(e) {
            var updatedLatLng = e.target.getLatLng();
            saveCoordinates(updatedLatLng.lat, updatedLatLng.lng);
        });
    } else {
        // Αν υπάρχει ήδη ο marker, απλώς τον μετακινούμε
        marker.setLatLng(latLng);
        saveCoordinates(latLng.lat, latLng.lng);
    }
});
  </script>
</body>
</html>
