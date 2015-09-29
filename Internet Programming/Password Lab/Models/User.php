<?php
require_once("PasswordHash.php");

try{
		$dbh = new PDO( 'mysql:host=localhost;dbname=3342a10',
							'3342', 'temp1324',
							array( PDO::ATTR_PERSISTENT => true ) );
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}catch( PDOException $e ) {
			print "ERROR: ".$e->getMessage();
}

class User
{
	public static $tableName = "users";
	
	public $username;
	public $full_name;
	public $id;
	public $password_hash;
	public $admin;
	
	function copyFromRow( $row ){
		$this->id = $row['id'];
		$this->full_name = $row['full_name'];
		$this->username = $row['username'];
		$this->password_hash = $row['password_hash'];
		$this->admin = $row['admin'];
	}
	
	function findByUsername($username, $dbh){
		$stmt = $dbh->prepare( "select * from ".User::$tableName." where username = :username;");
		$stmt->bindParam(':username', $username);
		$stmt->execute();
		
		$this->copyFromRow($stmt->fetch());
	}
	
	function login($password){
		$hasher = new PasswordHash( 8, false );
		return $hasher->CheckPassword( $password, $this->password_hash );
	}
	
	function saveWithPassword($dbh, $password){
		$hasher = new PasswordHash( 8, false );
		$this->password_hash = $hasher->HashPassword( $password );
		
		//check if this is a new object
		if( !$this->id){
			//if so insert
			$stmt = $dbh->prepare( "insert into ".User::$tableName." (username, full_name, password_hash) values (:username, :full_name, :password_hash)");
			$stmt->bindParam(":username", $this->username);
			$stmt->bindParam(":full_name", $this->full_name);
			$stmt->bindParam(":password_hash", $this->password_hash);
			$stmt->execute();
			//and set id
			$this->id = $dbh->lastInsertId();
		} 
			//otherwise update
			//write the update code
		else{
			$stmt = $dbh->prepare( "update ".User::$tableName." set username=:username, full_name=:full_name, password_hash=:password_hash where id=".$this->id);
			$stmt->bindParam(":username", $this->username);
			$stmt->bindParam(":full_name", $this->full_name);
			$stmt->bindParam(":password_hash", $this->password_hash);
			$stmt->execute();
			}
	}
	
}
?>