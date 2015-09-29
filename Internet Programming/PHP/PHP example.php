<html>

<body>

<h1>This is my body</h1>

<?php
print "This is coming from php";
$a = 17;
$b = 23;
print "<p>".$a * $b."</p>";
print "<p>$a</p>";
print "<p>$a*$b</p>";

$numbers = array(3,4,5,6);

print( $numbers[2] );

print "<p></p>";

print_r($numbers);

print "<p></p>";

$numbersNew = [ 0 => 3, 1 => 4, 2 => 5 ];

print_r($numbersNew);

foreach($numbersNew as $n) {
	print("<p>$n</p>");
}

foreach($numbersNew as $k => $v){
	print("<p>$k is the key for $v</p>");
}

?>

<p>Thing thing thing</p>

<ul>
<?php
	$colors = ['red', 'green', 'blue'];
	
	foreach($colors as $color){
?>
		<li><?=$color?></li>
<?php
	}
?>

</ul>
<p></p>

<?php
// fake item data using a php associative array
$items = [
	['id' => 1000,
	 'name' => 'Big Chair',
	 'price' => 56.78,
	 'img' => 'http://smartshopbuy.com/images/HomeDecorations/taylor-big-chair.jpg',
	 'desc' => 'A big, comfy chair. Great for sitting, also laying down if you are very small.'],

	['id' => 1001,
	 'name' => 'Cool Bridge',
	 'price' => 20000.00,
	 'img' => 'http://upload.wikimedia.org/wikipedia/commons/e/e1/Gaoliang_Bridge.JPG',
	 'desc' => 'Slightly used, in great condition. Price does not include shipping.'],

	['id' => 1002,
	 'name' => 'Best Friend',
	 'price' => 12.34,
	 'img' => 'http://animalcontrolphx.com/wp-content/uploads/2013/05/gophers-400.jpg',
	 'desc' => 'Occasionally rabid, but always there for you.']
	]

?>

<?php
	print_r($items[0]['name']);
?>
<p></p>
<?php

for($i=0;$i<count($items);$i++){
	$b=0;
	foreach($items[$i] as $key=>$value){
		$b++;
		echo $key."=".$value;
		if($b<count($items[$i])) echo ",";
	}
	echo "<br>";
}

?>



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
		<input type="checkbox" name="item_id[]" value="1000">
		<img class="thumb" src=<?=$items[$i]['img']?>>
	</td>
	<td><span class="name"><?=$items[$i]['name']?></span> <span class="price">$56.78</span></td>
</tr>
<tr><td colspan="2">A big, comfy chair. Great for sitting, also laying down if you are very small.</td></tr>

<?php
	
}
?>
</table>

<?php

?>

</body>

</html>