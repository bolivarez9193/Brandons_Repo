<?php
try{
		$dbh = new PDO( 'mysql:host=localhost;dbname=recipes',
							'bjolivarez', 'insertpassword',
							array( PDO::ATTR_PERSISTENT => true ) );
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}catch( PDOException $e ) {
			print "ERROR: ".$e->getMessage();
}
?>