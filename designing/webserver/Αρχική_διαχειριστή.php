<html lang="en" dir="ltr">
	<head>
		<meta charset="utf-8">
		<title>Web Project 23'-24'</title>
		<style>

		body {
			background-color: cyan;
		}

		.wrapper {
	    display: flex; 
	    padding: 14px 25px; /* Εξωτερική απόσταση του κουτιού */
	    text-decoration: none; /* Καμία γραμμή κάτω από το κείμενο του link */
	    color: #ffffff; /* Χρώμα κειμένου του link */
	}

	.wrapper a {
	    color: #ffffff; /* Χρώμα κειμένου του link εντός του κουτιού */
	    text-decoration: none; /* Καμία γραμμή κάτω από το κείμενο του link εντός του κουτιού */
	}

	.link {
    background-color: #db5034;
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
		<nav>
			<div class="wrapper">
        <a href="Αρχική_διαχειριστή.php" class="link">Αρχική_Διαχειριστή</a>
				<a href="Εμφάνιση_Χάρτη1.php" class="link">Καθορισμός_βάσης</a>
				<a href="Προβολή_δεδομένων1.php" class="link">Προβολή_δεδομένων</a>
				<a href="Δημιουργία_λογαριασμού_διασώστη.php" class="link">Δημιουργία_διασωστών</a>
				<a href="Δημιουργία_ανακοινώσεων.php" class="link">Δημιουργία_ανακοινώσεων</a>
				<a href="Χάρτης_με_δεδομένα.php" class="link">Χάρτης_με_δεδομένα</a>
        <a href="Αρχική.php" class="link">Έξοδος</a>
			</div>
		</nav>
	</body>
	</html>
