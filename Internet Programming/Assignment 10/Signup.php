<?php
require_once( "models/DB.php" );
require_once( "models/User.php" );

// attempt to signup

// case 1: the signup fields are valid
// outcome: save the validated user object to the db, start a session and push
//          the user into session, and render the home.php view

// case 2: the signup fields are not valid
// outcome: create a $signup_user with the full_name and username set and
//          appropriate error messages, also an empty $login_user object,
//          and render the loginform.php view

// find their session or create a new one

session_start();
// copy the form fields in to a new User object

$full_name = $_POST["full_name"];
$username = $_POST["username"];
$password = $_POST["password"];
$password2 = $_POST["password2"];
$signup_user = new User();

$checkUser = User::findByUsername($username, $dbh);
// validate the object, if success, save and render home view
if($full_name!=null && $username!=null && $password!=null && $password2!=null && $signup_user->validatePassword($password, $password2) && !$checkUser){
	
	$signup_user->full_name = $full_name;
	$signup_user->username = $username;
	
	$signup_user->saveWithPassword($dbh, $password);
	$user = $signup_user;
	$_SESSION["user"]=$user;
	include_once( "views/home.php" );
	
// if failed, errors should already be set, go back to loginform view
// you'll also need an empty login user model for the page
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
} else if($checkUser){
	$signup_user->errors = array();
	$signup_user->errors['username'] = 'Username already taken.';
	$login_user = new User();
	include_once( "views/loginform.php" );
	
} else { 

	$login_user = new User();
	include_once( "views/loginform.php" );
}
?>
