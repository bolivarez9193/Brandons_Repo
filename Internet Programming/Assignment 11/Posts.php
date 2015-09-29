<?php
require_once("models/User.php");
require_once("models/DB.php");
require_once("models/Post.php");

session_start();
if(!isset($_SESSION["user"])){
	$user = new User();
	$user->username = "Guest";
}
else{
	$user = $_SESSION["user"];
}

$posts = Post::sortByTime($dbh);
$users = User::findAll($dbh);

include_once("views/posts.php");
?>