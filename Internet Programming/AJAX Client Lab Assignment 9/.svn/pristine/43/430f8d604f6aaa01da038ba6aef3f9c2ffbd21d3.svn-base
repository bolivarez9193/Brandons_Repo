function cool_ingredients_widget(elt){

	elt.append($("<option>").attr("name", "ing[]").attr("value", 0));
	elt.append($("<option>").attr("name", "ing[]").attr("value", 0).text("Add new... "));	
	elt.append($("<option>").attr("name", "ing[]").attr("value", 17).text("chicken"));
	elt.append($("<option>").attr("name", "ing[]").attr("value", 16).text("broccoli"));
	
	
	$.getJSON("http://localhost/AJAX%20Client%20Lab/test_controller.php/GetIngredients", function(obj)
	{
		//$.each(obj,function(){
			//elt.append($("<option>").attr("name", "ing[]").attr("value", key).text(x));
		//});
		console.log(obj);
	});
	
	elt.change(function(data){
		console.log(elt.val());
	});
	
}