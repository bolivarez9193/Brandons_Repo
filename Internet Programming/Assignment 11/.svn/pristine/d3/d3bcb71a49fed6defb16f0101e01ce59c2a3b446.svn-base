<html>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css">

<?php
require_once dirname(__FILE__) . '/../Posts.php';
?>
<head>
  
<title>Blog Posts</title>

<nav class="navbar navbar-default" role="navigation">
   <div class="navbar-header">
      <a class="navbar-brand" href="#">Blog Posts</a>
   </div>
	<p class="navbar-text text-right">Hello <?=$user->username?></p>
	<?php 
		if(!$user->id){
	?>
	<p class="navbar-text text-right"><a href="Login_form.php">login/signup</a></p> 

	<?php 
		} else {
	?>
	<p class="navbar-text text-right"><a href="Log_out.php">log out</a></p> 
	<?php
		}
	?>
</nav>

</head>

<body>
<div class="row col-md-8 col-md-offset-2">
  
<table class="table">
<tr>
	<th>Title</th>
	<th>Author</th>
	<th>Date</th>
	<th>Recent Comment Time</th>
	<th>Comment Author</th>
	<th>Comments</th>
</tr>
 <?php
	for($i = 0; $i < count($posts); $i++){
	//$last = count($posts[$i]->comments)-1;
?>
<tr>
	<td><a href="http://localhost/Assignment%2011/Comment.php?post_id=<?=$posts[$i]->id?>"><?=$posts[$i]->title?></a></td>
	<td><?php
		for($j = 0; $j < count($users); $j++){
			if($users[$j]->id == $posts[$i]->author_id){
				echo $users[$j]->username;
			}
		}
		?></td>
	<td><?=$posts[$i]->create_time?></td>
	<td><?=$posts[$i]->mostRecentCommentTime?></td>
	<td><?php
		for($j = 0; $j < count($users); $j++){
			if($users[$j]->id == $posts[$i]->recentCommenter->author_id){
				echo $users[$j]->username;
			}
		}
		?></td>
	<td><?=$posts[$i]->numberOfComments?></td>
</tr>

<?php
}
?>
</table>


<?php if($user->id){?>
<div class="panel panel-default">
	<div class="panel-heading">
		<h1 class="panel-title">Wanna Post?</h1>
	</div>
	
	<div class="panel-body">
		<form method="POST" action="">
			<div class="form-group">
				<input type="textbox" id="title" name="title" class="form-control" placeholder="Title"/>
			</div>
			<div class="form-group">
				<textarea rows="4" cols="60" id="body" class="form-control" name="body" placeholder="Body"></textarea>
			</div>
			<div class="form-group">
				<button class="btn btn-primary" id="submit">Submit</button>
			</div>
		</form>
	</div>
</div>

<?php } ?>

<script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="http://localhost/Assignment%2011/views/posts.js"></script>
</body>

</html>
