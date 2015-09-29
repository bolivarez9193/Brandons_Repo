-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Oct 20, 2014 at 02:12 AM
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
(2, 'Burger', 'Burger with beef, buns, tomato, and cheese', 'https://upload.wikimedia.org/wikipedia/commons/1/11/Cheeseburger.png', '03:00', '15:00', 5),
(3, 'Mac and Cheese', 'Macaroni pasta with cheese sauce.', 'http://eatathomecooks.com/wp-content/uploads/2009/06/macaroni-and-cheese-done-1024x680.jpg', '04:00', '30:00', 5),
(4, 'Green Beans', 'Some beans and they''re green!', 'http://pad3.whstatic.com/images/thumb/b/b4/Freeze-Green-Beans-Step-23.jpg/670px-Freeze-Green-Beans-Step-23.jpg', '01:00', '20:00', 2),
(5, 'Hot Pockets', 'A sandwich that can be made in the microwave.', 'http://jessienextdoor.com/wp-content/uploads/2012/01/hotpockets1.jpg', '00:30', '03:00', 3);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `recipes`
--
ALTER TABLE `recipes`
 ADD PRIMARY KEY (`ID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
