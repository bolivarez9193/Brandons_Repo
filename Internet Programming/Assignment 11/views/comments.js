var next = 0;

update_comments()

function update_comments(){

	$.ajax({
		'url' : "http://localhost/Assignment%2011/New_comments.php?next="+next,
		'dataType' : 'JSON'
		}).done(function(comments) {
			add_to_section(comments)
			
			if(comments.length > 0){
				next = parseInt(comments[comments.length-1].id)+1
			}
		})
		/*
		$.getJSON("http://localhost/Assignment%2011/New_comments.php?next="+next, function(comments){
			add_to_section(comments)
			
			if(comments.length > 0){
				next = parseInt(comments[comments.length-1].id)+1
		});*/
}

function add_to_section(comments){
	section = $("#commentSection")
	$.each(comments, function(i, comment){
		section.append("<p>"+comment.create_time+"</p>"+"\n")
	})
}