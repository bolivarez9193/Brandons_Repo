<?php
class RecipeDetails{
	
	# data columns
	public $recipe_id;
	public $ingredient_id;
	public $unit_id;
	public $amount;
	public $name;
	public $unit_name;
	
	function copyFromRow( $row ) {
		$this->recipe_id = $row['recipe_id'];
		$this->ingredient_id = $row['ingredient_id'];
		$this->unit_id = $row['unit_id'];
		$this->amount = $row['amount'];
		$this->name = $row['name'];
		$this->unit_name = $row['unit_name'];
	}
	
	function __toString(){
		return $this->name."  ".$this->amount." ".$this->unit_name;
	}
	
	# static function to get more than one result, returns an array of RecipeStep objects
	
	static function findAllForRecipe( $recipe_id, $dbh ){
		$stmt = $dbh->prepare( "select * from recipe_ingredients_units riu, ingredients i, units_of_measure u
		where recipe_id = :recipe_id and riu.ingredient_id = i.id and u.id = riu.unit_id");
		$stmt->bindParam(":recipe_id", $recipe_id);
		$stmt->execute();
		
		$result = array();
		while($row = $stmt->fetch()){
			$rd = new RecipeDetails();
			$rd->copyFromRow($row);
			$result[]=$rd;
		}
		return $result;
	}
}
?>