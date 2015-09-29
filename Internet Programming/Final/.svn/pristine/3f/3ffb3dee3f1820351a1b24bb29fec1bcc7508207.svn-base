function editOn() {
	elt = $("<input type='text' class='form-control'>");
	elt.val( $(this).text() );
	elt.blur( editOff );

	$(this).text( '' );
	$(this).append( elt );
	$(elt).focus();
	$(this).off( 'click' );
}

function editOff() {
	td = $(this).parent();
	td.text( $(this).val() );
	td.on( 'click', editOn );

	$(this).remove();
}

$(".edit").click( editOn );

//Question 4
$(".del").click( function() {
	var id = this.id;
	$.post("Resolved.php?id="+id, function(data){}, "json");
	return false;
	
});

