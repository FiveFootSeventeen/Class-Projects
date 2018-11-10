/*********************************************************************
** Class Name: Space
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the Space
** class.
*********************************************************************/

#include "Space.hpp"
//Space default constructor

Space::Space()
{
	top = nullptr;
	left = nullptr;
	right = nullptr;
	bottom = nullptr;
	spaceMap = nullptr;
}

//Destructor for the Space class
Space::~Space()
{
	if (spaceMap != nullptr)
	{
		delete spaceMap;
		spaceMap = nullptr;
	}
}
