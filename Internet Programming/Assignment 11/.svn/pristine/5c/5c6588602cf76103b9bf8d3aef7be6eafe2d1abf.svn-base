<?php
require_once("models/DB.php");
require_once("models/Comment.php");

$post_id = $_SESSION["post_id"];
header( "Content-type: text/json" );
echo json_encode(get_comments($_GET['next'], $post_id, $dbh));
?>