<?php
require_once( "models/DB.php" );
require_once( "models/Enemy.php" );

//Bonus Question
session_start();
if(isset($_SESSION['doomed'])){
	$_SESSION['doomed'] = $_SESSION['doomed'] + 1;
} else{
	$_SESSION['deleted'] = 1;
}

//Question 4
if( isset( $_GET['id']) ) {
	$id = $_GET['id'];
	$doom = Enemy::find($id, $dbh);
	$doom->delete($dbh);
} else {
# no id to delete, failed!
	echo json_encode( array( 'status' => 'fail' ) );
}
?>
