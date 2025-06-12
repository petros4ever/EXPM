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
			background-color: orange;
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
    background-color: #db3488;
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
				<a href="Αρχική_πολίτη.php" class="link">Αρχική_πολίτη</a>
				<a href="Ανακοινώσεις.php" class="link">Ανακοινώσεις</a>
				<a href="Προβολή_δεδομένων2.php" class="link">Προβολή_δεδομένων</a>
				<a href="Δημιουργία_αιτημάτων.php" class="link">Δημιουργία_αιτημάτων</a>
				<a href="Εμφάνιση_αιτημάτων2.php" class="link">Εμφάνιση_αιτημάτων</a>
				<a href="Δημιουργία_προσφοράς.php" class="link">Δημιουργία_προσφοράς</a>
				<a href="Εμφάνιση_προσφοράς2.php" class="link">Εμφάνιση_προσφορών</a>
				<a href="Έξοδος.php" class="link">Έξοδος</a>
			</div>
		</nav>
	</body>
	</html>
