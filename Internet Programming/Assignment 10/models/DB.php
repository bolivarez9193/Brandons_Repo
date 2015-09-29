<?php
try{
		$dbh = new PDO( 'mysql:host=localhost;dbname=3342a10',
							'3342', 'temp1324',
							array( PDO::ATTR_PERSISTENT => true ) );
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}catch( PDOException $e ) {
			print "ERROR: ".$e->getMessage();
}
?>