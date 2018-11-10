/*********************************************************************
** Class Name: Practice
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the Practice
** class.
*********************************************************************/

#include "Practice.hpp"

//Destructor for the Practice class
Practice::~Practice()
{
	if (spaceMap)
	{
		delete spaceMap;
		spaceMap = nullptr;
	}
}

//Practice class constructor
Practice::Practice(std::string mapName) : Space()
{
	initializeMap(mapName);
}

//Initialize the map object with a given file name
void Practice::initializeMap(std::string mapName)
{
	this->spaceMap = new Map;
	this->spaceMap->loadMap(mapName);
}