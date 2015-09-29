<html>

<head>
<title>Recipe Details</title>

<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css">
<link rel="stylesheet" href="main.css">

<?php
	require_once dirname(__FILE__) . '/../RecipeDetail.php'
?>
</head>

<body>

<div class="container">

<div class="page-header">
	<h1><?=$nameOfRecipe?> Recipe</h1>
</div>

<div>

	<img id=image src="<?=$recipeItself->Image?>">

</div>

<table class="table">

<tr>

	<th>Name</th>
	<th>Prep Time</th>
	<th>Total Time</th>
	<th>Rating</th>
</tr>

<tr>
	<td><?=$recipeItself->Name?></td>
	<td><?=$recipeItself->Prep?></td>
	<td><?=$recipeItself->Total?></td>
	<td><?=$recipeItself->Rating?></td>
</tr>
</table>

<table class="table">
<tr>
	<th>Ingredient</th>
</tr>
<?php
	for($i=0; $i<count($recipeItself->recipe_details);$i++){
?>
<tr>
	<td><?=$recipeItself->recipe_details[$i]->name?><td>
	<td><?=$recipeItself->recipe_details[$i]->amount?> <?=$recipeItself->recipe_details[$i]->unit_name?></td>
</tr>
<?php
	}
?>
</table>

<table class="table">

<tr>
	<th>Steps</th>
</tr>
<?php 
	for($i=0; $i<count($recipeItself->recipe_steps);$i++){
?>
	<tr>
		<td><?=$recipeItself->recipe_steps[$i]->stepno?>. <?=$recipeItself->recipe_steps[$i]->text?>.</td>
	</tr>
<?php 
	}
?>
</table>

	<p><a href="RecipeList.php">Go back to recipes.</a></p>
	
</body>

</div>

</html>