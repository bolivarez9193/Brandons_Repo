<?php
require_once( 'PasswordHash.php' );

if( $_POST ) {
    $passwd = $_POST['data'];

    //////////////////////////////
    // manually doing it
    //
    // Just to show you how it works! NEVER do it this way!
    // First, MD5 is broken, and second, use tested code like PHPass.
	//////////////////////////////

    // EXAMPLE: STORING A PASSWORD HASH

    // Note! salt should be random per password, this is just an example
    // salts are usually fixed length (8 chars in this case)
    //$salt = 'abcdefgh';

    // hash salt together with password
    //$hash = md5( $salt.$passwd );

    // to check against it, we need to store the salt and the hash
    // common practice is to just append them together
    // (since the salt is a fixed length, splitting them is easy)
    //$hash_to_store = $salt.$hash;


    // EXAMPLE: CHECKING A PASSWORD AGAINST THAT HASH
    // (better succeed, since it's the same password)

    // extract the salt and the hash to check
    //$salt = substr($hash_to_store, 0, 8);
    //$hash = substr($hash_to_store, 8);

    //if( md5( $salt.$passwd ) == $hash ) {
       // echo "data checks out";
    //} else {
      //  echo "data does not check out";
    //}

    //////////////////////////////
    // Using PHPass (good!)
    //////////////////////////////

    // EXAMPLE: STORING A PASSWORD HASH

    $hasher = new PasswordHash( 8, false );
    $hash_to_store = $hasher->HashPassword( $passwd );
    // note: the salt is prepended to that hash

    // EXAMPLE: CHECKING A PASSWORD AGAINST THAT HASH
    // (better succeed, since it's the same password)
	/*
    $hasher = new PasswordHash( 8, false );
    if( $hasher->CheckPassword( $passwd, $hash_to_store ) ) {
    	echo "data checks out";
    } else {
    	echo "data does not check out";
    }
	*/
}

?>

<html>

<head>
<title>Hashing Tests</title>
</head>

<body>

<?php
	if( isset( $passwd ) ) {
	echo "<div>Data is: $passwd</div>";
	echo "<div>Hash is: $hash_to_store</div>";
} ?>

<form method="POST" action="">

<div>
	<input type="text" name="data" placeholder="Data Goes Here">
</div>

<div>
	<button type="submit">Send</button>
</div>

</form>

</body>
</html>