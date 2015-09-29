CREATE TABLE steps
(
  id            INT             NOT NULL AUTO_INCREMENT PRIMARY KEY,
  recipe_id     INT             NOT NULL,
  stepno        INT             NOT NULL,
  text          VARCHAR(1024)   NOT NULL,
  FOREIGN KEY (recipe_id) REFERENCES recipes(id)
);

CREATE TABLE ingredients
(
  id            INT             NOT NULL AUTO_INCREMENT PRIMARY KEY,
  name          VARCHAR(45)     NOT NULL UNIQUE
);

CREATE TABLE units_of_measure
(
  id            INT             NOT NULL AUTO_INCREMENT PRIMARY KEY,
  name          VARCHAR(20)     NOT NULL UNIQUE
);

CREATE TABLE recipe_ingredients_units
(
  recipe_id     INT             NOT NULL,
  ingredient_id INT             NOT NULL,
  unit_id       INT,
  amount        DOUBLE          NOT NULL,
  FOREIGN KEY (recipe_id) REFERENCES recipes(id),
  FOREIGN KEY (ingredient_id) REFERENCES ingredients(id),
  FOREIGN KEY (unit_id) REFERENCES units_of_measure(id),
  UNIQUE(recipe_id,ingredient_id,unit_id)
);
