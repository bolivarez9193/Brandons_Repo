<?php isset($user) or die; ?>
<html>

<head>
	<link rel="stylesheet" href="http://netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css">
	<link rel="stylesheet" href="main.css">
</head>

<body>

<div class="container">
<div class="row col-sm-10 col-sm-offset-1">

	<div class="row">
	<div class="page-header">
		<h1>The Awesome Website of Awesome</h1>
		<div>Welcome, <?=$user->username?>! <?php
		if( $user->id ) { ?>(<a href="Logout.php"><em>logout</em></a>)<?php } ?></div>
	</div></div>

<?php if( !$user->admin ) { ?>
	<div class="row">
	<p>You are not an adminstrator. You are a common peasant from the
	internet. You'll get a picture of garbage and like it.</p>

	<img src="http://img.timeinc.net/time/photoessays/2008/naples_garbage/garbage_naples_01.jpg">
	</div>

<?php } else { ?>
	<div class="row">
	<p>You are Awesome. As a reward, here's a picture of a majestic Bengal Tiger.</p>

	<img src="http://wfiles.brothersoft.com/b/bengal-tiger-in-the-water_179286-1920x1200.jpg">
	</div>
<?php } ?>

	<div class="row">
	<p><a href="index.php">Step off, man</a></p>
	</div>

</div>
</div>

</body>
</html>
