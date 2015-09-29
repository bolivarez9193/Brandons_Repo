-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Oct 29, 2014 at 09:02 PM
-- Server version: 5.6.20
-- PHP Version: 5.5.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `recipes`
--

-- --------------------------------------------------------

--
-- Table structure for table `ingredients`
--

CREATE TABLE IF NOT EXISTS `ingredients` (
`id` int(11) NOT NULL,
  `name` varchar(45) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `ingredients`
--

INSERT INTO `ingredients` (`id`, `name`) VALUES
(4, 'Beef'),
(2, 'Bread'),
(7, 'Butter'),
(1, 'Cheese'),
(12, 'Condiments'),
(8, 'Green Beans'),
(3, 'Ham'),
(9, 'Hot Pocket'),
(6, 'Pasta'),
(10, 'Salt'),
(5, 'Veggies'),
(11, 'Water');

-- --------------------------------------------------------

--
-- Table structure for table `recipes`
--

CREATE TABLE IF NOT EXISTS `recipes` (
  `ID` int(1) NOT NULL,
  `Name` varchar(64) NOT NULL,
  `Description` varchar(128) NOT NULL,
  `Image` varchar(200) NOT NULL,
  `Prep` varchar(6) NOT NULL,
  `Total` varchar(6) NOT NULL,
  `Rating` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `recipes`
--

INSERT INTO `recipes` (`ID`, `Name`, `Description`, `Image`, `Prep`, `Total`, `Rating`) VALUES
(1, 'Sandwich', 'A very tasty sandwich', 'http://www.grotecompany.com/wp-content/uploads/2009/12/sandwich-production.jpg', '01:35', '05:00', 5),
(2, 'Burger ', 'Burger with beef, buns, tomato, and cheese. ', 'https://upload.wikimedia.org/wikipedia/commons/1/11/Cheeseburger.png', '03:00', '15:00', 5),
(3, 'Mac and Cheese', 'Macaroni pasta with cheese sauce.', 'http://eatathomecooks.com/wp-content/uploads/2009/06/macaroni-and-cheese-done-1024x680.jpg', '04:00', '30:00', 5),
(4, 'Green Beans ', 'Some beans and they''re green! ', 'http://pad3.whstatic.com/images/thumb/b/b4/Freeze-Green-Beans-Step-23.jpg/670px-Freeze-Green-Beans-Step-23.jpg', '01:00', '20:00', 2),
(5, 'Hot Pockets', 'A sandwich that can be made in the microwave.', 'http://jessienextdoor.com/wp-content/uploads/2012/01/hotpockets1.jpg', '00:30', '03:00', 3);

-- --------------------------------------------------------

--
-- Table structure for table `recipe_ingredients_units`
--

CREATE TABLE IF NOT EXISTS `recipe_ingredients_units` (
  `recipe_id` int(11) NOT NULL,
  `ingredient_id` int(11) NOT NULL,
  `unit_id` int(11) DEFAULT NULL,
  `amount` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `recipe_ingredients_units`
--

INSERT INTO `recipe_ingredients_units` (`recipe_id`, `ingredient_id`, `unit_id`, `amount`) VALUES
(1, 1, 5, 1),
(1, 2, 5, 2),
(1, 3, 5, 2),
(1, 5, 5, 3),
(1, 12, 2, 2),
(2, 1, 5, 1),
(2, 2, 5, 2),
(2, 4, 5, 1),
(2, 5, 5, 3),
(2, 10, 4, 1),
(2, 12, 2, 1),
(3, 1, 1, 1),
(3, 6, 1, 3),
(3, 7, 3, 1),
(3, 11, 1, 2),
(4, 8, 1, 3),
(4, 7, 3, 1),
(4, 11, 1, 2),
(4, 10, 4, 1),
(5, 9, 6, 1),
(5, 1, 5, 1),
(5, 3, 5, 2);

-- --------------------------------------------------------

--
-- Table structure for table `steps`
--

CREATE TABLE IF NOT EXISTS `steps` (
`id` int(11) NOT NULL,
  `recipe_id` int(11) NOT NULL,
  `stepno` int(11) NOT NULL,
  `text` varchar(1024) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Dumping data for table `steps`
--

INSERT INTO `steps` (`id`, `recipe_id`, `stepno`, `text`) VALUES
(1, 1, 1, 'Get bread.'),
(2, 1, 2, 'Get middle ingredients.'),
(3, 1, 3, 'Put it together.'),
(4, 2, 1, 'Cook Meat.'),
(5, 2, 2, 'Get ingredients.'),
(6, 2, 3, 'Put it together.'),
(7, 3, 1, 'Boil pasta'),
(8, 3, 2, 'Heat Cheese'),
(9, 3, 3, 'Stir baby!'),
(10, 4, 1, 'Get Beans.'),
(11, 4, 2, 'Cook beans.'),
(12, 4, 3, 'Put Butter.'),
(13, 5, 1, 'Open Package.'),
(14, 5, 2, 'Cook Hot Pocket'),
(15, 5, 3, 'Enjoy!');

-- --------------------------------------------------------

--
-- Table structure for table `units_of_measure`
--

CREATE TABLE IF NOT EXISTS `units_of_measure` (
`id` int(11) NOT NULL,
  `unit_name` varchar(20) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `units_of_measure`
--

INSERT INTO `units_of_measure` (`id`, `unit_name`) VALUES
(1, 'Cups'),
(6, 'Pack'),
(4, 'Pinch'),
(5, 'Slice'),
(3, 'Tablespoons'),
(2, 'Teaspoons');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ingredients`
--
ALTER TABLE `ingredients`
 ADD PRIMARY KEY (`id`), ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `recipes`
--
ALTER TABLE `recipes`
 ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `recipe_ingredients_units`
--
ALTER TABLE `recipe_ingredients_units`
 ADD UNIQUE KEY `recipe_id` (`recipe_id`,`ingredient_id`,`unit_id`), ADD KEY `ingredient_id` (`ingredient_id`), ADD KEY `unit_id` (`unit_id`);

--
-- Indexes for table `steps`
--
ALTER TABLE `steps`
 ADD PRIMARY KEY (`id`), ADD KEY `recipe_id` (`recipe_id`);

--
-- Indexes for table `units_of_measure`
--
ALTER TABLE `units_of_measure`
 ADD PRIMARY KEY (`id`), ADD UNIQUE KEY `name` (`unit_name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `ingredients`
--
ALTER TABLE `ingredients`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=13;
--
-- AUTO_INCREMENT for table `steps`
--
ALTER TABLE `steps`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=16;
--
-- AUTO_INCREMENT for table `units_of_measure`
--
ALTER TABLE `units_of_measure`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=7;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `recipe_ingredients_units`
--
ALTER TABLE `recipe_ingredients_units`
ADD CONSTRAINT `recipe_ingredients_units_ibfk_1` FOREIGN KEY (`recipe_id`) REFERENCES `recipes` (`ID`),
ADD CONSTRAINT `recipe_ingredients_units_ibfk_2` FOREIGN KEY (`ingredient_id`) REFERENCES `ingredients` (`id`),
ADD CONSTRAINT `recipe_ingredients_units_ibfk_3` FOREIGN KEY (`unit_id`) REFERENCES `units_of_measure` (`id`);

--
-- Constraints for table `steps`
--
ALTER TABLE `steps`
ADD CONSTRAINT `steps_ibfk_1` FOREIGN KEY (`recipe_id`) REFERENCES `recipes` (`ID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
