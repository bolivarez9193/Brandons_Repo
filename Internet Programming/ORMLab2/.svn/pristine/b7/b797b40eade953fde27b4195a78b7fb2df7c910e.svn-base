<?php
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
	
	function copyFromRow( $row ){
		$this->ID = $row['ID'];
		$this->Name = $row['Name'];
		$this->Description = $row['Description'];
		$this->Image = $row['Image'];
		$this->Prep = $row['Prep'];
		$this->Total = $row['Total'];
		$this->Rating = $row['Rating'];
	}
	
	function find( $ID, $dbh ){
		$stmt = $dbh->prepare( "select * from ".Recipe::$nameTable." where ID = :ID;" );
		$stmt->bindParam(":ID", $ID);
		$stmt->execute();
		
		$row = $stmt->fetch();
		$this->copyFromRow( $row );
	}
	
	static function findAll( $dbh ) {
		$stmt = $dbh->prepare( "select * from ".Recipe::$nameTable );
		$stmt->execute();
		
		$result = array();
		while( $row = $stmt->fetch() ){
			$r = new Recipe();
			$r->copyFromRow( $row );
			$result[] = $r;
		}
		return $result;
	}
	
	function __toString()
	{
		return $this->Name."<br>".$this->ID."<br>".$this->Description."<br>".$this->Image."<br>".$this->Prep."<br>".$this->Total."<br>".$this->Rating;
	}
}
?>