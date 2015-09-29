CREATE TABLE users
(
	id				INTEGER			NOT NULL AUTO_INCREMENT PRIMARY KEY,
	username		VARCHAR(64)		NOT NULL,
	password_hash	VARCHAR(128)	NOT NULL,
	full_name		VARCHAR(64)		NOT NULL,
	admin			BOOLEAN			NOT NULL DEFAULT false
);

-- bogus data for testing (unhashed password)
INSERT INTO users (username, password_hash, full_name, admin)
VALUES( 'etomai', '$2a$08$reVmn4QA78tQYpSsRT2DdeY0XoYprqQ7Ei.OH3dKsM6arsY32kEwS', 'Test Guy', true );
