<?php
require_once("models/RecipeStep.php");
require_once("models/RecipeDetails.php");

class Recipe{

	public static $nameTable = "Recipes";
	
	# db columns
	public $ID;
	public $Name;
	public $Description;
	public $Image;
	public $Prep;
	public $Total;
	public $Rating;
	
	# non-db data
	public $recipe_steps;
	public $recipe_details;
	
	function copyFromRow( $row ){
		$this->ID = $row['ID'];
		$this->Name = $row['Name'];
		$this->Description = $row['Description'];
		$this->Image = $row['Image'];
		$this->Prep = $row['Prep'];
		$this->Total = $row['Total'];
		$this->Rating = $row['Rating'];
	}
	
	function getRecipeSteps($dbh){
		$this->recipe_steps = RecipeStep::findAllForRecipe($this->ID, $dbh);
	}
	
	function getRecipeDetails($dbh){
		$this->recipe_details = RecipeDetails::findAllForRecipe($this->ID, $dbh);
	}
	
	function find( $ID, $dbh, $withSteps=false ){
		$stmt = $dbh->prepare( "select * from ".Recipe::$nameTable." where ID = :ID;" );
		$stmt->bindParam(":ID", $ID);
		$stmt->execute();
		
		$row = $stmt->fetch();
		$r = new Recipe();
		$r->copyFromRow( $row );
	
		if($withSteps){
			$r->getRecipeSteps($dbh);
			$r->getRecipeDetails($dbh);
		}
		return $r;
	}
	
	static function findAll( $dbh, $sortKey, $fieldKey, $withSteps=false ) {
		$stmt = $dbh->prepare( "SELECT * FROM ".Recipe::$nameTable." ORDER BY ".$fieldKey." ".$sortKey );
		$stmt->execute();
		
		$result = array();
		while( $row = $stmt->fetch() ){
			$r = new Recipe();
			$r->copyFromRow( $row );
			if($withSteps){
			$r->getRecipeSteps($dbh);
			$r->getRecipeDetails($dbh);
			}
			$result[] = $r;
		}
		return $result;
	}
	
	
	static function findByKeyword($dbh, $searchOne, $withSteps=false){
		
		$stmt = $dbh->prepare( "SELECT * FROM ".Recipe::$nameTable." WHERE Name LIKE '%".$searchOne."%' AND Description LIKE '%".$searchOne."%'" );
		$stmt->execute();
		
		$newResult = array();
		while( $row = $stmt->fetch() ){
			$r = new Recipe();
			$r->copyFromRow( $row );
			if($withSteps){
			$r->getRecipeSteps($dbh);
			}
			$newResult[] = $r;
		}
		return $newResult;
	}
	
	function __toString()
	{
		return $this->Name."<br>".$this->ID."<br>".$this->Description."<br>".$this->Image."<br>".$this->Prep."<br>".$this->Total."<br>".$this->Rating;
	}
}
?>