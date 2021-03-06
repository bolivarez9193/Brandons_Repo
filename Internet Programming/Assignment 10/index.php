<?php
require_once( "models/DB.php" );
require_once( "models/User.php" );

// this is the main entry point

// case 1: they have an active session, with a valid userid in it
// outcome: inflate $user with that id and render the home.php view

// case 2: they don't have an active session with a valid userid in it
// outcome: create an empty $user object, set the username to "Filthy, Filthy Guest",
//          and render the home.php view

// find their session or create a new one
session_start();


// make a User object $user with the default name "Guest"

if(!isset($_SESSION['user'])){
	$user = new User();
	$user->username = "guest";
}
// if there's a user object in session, inflate the $user object with it
else{
	$user = $_SESSION['user'];	
}

// at this point you always have a session and user, include the home view
include_once( "views/home.php" );
?>
