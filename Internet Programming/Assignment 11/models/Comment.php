<?php
class Comment
{
	public static $tableName = "comments";
	
	public $id;
	public $create_time;
	public $post_id;
	public $author_id;
	public $body;
	public $reply_to_id;
	
	function copyFromRow( $row ){
		$this->id = $row['id'];
		$this->create_time = $row['create_time'];
		$this->post_id = $row['post_id'];
		$this->author_id = $row['author_id'];
		$this->body = $row['body'];
		$this->reply_to_id = $row['reply_to_id'];
	}
	
	function findAllForPost($post_id, $dbh){
		$stmt = $dbh->prepare( "select * from ".Comment::$tableName." where post_id = :post_id");
		$stmt->bindParam(":post_id", $post_id);
		$stmt->execute();
		
		$result = array();
		while($row = $stmt->fetch()){
			$c = new Comment();
			$c->copyFromRow($row);
			$result[]=$c;
		}
		return $result;
	}
	
	function mostRecentCommentTime($post_id, $dbh){
		$stmt = $dbh->prepare( "select max(create_time) from ".Comment::$tableName." where post_id = :post_id");
		$stmt->bindParam(":post_id", $post_id);
		$stmt->execute();
		
		$row = $stmt->fetch();
		return $row["max(create_time)"];
		
	}
	function numberOfComments($post_id, $dbh){
		$stmt = $dbh->prepare( "select count(id) from ".Comment::$tableName." where post_id = :post_id");
		$stmt->bindParam(":post_id", $post_id);
		$stmt->execute();
		
		$row = $stmt->fetch();
		return $row["count(id)"];
	}
	
	function mostRecentComment($post_id, $dbh){
		$stmt = $dbh->prepare( "select *, max(create_time) from ".Comment::$tableName." where post_id = :post_id");
		$stmt->bindParam(":post_id", $post_id);
		$stmt->execute();
		
		$row = $stmt->fetch();
		$c = new Comment();
		$c->copyFromRow($row);
		return $c;
	}
	
	//This is based on the polling lab that we did
	function get_comments($next, $post_id, $dbh) {
	$stmt = $dbh->prepare( "SELECT * FROM comments WHERE id >= :next AND post_id = :post_id ORDER BY id DESC" );
	$stmt->bindParam(":next", $next);
	$stmt->bindParam(":post_id", $post_id);
	$stmt->execute();
	
	$result = array();
		while($row = $stmt->fetch()){
			$comment = new Comment();
			$comment->copyFromRow($row);
			$result[] = $comment;
		}
		return $result;
	}
	
	function add_comment($user, $text, $dbh) {
		$stmt = $dbh->prepare( "INSERT INTO ".Comment::$tableName." (username, text) VALUES(:user, :text)" );
		$stmt->bindParam(":user", $user);
		$stmt->bindParam(":text", $text);
		$stmt->execute();
}
	
}
?>