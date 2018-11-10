/*
*********************************************************************
** Title: CS 340 Hardware Store Database
** Author: Jacob Leno
** Date: 03/16/18
*********************************************************************
*/

DROP TABLE IF EXISTS `customer`;

CREATE TABLE `customer`(
	`id` INT(11) PRIMARY KEY AUTO_INCREMENT,
	`custName` varchar(80) NOT NULL,
	`custAddress` varchar(80) DEFAULT NULL,
	`custPhoneNumber` varchar(80) DEFAULT NULL,
	`custEmail` varchar(80) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `customer`(`id`, `custName`,`custAddress`,`custPhoneNumber`, `custEmail`) values 

(1, 'Thomas Shealtiel', '123 6th St.', '(555) 605-9430', ''),
(2, 'Sally Dorthy', '4 Goldfield Rd.', '(555) 168-2717', 'webdragon@comcast.net'),
(3, 'Wanda Walsh', '71 Pilgrim Avenue', '(555) 384-4631', 'wwalsh@icloud.com'),
(4, 'Edgar Beck', '44 Shirley Ave. ', '(555) 587-7519', ''),
(5, 'Cody Shaw ', '70 Bowman St.', '(555) 569-0082', ''),
(6, 'Rosalie Norton', '', '', ''),
(7, 'Velma Morton', '514 S. Magnolia St.', '(555) 913-7478', 'vmorton@gmail.com'),
(8, 'Peggy Boone', '502 Ketch Harbour Drive ', '(555) 316-0103', ''),
(9, 'Mike Gross ', '957 Willow Street ', '(555) 582-7877', ''),
(10, 'Dwayne Wilkins', '676 53rd Road ', '(555) 302-4238', 'dwilkins@outlook.com'),
(11, 'Sonia Rose ', '72 E. Halifax Street ', '(555) 479-4012', ''),
(12, 'Chris Nguyen', '8003 Bear Hill Lane', '(555) 121-4593', ''),
(13, 'Kristina Quinn', '187 South Cambridge Lane', '(555) 631-8505', ''),
(14, 'Freddie Parker', '9804 Adams Lane', '(555) 618-1561', ''),
(15, 'Toby Frazier', '768 Pierce St. ', '(555) 347-3421', '');

DROP TABLE IF EXISTS `employee`;

CREATE TABLE `employee`(
	`id` INT(11) PRIMARY KEY AUTO_INCREMENT,
	`empName` varchar(80) NOT NULL,
	`empAddress` varchar(80) NOT NULL,
	`empPhoneNumber` varchar(80) NOT NULL,
	`empEmail` varchar(80) DEFAULT NULL,
	`hourlyRate` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `employee`(`id`, `empName`,`empAddress`,`empPhoneNumber`, `empEmail`, `hourlyRate`) values 

(1, 'Nathan Mcilvaine', '670 Church Street', '(555) 588-3240', 'nmcilvaine@outlook.com', 12.5),
(2, 'Keena Connally', '273 Golden Star Circle', '(555) 809-6223', '', 12.5),
(3, 'Douglas Douglas', '225 Tower Lane', '(555) 205-8102', 'dougdoug@gmail.com', 18.5),
(4, 'Jana Massey', '661 Trout Dr.', '(555) 601-2172', '', 20),
(5, 'Carrie Willis', '446 Riverside St. ', '(555) 643-6499', '', 18.5),
(6, 'Alfred Price', '242 Hill Field Road', '(555) 865-3391', '', 30),
(7, 'Jean Luna', '445 Homewood Street ', '(555) 373-0856', '', 12.5),
(8, 'Nichole Joseph', '94 Queen St.', '(555) 377-7958', '', 30),
(9, 'Jeff Oliver', '471 West Hartford St.', '(555) 408-5497', 'joliver@icloud.com', 30),
(10, 'Miguel Burton', '72 Hillside Court', '(555) 656-5753', '', 20),
(11, 'Wilfred Osborne', '7933 3rd St.', '(555) 217-4267', '', 22.5),
(12, 'Andres Cummings', '7623 Carriage Road', '(555) 471-7651', '', 40),
(13, 'Michael Jones', '8861 South Union Ave.', '(555) 419-1721', 'mjones@gmail.com', 20.5),
(14, 'Leo Boyd', '638 Swanson St.', '(555) 128-1533', '', 17.5),
(15, 'Alicia Cook', '9248 North 6th St.', '(555) 361-5295', '', 15.5);

DROP TABLE IF EXISTS `transactions`;

CREATE TABLE `transactions`(
	`id` INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,
	`fkCustomerID` INT(11) NOT NULL,
	`fkEmpID` INT(11) NOT NULL,
	`totalPrice` decimal(10,2) NOT NULL,
	`transactionDate` date DEFAULT NULL,
	FOREIGN KEY (`fkCustomerID`) REFERENCES `customer` (`id`),
	FOREIGN KEY (`fkEmpID`) REFERENCES `employee` (`id`) 
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `transactions`(`id`, `fkCustomerID`, `fkEmpID`, `totalPrice`, `transactionDate`) values 
(1, 1, 1, 121.69, '2014-05-29'),
(2, 1, 2, 289.99, '2014-07-02'),
(3, 2, 2, 549.00, '2014-09-17'),
(4, 3, 5, 278.99, '2014-11-17'),
(5, 4, 1, 390.44, '2015-01-29'),
(6, 5, 14, 20.00, '2015-08-06'),
(7, 6, 14, 75.15, '2015-08-14'),
(8, 7, 1, 4.95, '2015-12-07'),
(9, 8, 5, 4997.95, '2015-12-07'),
(10, 8, 2, 39.95, '2016-02-10'),
(11, 9, 2, 45.95, '2016-06-18'),
(12, 10, 5, 20.00, '2016-09-26'),
(13, 10, 1, 299.99, '2016-11-26'),
(14, 11, 14, 93.74, '2017-04-18'),
(15, 12, 14, 508.90, '2017-05-03'),
(16, 13, 14, 35.20, '2017-06-12'),
(17, 14, 5, 549.00, '2017-12-08'),
(18, 15, 2, 27.95, '2018-05-12'),
(19, 15, 1, 99.69, '2018-05-25'),
(20, 15, 1, 569.94, '2018-08-27');


DROP TABLE IF EXISTS `department`;

CREATE TABLE `department`(
	`id` INT(11) PRIMARY KEY AUTO_INCREMENT,
	`fkEmpID` INT(11) NOT NULL,
	`name` varchar(80) NOT NULL,
	`totalSales` decimal(10,2) DEFAULT NULL,
	`yearlyGoal` decimal(10,2) DEFAULT NULL,
	FOREIGN KEY (`fkEmpID`) REFERENCES `employee` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `department`(`id`, `fkEmpID`, `name`, `totalSales`,`yearlyGoal`) values 

(1, 12, 'Paint', 12723.80, 15000),
(2, 4,  'Electrical',23481.71, 20000),
(3, 6, 'Hardware', 18301.23, 30000),
(4, 8, 'Lawn and Garden', 10379.09, 15000),
(5, 9, 'Plumbing', 14038.51, 20000),
(6, 3, 'Tools', 35239.72, 40000);



DROP TABLE IF EXISTS `product`;

CREATE TABLE `product`(
	`id` INT(11) PRIMARY KEY AUTO_INCREMENT,
	`fkDepartmentID` INT(11) NOT NULL,
	`productName` varchar(80) NOT NULL,
	`description` varchar(255) DEFAULT NULL,
	`price` decimal(10,2) NOT NULL,
	`stock` INT(11) DEFAULT NULL,
	FOREIGN KEY (`fkDepartmentID`) REFERENCES `department` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `product`(`id`, `fkDepartmentID`,`productName`,`description`, `price`, `stock`) values 

(1, 1, 'Ultra Pure White Satin Enamel Exterior Paint', ' This exciting product, featuring Nanoguard technology, provides an extra-protective shell that guards against damage from sunlight, moisture, stains and dirt.', 35.20, 10),
(2, 1, 'Bright Cornflower Blue Satin Interior Paint with Primer', 'Protects and beautifies just about any room in your home, including basements and high-traffic areas.', 27.95, 5),
(3, 1, 'Epoxy Concrete and Garage Floor Paint', 'High-performance, ready-to-use, water-based floor paint that resists tire marks and marring', 39.95, 7),
(4, 2, '250 ft. 14/2 Gray Solid Wire', 'Used in applications that include outside lamp posts, pumps and other loads. It can also be used for outbuildings such as garages and barns.', 93.74, 10),
(5, 2, '60-Watt Equivalent Non-Dimmable LED Light Bulb', 'The bulb is designed for indoor use and features an A-line shape and medium base. ', 4.95, 5),
(6, 2, '4-in-1 Home Security Kit', 'HD camera, smoke detector, motion detector and 90 DB siren in 1 sensor, security app allows user to call police, dismiss alarm, sound siren and more', 299.99, 4),
(7, 3, '#9 x 3 in. Star Wood Deck Screws', 'A lifetime polymer coating provides extra corrosion resistance that is guaranteed for the life of your outdoor projec', 5.95, 16),
(8, 3, 'Satin Nickel Smart Lock with Alarm', 'Combines advanced features and compatibility with your home automation system, allowing you to control your home from anywhere and freeing you from the hassles of keys.', 249.99, 6),
(9, 3, '1/2 in. x 100 ft. Heavy Duty Rope', 'This general purpose rope is flexible and lightweight, rot proof, resists oil, water, gasoline and most chemicals.', 20.00, 10),
(10, 4, '50 Gal. Rain Barrel with Brass Spigot', 'Oak barrel texture is molded into each barrel and will not fade, rot or risk insect infestation.', 90.49, 3),
(11, 4, '2-Burner Propane Gas Grill', 'Two durable stainless steel burners and two stainless steel tables that fold down for easy maneuverability and storage.', 299.95, 4),
(12, 4, '5-Piece Padded Patio Dining Set', 'Durable with rust-resistant steel frames powder-coated in pewter, the set includes four swivel motion chairs with UV resistant material', 388.95, 2),
(13, 5, 'Heavy-Duty 100 Gal. 270,000 BTU Natural Gas Water Heater', 'Designed to fit into tight retrofit applications. This model requires a 120-Volt power source.', 4997.95, 3),
(14, 5, '6-Station Easy-Set Logic Indoor/Outdoor Sprinkler Timer', '6-Station Sprinkler Timer features Easy-Set programming logic and a large LCD and dial to make programming your watering system easy.', 39.95, 15),
(15, 5, '1 HP Shallow Well Jet Pump', '1 HP durable, cast iron shallow well jet pump packaged with a comprehensive installation manual to help anyone build a safe and long-lasting well pump system.', 278.99, 2),
(16, 6, '20-Volt Lithium-Ion Cordless Compact Drill/Driver', 'It has a slim handle with a contoured, ergonomic grip to provide excellent balance and superb control during use.', 119.95, 5),
(17, 6, '9-Drawer Mobile Workbench with Solid Wood Top', 'Designed to handle rough usage without compromising integrity.', 289.99, 2),
(18, 6, '13 Amp 10 in. Professional Cast Iron Table Saw', '13 Amp motor for speeds up to 3450 RPM. The cast iron tables milled and polished surface minimizes vibration and provides a flat, level surface for trouble-free cutting.', 549.00, 3);


DROP TABLE IF EXISTS `productSold`;

CREATE TABLE `productSold`(
	`productID` INT(11),
	`transactionID` INT(11),
	PRIMARY KEY (`productID`, `transactionID`),
	KEY `productID` (`productID`),
	KEY `transactionID` (`transactionID`),
	CONSTRAINT `productSoldfk1` FOREIGN KEY (`productID`) REFERENCES `product` (`id`),
	CONSTRAINT `productSoldfk2` FOREIGN KEY (`transactionID`) REFERENCES `transactions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert  into `productSold`(`productID`,`transactionID`) values

(2 ,1),
(4 ,1),
(17,2),
(18 ,3),
(15 ,4),
(11 ,5),
(10 ,5),
(9 ,6),
(1 ,7),
(3 ,7),
(5 ,8),
(13 ,9),
(14 ,10),
(7 ,11),
(3 ,11),
(9 ,12),
(6 ,13),
(4 ,14),
(12 ,15),
(16 ,15),
(1 ,16),
(18 ,17),
(2 ,18),
(4 ,19),
(7 ,19),
(11 ,20),
(8 ,20),
(9 ,20);

