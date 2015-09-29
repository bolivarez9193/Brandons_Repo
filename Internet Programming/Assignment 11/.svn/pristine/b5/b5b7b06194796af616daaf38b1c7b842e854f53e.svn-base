<?php
require_once("models/DB.php");
require_once("models/Post.php");

session_start();
$user = $_SESSION["user"];
if($_POST){
	$post = new Post();
	$user_id = $user->id;
	$post->add_post($_POST["title"], $_POST["body"], $user_id, $dbh);
	echo '[]';
	}
?>