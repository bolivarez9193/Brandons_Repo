<?php
require_once( "models/DB.php" );
require_once( "models/Enemy.php" );

$add_enemy = new Enemy();
if( $_POST ) {
	$add_enemy->copyFromRow( $_POST );
	
	if( $add_enemy->validate() ) {
		$add_enemy->save( $dbh );
		# success! try a redirect to reset the URL
		header( 'Location: TheList.php' );
		die();
	}
}

# if failed, include main controller to show list again
include_once("TheList.php");

?>
