<?php
class RecipeStep{
	# class reflects a db table
	public static $nameTable = "steps";
	
	# data columns
	public $id;
	public $recipe_id;
	public $stepno;
	public $text;
	
	function copyFromRow( $row ) {
		$this->id = $row['id'];
		$this->recipe_id = $row['recipe_id'];
		$this->stepno = $row['stepno'];
		$this->text = $row['text'];
	}
	
	function __toString(){
		return $this->stepno."  ".$this->text;
	}
	
	#inflation - making this object match a db row
	function find( $id, $dbh ){
		$stmt = $dbh->prepare( "select * from ".RecipeStep::$nameTable." where id = :id;" );
		
		$stmt->bindParam(':id', $id);
		$stmt->execute();
		
		$row = $stmt->fetch();
		$this->copyFromRow($row);
	}
	
	# static function to get more than one result, returns an array of RecipeStep objects
	
	static function findAll($dbh){
		$stmt = $dbh->prepare("select * from ".RecipeStep::$nameTable );
		$stmt->execute();
		
		$result = array();
		while( $row = $stmt->fetch()){
			$rs = new RecipeStep();
			$rs->copyFromRow($row);
			$result[] = $rs;
		}
		return $result;
	}
	
	# static function to get more than one result, returns an array of RecipeStep objects
	
	static function findAllForRecipe( $recipe_id, $dbh ){
		$stmt = $dbh->prepare( "select * from ".RecipeStep::$nameTable." where recipe_id = :recipe_id");
		$stmt->bindParam(":recipe_id", $recipe_id);
		$stmt->execute();
		
		$result = array();
		while($row = $stmt->fetch()){
			$rs = new RecipeStep();
			$rs->copyFromRow($row);
			$result[]=$rs;
		}
		return $result;
	}
}
?>