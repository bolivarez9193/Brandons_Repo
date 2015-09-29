<?php
require_once( "models/DB.php" );
require_once( "models/User.php" );

// a sample content page

// case 1: they have an active session, with a valid user in it
// outcome: set $user to that User and render the content.php view

// case 2: they don't have an active session with a valid user in it
// outcome: render the noaccess.php view

// find their session or create a new one
session_start();

$user = new User();
// check session for a valid user, go to content if found
if(isset($_SESSION['user'])){
	$user = $_SESSION['user'];
	include_once("views/content.php");
}else{
// otherwise, not allowed here!
	include_once( "views/noaccess.php" );
}
?>
