<?php
require_once( "models/DB.php" );
require_once( "models/User.php" );

session_start();
$full_name = $_POST["full_name"];
$username = $_POST["username"];
$password = $_POST["password"];
$password2 = $_POST["password2"];
$signup_user = new User();


if($full_name!=null && $username!=null && $password!=null && $password2!=null && $signup_user->validatePassword($password, $password2) ){
	
	$signup_user->full_name = $full_name;
	$signup_user->username = $username;
	
	$signup_user->saveWithPassword($dbh, $password);
	$user = $signup_user;
	$_SESSION["user"]=$user;
	include_once( "views/posts.php" );
	
} else if($full_name==null){
	$signup_user->errors = array();
	$signup_user->errors['full_name'] = 'You need to enter a name.';
	$login_user = new User();
	include_once( "views/loginform.php" );
	
} else if($username==null){
	$signup_user->errors = array();
	$signup_user->errors['username'] = 'You need to enter a username.';
	$login_user = new User();
	include_once( "views/loginform.php" );
	
} else if($password==null || $password2==null){
	$signup_user->errors = array();
	$signup_user->errors['password'] = 'Password fields cannot be blank.';
	$login_user = new User();
	include_once( "views/loginform.php" );

} else { 

	$login_user = new User();
	include_once( "views/loginform.php" );
}
?>
