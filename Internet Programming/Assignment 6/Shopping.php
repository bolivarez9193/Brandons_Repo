<?php
// include the data file to fake database data
require_once("data.php");

// check if any form data was sent
$error = false;

if($_POST) {

	// debugging the form output, so you can see what was sent
	print( "There was a post!<br/>");

	print_r($_POST);
	print("<br/>");

	// check to see if the user checked any checkboxes
	if( isset($_POST['item_id']) ) {
		print( "There is at least one item!<br/>");

		print_r($_POST['item_id']);
		print("<br/>");

		// calculate total price (should be in a model, but we don't have one yet)
		$price = 0;
		
		foreach($_POST['item_id'] as $value){
			for($i=0;$i<3;$i++){
				if($value==$items[$i]['id']){
					$price=$price+$items[$i]['price'];
					}
			}
		}
		
		// include the confirm page
		require_once("view_confirm.php");
		die();
	}
	else if(!isset($_POST['item_id'])){
		$error=true;
	}

} else {
	print( "No post for you!<br/>");
}

// include the view items page
require_once("view_items.php");
?>
