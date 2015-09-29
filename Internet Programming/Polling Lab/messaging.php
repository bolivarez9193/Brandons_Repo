<?php
try {
	$dbh = new PDO( 'mysql:host=localhost;dbname=3342a11', 
		'bjolivarez', 'insertpassword',
 		array( PDO::ATTR_PERSISTENT => true) );

	$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

} catch( PDOException $e ) { 
	print "ERROR: ".$e->getMessage()."<br/>";
	die();
}

function get_messages($next, $dbh) {
	$stmt = $dbh->prepare( "SELECT * FROM comments WHERE id >= :next ORDER BY id" );
	$stmt->bindParam(":next", $next);
	$stmt->execute();

	return $stmt->fetchall(); 
}

function add_message($user, $text, $dbh) {
	$stmt = $dbh->prepare( "INSERT INTO messages (username, text) VALUES(:user, :text)" );
	$stmt->bindParam(":user", $user);
	$stmt->bindParam(":text", $text);
	$stmt->execute();
}
?>
