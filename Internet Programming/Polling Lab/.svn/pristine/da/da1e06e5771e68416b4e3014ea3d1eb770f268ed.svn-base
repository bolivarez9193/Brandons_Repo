<?php
require_once("messaging.php");

if( $_POST ) {
	add_message( $_POST['username'], $_POST['text'], $dbh);
	echo '[]';

} else {
	echo json_encode(get_messages( $_GET['next'], $dbh ));
}
?>