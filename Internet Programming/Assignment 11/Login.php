<?php 
require_once("models/DB.php");
require_once("models/User.php");

session_start();

$username = $_POST["username"];
$password = $_POST["password"];

$login_user=User::findByUsername($username, $dbh);

if( $login_user&&$login_user->login($password) ) {
	$_SESSION["user"] = $login_user;
	$user = $login_user;
	require_once("Posts.php");
} 	else { 
	$signup_user = new User();

	include_once( "views/loginform.php" );
}
?>