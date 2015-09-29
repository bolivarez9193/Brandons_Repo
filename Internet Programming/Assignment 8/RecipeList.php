<?php
// include models, including the database connection
require_once("models/Recipe.php");
require_once("models/DB.php");

// get querystring data (part 2)
$fieldName='Name';
$sortingTitle='ASC';

//Switching between sorting ASC and DESC

if(isset($_GET['sort'])){
	if($_GET['sort']=='ASC'){
		$sortingTitle='DESC';
	}
	else{
		$sortingTitle='ASC';
	}
}

//Determining whether the field is Name, Prep Time, Total Time, and Rating
if(isset($_GET['field'])){
if($_GET['field']=='Name'){
	$fieldName="Name";
}
else if($_GET['field']=='Prep'){
	$fieldName="Prep";
}
else if($_GET['field']=='Total'){
	$fieldName="Total";
}
else if($_GET['field']=='Rating'){
	$fieldName="Rating";
}
}

// get form data (part 3)

//If user clicks button, this happens
if($_POST){

$searching = $_POST["terms"];
$recipes = Recipe::findByKeyword($dbh, $searching, true);

require_once("views/view_recipes.php");

}
// using the Recipe model, retrieve an array of recipes

//If beginning to look at page, this happens
else {
$recipes = Recipe::findAll($dbh, $sortingTitle, $fieldName, true);

// require the view
require_once("views/view_recipes.php");

}


?>
