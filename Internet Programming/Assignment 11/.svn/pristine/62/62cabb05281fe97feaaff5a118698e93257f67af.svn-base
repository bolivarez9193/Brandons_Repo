<?php
require_once("models/Comment.php");
class Post
{
	public static $tableName = "posts";
	
	public $id;
	public $create_time;
	public $author_id;
	public $title;
	public $body;
	
	public $mostRecentCommentTime;
	public $numberOfComments;
	public $recentCommenter;
	
	public $comments = array();
	
	function copyFromRow( $row ){
		$this->id = $row['id'];
		$this->create_time = $row['create_time'];
		$this->author_id = $row['author_id'];
		$this->title = $row['title'];
		$this->body = $row['body'];
	}
	
	function getMostRecentCommentTime($dbh){
		$this->mostRecentCommentTime=Comment::mostRecentCommentTime($this->id, $dbh);
	}
	
	function getNumberOfComments($dbh){
		$this->numberOfComments=Comment::numberOfComments($this->id, $dbh);
	}
	
	function getMostRecentComment($dbh){
		$this->recentCommenter=Comment::mostRecentComment($this->id, $dbh);
	}
	
	function getComments($dbh){
		$this->comments = Comment::get_comments(0, $this->id,$dbh); 
	}
	
	function sortByTime($dbh){
		$stmt = $dbh->prepare( "select * from ".Post::$tableName." order by create_time desc");
		$stmt->execute();
		
		$result = array();
		while($row = $stmt->fetch()){
			$post = new Post();
			$post->copyFromRow($row);
			$post->getMostRecentCommentTime($dbh);
			$post->getNumberOfComments($dbh);
			$post->getMostRecentComment($dbh);
			$result[] = $post;
		}
		return $result;
	}
	
	function add_post($title, $body, $author_id,$dbh) {
		$stmt = $dbh->prepare( "INSERT INTO ".Post::$tableName." (title, body, author_id) VALUES(:title, :body, :author_id)" );
		$stmt->bindParam(":title", $title);
		$stmt->bindParam(":body", $body);
		$stmt->bindParam(":author_id", $author_id);
		$stmt->execute();
	}
	
	function findByID($id, $dbh){
		$stmt = $dbh->prepare( "select * from ".Post::$tableName." where id = :id;");
		$stmt->bindParam(':id', $id);
		$stmt->execute();
		
		$this->copyFromRow($stmt->fetch());
		$this->getMostRecentCommentTime($dbh);
		$this->getNumberOfComments($dbh);
		$this->getMostRecentComment($dbh);
		$this->getComments($dbh);
	}
}
?>