<?php
require_once( "models/DB.php" );
require_once( "models/Enemy.php" );

session_start();

if(isset($_SESSION['doomed'])){
	$doomed = $_SESSION['doomed'];
} else{
	$_SESSION['deleted'] = 0;
	$doomed = $_SESSION['deleted'];
}

$enemies = Enemy::findAll($dbh);

include_once( "views/thelist.php" );
?>
