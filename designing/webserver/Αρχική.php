<html lang="en" dir="ltr">
	<head>
		<meta charset="utf-8">
		<title>Web Project 23'-24'</title>
		<style>
		body {
			background-color: MediumSeaGreen;
		}
		a:link, a:visited {
  background-color: #f44336;
  color: white;
  padding: 14px 25px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}

a:hover, a:active {
  background-color: red;
}

/* Κίνηση του κειμένου με χρήση της CSS animation */
			 @keyframes moveText {
					 0% { transform: translateX(-100%); opacity: 0; }
					 25% { transform: translateX(0); opacity: 1; }
					 50% { transform: translateX(100%); opacity: 0; }
					 75% { transform: translateX(0); opacity: 1; }
					 100% { transform: translateX(-100%); opacity: 0; }
			 }

			 /* Στυλ για τον κείμενο */
			 .moving-text {
					 font-size: 24px;
					 color: blue;
					 animation: moveText 20s linear infinite; /* Εφαρμογή της animation στο κείμενο */
			 }



		</style>
	</head>
	<body>
		<p class="moving-text">
			Προσοχή στις μετακινήσεις,προβλέπεται φυσική καταστροφή εντός ολίγων ωρών.
		</p>
		<nav>
			<div class="wrapper">
				<a href="Αρχική.php"></a>
					<ul>
						<a href="Αρχική.php">Αρχική</a>
						<?php
								echo "<a href='Δημιουργία_λογαριασμού_πολίτη.php'>Δημιουργία λογαριασμού πολίτη</a>";
								echo "<a href='Είσοδος_πολίτη.php'>Είσοδος πολίτη</a>";
								echo "<a href='Είσοδός_διαχειριστή.php'>Είσοδος διαχειριστή</a>";
								echo "<a href='Είσοδος_διασώστη.php'>Είσοδος διασώστη</a>";
						?>
					</ul>
			</div>
		</nav>
		 <img class="moved-image" src="katastrofes.jpg" alt="Ετικέτα Εικόνας" width="700" height="300">
</body>
</html>
