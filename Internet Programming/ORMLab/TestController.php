<?php
// a simple test controller for your lab work
// we're not going to bother with a view

// Table Name testing
require_once("models/Recipe.php");

print "Table name is: " . Recipe::$nameTable;

?>
<br>
<?php
// Data Members testing
$newRecipe = new Recipe();

$newRecipe->Name = "Soup";
$newRecipe->ID = 1000;
$newRecipe->Description = "It's Hot";
$newRecipe->Image ="haha no";
$newRecipe->Prep = "10:25";
$newRecipe->Total = "20:00";
$newRecipe->Rating = 5;
print $newRecipe;
?>
<br>
<br>
<?php
// copyFromRow testing
$thisArray = [
				'ID' => 1001,
				'Name' => "Bread",
				'Description' => "It's Soft",
				'Image' => "haha no",
				'Prep' => "00:25",
				'Total' => "05:00",
				'Rating' => 4];
$recipe2 = new Recipe();
$recipe2->copyFromRow($thisArray);
print $recipe2;

?>
<br>
<br>
<?php
// find testing
require_once("models/DB.php");
$recipe3 = new Recipe();
//$recipe3->ID = 1;
$recipe3->find(1, $dbh);
print $recipe3;

?>
<br>
<br>
<?php
// findAll testing
$recipes = Recipe::findAll($dbh, true);
for($i = 0; $i < count($recipes); $i++){
	print $recipes[$i];
	?>
<br>
<br>
<?php
}
?>