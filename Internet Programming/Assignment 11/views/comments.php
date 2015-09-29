<html>

<head>
  
<title><?=$post->title?></title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css">
</head>
<!-- Exact code I got from the post view -->
<nav class="navbar navbar-default" role="navigation">
   <div class="navbar-header">
      <a class="navbar-brand" href="http://localhost/Assignment%2011/Posts.php">Blog Posts</a>
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

<body>

<div class="row col-md-8 col-md-offset-2">

<div class="page-header">

	<h1><?=$post->title?> <small>by:<?=$postAuthor->username?>, <?=$post->create_time?></small></h1>
	
</div>

  <p><?=$post->body?></p>
  
  <hr/>
  <p></p>
 
  
  <!--A majority of this I got from the comment board assignment-->
  <?php if($user->id){?>
	<div class="panel panel-default">
		<div class="panel-heading">
			<h2 class="panel-title">Add a comment</h2>
		</div>

		<div class="panel-body">
			<form>
				<div class="form-group">
					<input type="textbox" id="name" class="form-control" placeholder="Name"/>
				</div>
				<div class="form-group">
					<textarea rows="4" cols="60" id="comment" class="form-control" placeholder="Comment"></textarea>
				</div>
				<div class="form-group">
					<button class="btn btn-primary" id="submit">Post</button>
				</div>
			</form>
		</div>
	</div>
	<?php } ?>
	  <p></p>
	  <?php if($post->numberOfComments > 1){?>
	 <p><?=$post->numberOfComments?> Comments</p>
	 <?php }  else if($post->numberOfComments == 1){?>
	  <p><?=$post->numberOfComments?> Comment</p>
	  <?php } else if($post->numberOfComments == 0){ ?>
	   <p>No Comments</p>
	   <?php } ?>
	 <br></br>
<div id="commentSection">
<?php
 for($i = 0; $i<count($post->comments); $i++){
 
	for($j = 0; $j < count($users); $j++){
			if($users[$j]->id == $post->comments[$i]->author_id){
				echo $users[$j]->username;
			}
	}
	
?>
	<p><?=$post->comments[$i]->body?></p>
<?php
}
?>

</div>
<script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="http://localhost/Assignment%2011/views/comments.js"></script>
</body>

</html>
