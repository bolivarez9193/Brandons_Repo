<?php 
require_once("Models/User.php");

$user = new User();

    $user->username = "testguy";
    $user->full_name = "Test Guy";
    $user->saveWithPassword($dbh, "bogusbogusbogus");
    echo "User added, ID is: ".$user->id."<br/>";

    // test update
    $user->full_name = "Test Gal";
    $user->saveWithPassword($dbh, "bogusbogusbogus");
    echo "User updated, ID should not have changed: ".$user->id."<br/>";
	
	//$user = new User();
    //$user->findByUsername("testguy", $dbh);
    //echo "Got user ".$user->full_name." (".$user->username."), id: ".$user->id."<br/>";

    //echo "Login with correct password...<br/>";
    //if( $user->login("bogusbogusbogus") ) {
      // echo "Success!<br/>";
    //} else { 
      // echo "Failure!<br/>";
    //}
	/*
    echo "Login with incorrect password...<br/>";
    if( $user->login("notmypassword") ) {
       echo "Success!<br/>";
    } else { 
       echo "Failure!<br/>";
    }
	*/
?>