<?php 
# set up empty object if necessary, so error display code below can expect it
if(!isset($add_enemy)) { $add_enemy = new Enemy(); }
?>
<html>

<?php
	require_once dirname(__FILE__) . '/../TheList.php';
?>

<head>
	<link rel="stylesheet" href="http://netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css">
	<link rel="stylesheet" href="views/main.css">
</head>

<body>

<div class="container">

<div class="page-header">
	<h1>The List</h1>
</div>

<p id="doomed"><?=$doomed?> have been deleted!</p>
	
<table class="table">
	<tr>
		<th class="col-sm-1">Priority</th>
		<th class="col-sm-3">Name</th>
		<th class="col-sm-8">Justified!</th>
	</tr>
	
<?php
	//Question 1
	for($i = 0; $i < count($enemies); $i++){
?>
	<tr>
		<td>
			<button class="btn btn-xs del" id="<?=$enemies[$i]->id?>">X</button>
			<?=$enemies[$i]->priority?>
		</td>
		<td><?=$enemies[$i]->username?></td>
		<td class="edit"><?=$enemies[$i]->note?>-></td>
	</tr>
<?php
} 
?>

	<form action="AddEnemy.php" method="POST">

	<tr>
		<td>
			<input class="form-control" type="text" name="priority" 
			value="<?=$add_enemy->priority?>" placeholder="#">
		</td>
		<td>
			<input class="form-control" type="text" name="username" 
			value="<?=$add_enemy->username?>" placeholder="name">
		</td>
		<td>
			<input class="form-control" type="text" name="note"
			value="<?=$add_enemy->note?>" placeholder="why?">
		</td>
	</tr>

	<tr>
		<td colspan="3">
			<div class="error"><?=$add_enemy->getError('username')?></div>
			<div class="error"><?=$add_enemy->getError('priority')?></div>
			<div class="error"><?=$add_enemy->getError('letters')?></div>
			<button class="btn btn-primary">You're on the List</button>
		</td>
	</tr>

	</form>

</table>

</div>

<script src="http://code.jquery.com/jquery-1.10.2.min.js"></script>
<script src="views/thelist.js"></script>

</body>
</html>
