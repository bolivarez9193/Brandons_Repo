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
if(isset($_GET["post_id"])){
	$post_id = $_GET["post_id"];
	$_SESSION["post_id"] = $post_id;
	$post = new Post();
	$post->findByID($post_id, $dbh);
	$postAuthor = User::findByID($post->author_id, $dbh);
	$users = User::findAll($dbh);
	require_once("views/comments.php");
} else {
	//no id, no post for you
	require_once("Posts.php");
}
?>
