<?php
class Enemy
{
	# table name
	public static $tableName = "enemies";

	# db column names
	public $id;
	public $priority;
	public $username;
	public $note;

	public $errors;

	function find( $id, $dbh ) {
		$stmt = $dbh->prepare( "select * from ".
								Enemy::$tableName.
								" where id = :id" );
		$stmt->bindParam( ":id", $id );
		$stmt->execute();

		if( $row = $stmt->fetch() ) {
			$this->copyFromRow( $row );
			return true;
		} else {
			return false;
		}
	}

	static function findAll( $dbh ) {
	//Question 2
		$stmt = $dbh->prepare( "select * from ".
								Enemy::$tableName." order by priority" );
		$stmt->execute();

		$result = array();
		while( $row = $stmt->fetch() ) {
			$e = new Enemy();
			$e->copyFromRow( $row );
			$result[] = $e;
		}
		return $result;
	}

	function copyFromRow( $row ) {
		if( isset( $row['id'] ) )
			$this->id = $row['id'];
		$this->username = $row['username'];
		if( isset( $row['note'] ) )
			$this->note = $row['note'];
		//Question 2
		if(isset($row['priority']))
			$this->priority = $row['priority'];
	}

	function validate() {
		$this->errors = array();

		if( !$this->username ) {
			$this->errors['username'] = "Username cannot be blank";
		}
		//Question 3
		if( !$this->priority){
			$this->errors['priority'] = "Priority cannot be blank";
		}
		
		if(ctype_alpha($this->priority)){
			$this->errors['letters'] = "Please don't use letters as a priority, I don't like that.";
		}

		return (count($this->errors) == 0);
	}

	function getError( $field ) {
		if( isset($this->errors[$field]) ) {
			return $this->errors[$field];
		}
		return "";
	}

	function save( $dbh ) {
		if( !$this->id ) {
			$stmt = $dbh->prepare( "insert into ".Enemy::$tableName
				." (username, note, priority) "
				//Question 3
				." VALUES( :username, :note, :priority ) " );
			$stmt->bindParam( ':username', $this->username );
			$stmt->bindParam( ':note', $this->note );
			$stmt->bindParam( ':priority', $this->priority);

			$stmt->execute();
			$this->id = $dbh->lastInsertId();
		}
	}

	function delete( $dbh ) {
		if( $this->id ) {
			$stmt = $dbh->prepare( "delete from ".Enemy::$tableName.
								" where id = :id" );
			$stmt->bindParam( ':id', $this->id );
			$stmt->execute();
		}
	}
}
?>