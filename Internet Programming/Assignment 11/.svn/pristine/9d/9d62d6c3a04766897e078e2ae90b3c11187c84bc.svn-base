<?php
try{
		$dbh = new PDO( 'mysql:host=localhost;dbname=3342a11',
							'3342', 'temp1234',
							array( PDO::ATTR_PERSISTENT => true ) );
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}catch( PDOException $e ) {
			print "ERROR: ".$e->getMessage();
}
?>