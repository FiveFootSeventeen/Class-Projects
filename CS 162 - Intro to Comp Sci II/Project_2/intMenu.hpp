/*********************************************************************
** Program Name: IntMenu
** Author: Jacob Leno
** Date:10/04/17
** Description: Header file for the intMenu function
*********************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <string>

int intMenu(std::string question, bool isYorN = false, int maxSize = 200000000, int minSize = 1, \
	 bool isHeading = false, std::string heading = "");

#endif