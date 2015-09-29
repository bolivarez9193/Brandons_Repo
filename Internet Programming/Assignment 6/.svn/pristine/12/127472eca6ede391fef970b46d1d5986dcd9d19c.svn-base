<html>

<head>
<title>Incredibly Simple Shopping</title>

<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css">
<link rel="stylesheet" href="main.css">

</head>

<body>

<?php
require_once("data.php");
?>

<div class="container">

<div class="page-header">
	<h1>Buy More!</h1>
</div>

<div class="row col-md-8 col-md-offset-2">

<!-- on button click, POST back to self (controller) -->
<form method="POST" action="">

<table class="table">

<!-- 
	use PHP to generate these table rows based on what is in the $items array.
	pay attention to the name/value attributes!
-->
<?php
for($i=0;$i<count($items);$i++){
	
?>
<tr>
	<td rowspan="2">	
		<input type="checkbox" name="item_id[]" value=<?=$items[$i]['id']?>>
		<img class="thumb" src=<?=$items[$i]['img']?>>
	</td>
	<td><span class="name"><?=$items[$i]['name']?></span> <span class="price"><?="$".$items[$i]['price']?></span></td>
</tr>
<tr><td colspan="2"><?=$items[$i]['desc']?></td></tr>

<?php
	
}
?>
</table>
<!-- 
	notice the button has a name attribute, so that you can tell they POSTed even if they didn't
	select any checkboxes!
-->
<button class="btn btn-primary" name="buy">Buy!</button>

</div>

<?php

if($error){
?>

<div> 
	<p class="error">Hey man you need to check one of these boxes.</p>
	<p class="error">You wanna buy something or not?</p>
</div>

<?php
}
?>

</body>

</html>
