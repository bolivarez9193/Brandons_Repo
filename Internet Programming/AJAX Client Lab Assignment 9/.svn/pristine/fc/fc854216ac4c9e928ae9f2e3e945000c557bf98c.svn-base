<?php

if( isset($_SERVER['PATH_INFO'])){
	$fn = substr($_SERVER['PATH_INFO'], 1);
	
}
echo json_encode($fn());

function GetIngredients(){
	require_once("models/Ingredient.php");
	$ingredients = Ingredient::findAll($dbh, true);
	return json_encode($ingredients);
}

function InsertIngredient(){
	require_once("models/Ingredient.php");
	$newIngredient = new Ingredient();
	$name = $_POST["name"];
	Ingredient::insert($dbh, $name);
	$newIngredient->find($dbh, $name);
	return json_encode($newIngredient);
}

?>