<?php
require_once("models/DB.php");
require_once("models/User.php");



if(isset($_SESSION["user"])){
	$user = $_SESSION["user"];
	require_once("posts.php");
} else {
	$login_user = new User();
	$signup_user = new User();
	
	include_once("views/loginform.php");
}
?>