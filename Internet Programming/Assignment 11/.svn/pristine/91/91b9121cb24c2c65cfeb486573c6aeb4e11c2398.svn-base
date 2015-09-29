
$("form").submit(function() {
	title = $("#title").val()
	body = $("#body").val()
	
	
	$.post("http://localhost/Assignment%2011/New_post.php",
			{ "title" : title, "body" : body },
			function(data){
					$("#title").val("")
					$("#body").val("")
			}, "json");

	return false;
})
