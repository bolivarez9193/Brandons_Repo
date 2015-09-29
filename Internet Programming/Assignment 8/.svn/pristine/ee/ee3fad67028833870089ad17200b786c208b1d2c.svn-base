<?php
require_once("models/Recipe.php");
require_once("models/DB.php");

$idOfRecipe = $_GET["ID"];
$recipeItself = Recipe::find( $idOfRecipe, $dbh, true );
$nameOfRecipe = $recipeItself->Name;
require_once("views/view_details.php");
?>