// turn all the "some text" red
function turn_red()
{
	$(".words").css( "color", "red" );
}

// set textbox value (try call from console)
function magic()
{
	$("#benny").val( "Magic!" );
}

// select the third option in the select box
function make_selection()
{
	$("#mysel").val(3);
}

// on click of the button, turn the second one blue
// (uses an anonymous function)
$("#btn").click( function()
	{
		$(".words").eq(1).css( "color", "blue" );
	} );

// do on load
turn_red();
// could also run when document is done with:
// $(turn_red);

//let's make a date variable

var d = new Date("5,24,2011");
var day = d.getDate();
var month = d.getMonth() + 1;
var year = d.getFullYear();
document.write("<b>" + month + "/" + day + "/" + year + "</b>");
document.write("<p> </p>"); 
day = day + 5;
document.write("<b>" + year + "/" + month + "/" + day + "</b>");


