/*********************************************************************
** Program Name: menu
** Author: Jacob Leno
** Date: 10/20/17
** Description: Header file for the menu() function
*********************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include "checkNum.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::showpoint;
using std::setprecision;

#ifndef MENU_HPP
#define MENU_HPP

int intMenu(std::string question, bool isYorN = false, int maxSize = 200000000, int minSize = 1, \
	 bool isHeading = false, std::string heading = "");

double decMenu(std::string question, double maxSize = 100000000000000.0, double minSize = 0.0, int precision = 1);

#endif