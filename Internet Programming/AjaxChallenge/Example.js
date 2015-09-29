$("#Button1").click(function(){
	$( "#newDiv" ).load( "Example1.html #paragraph" );
});

$("#Button2").click(function(){
	$("#newDiv").load("Example2.html #image");
});
