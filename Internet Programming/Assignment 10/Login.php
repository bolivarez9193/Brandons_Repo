<?php
require_once( "models/DB.php" );
require_once( "models/User.php" );

// attempt to login

// case 1: the username/password match what's in the db
// outcome: inflate $user with that username, start a session and push the user
//          into session as userid, and render the home.php view

// case 2: the username/password don't match what's in the db
// outcome: the $login_user should have an appropriate error set, create an 
//          empty $signup_user object, and render the loginform.php view

// find their session or create a new one
session_start();

// try logging in
$username = $_POST["username"];
$password = $_POST["password"];

$login_user=User::findByUsername($username, $dbh);

if( $login_user&&$login_user->login($password) ) {

// on success, show the home view and get out of here
	$_SESSION["user"] = $login_user;
	$user = $login_user;
	require_once("views/home.php");
} 	else { 
     
// on failure, errors should be set in the User model so that GetError works
// you'll also need an empty signup user model for the page
	$signup_user = new User();

	include_once( "views/loginform.php" );
}
?>
