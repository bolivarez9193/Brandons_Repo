<?php
require_once( "models/User.php" );

// user wants to logout

// all cases
// outcome: start/destroy session and redirect to the index.php controller

session_start();
session_destroy();

header( "Location: index.php" );
die();
?>
