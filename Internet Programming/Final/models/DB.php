<?php
try {
  # mirin
  $dbconnstr='mysql:host=localhost;dbname=final';
  $dbuser='bjolivarez';
  $dbpass='insertpassword';
  # hostgator
  #$dbconnstr='mysql:host=localhost;dbname=utpa01_recipes';
  #$dbuser='utpa01_temp';
  #$dbpass='temp1234';

	$dbh = new PDO( $dbconnstr, $dbuser, $dbpass,
 		array( PDO::ATTR_PERSISTENT => true) );

	$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

} catch( PDOException $e ) { 
	print "ERROR: ".$e->getMessage()."<br/>";
	die();
}
?>
