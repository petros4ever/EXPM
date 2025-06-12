<?php
session_start();
if (!isset($_SESSION["username"])) {
    echo "<script>window.location.href = 'Αρχική.php';</script>";
    exit();
}
 ?>
<html lang="en" dir="ltr">
	<head>
		<meta charset="utf-8">
		<title>Web Project 23'-24'</title>
		<style>

		body {
			background-color: brown;
		}

		.wrapper {
	    display: flex; 
	    padding: 14px 25px; /* Εξωτερική απόσταση του κουτιού */
	    text-decoration: none; /* Καμία γραμμή κάτω από το κείμενο του link */
	    color: #ffffff; /* Χρώμα κειμένου του link */
	}

	.wrapper a {
	    color: #fffff; /* Χρώμα κειμένου του link εντός του κουτιού */
	    text-decoration: none; /* Καμία γραμμή κάτω από το κείμενο του link εντός του κουτιού */
	}

	.link {
    background-color: green;
    color: #ffffff;
    padding: 10px 20px;
    text-decoration: none;
    border-radius: 5px;
    margin-right: 10px; /* Απόσταση μεταξύ των συνδέσμων - αυξήστε ανάλογα με τις ανάγκες σας */
}

.wrapper {
    margin-bottom: 20px; /* Απόσταση κάτω από την link-container - προσθέστε ανάλογα με τις ανάγκες σας */
}
		</style>
	</head>
	<body>
			<h2>Welcome, <?php echo $_SESSION["username"]; ?>!</h2>
		<nav>
			<div class="wrapper">
				<a href="Αρχική_διασώστη.php" class="link">Αρχική_Διασώστη</a>
				<a href="Χάρτης_με_δεδομένα3.php" class="link">Θεση οχήματος στον χαρτη</a>
					<a href="Χάρτης_με_δεδομένα2.php" class="link">Χάρτης_με_δεδομένα</a>
						<a href="Εμφάνιση_αιτημάτων_και_προσφορών.php" class="link">φόρτωση_στο_όχημα</a>
						<a href="Φορτίο.php" class="link">Φορτίο_Οχήματος</a>
				<a href="Έξοδος.php" class="link">Έξοδος</a>
			</div>
		</nav>
</body>
</html>
