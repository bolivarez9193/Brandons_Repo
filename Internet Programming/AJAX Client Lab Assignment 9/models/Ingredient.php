<?php
try{
		$dbh = new PDO( 'mysql:host=localhost;dbname=recipes',
							'bjolivarez', 'insertpassword',
							array( PDO::ATTR_PERSISTENT => true ) );
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}catch( PDOException $e ) {
			print "ERROR: ".$e->getMessage();
}

class Ingredient
{
	# table name
	public static $tableName = "ingredients";

	# db column names
	public $id;
	public $name;

	function copyFromRow( $row ){
		$this->id = $row['id'];
		$this->name = $row['name'];
	}
	
	static function findAll( $dbh, $withSteps=false) {
		$stmt = $dbh->prepare( "select * from ".Ingredient::$tableName." order by id" );
		$stmt->execute();
		
		$result = array();
		while( $row = $stmt->fetch() ){
			$i = new Ingredient();
			$i->copyFromRow( $row );
			$result[] = $i;
		}
		return $result;
	}
	
	function find( $dbh, $name ){
		$stmt = $dbh->prepare( "select * from ".Recipe::$tableName." where name = :name;" );
		$stmt->bindParam(":name", $name);
		$stmt->execute();
		
		$row = $stmt->fetch();
		$this->copyFromRow( $row );
	}
	
	static function insert($dbh, $name){
		$stmt = $dbh->prepare( "insert into ".Ingredient::$tableName." (name) values (:name)");
		$$stmt->bindParam(":name", $name);
		$stmt->execute();
			
		$this->id = $dbh->lastInsertId();
	}
	function __tostring() {
		return "Ingredient ".$this->id." ".$this->name;
	}
}
?>