/*********************************************************************
** Class Name: Challenge
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the Challenge
** class.
*********************************************************************/

#include "Challenge.hpp"

//Destructor for the Practice class
Challenge::~Challenge()
{
	if (spaceMap) 
	{
		delete spaceMap;
		spaceMap = nullptr;
	}
}

//Practice class constructor
Challenge::Challenge(std::string mapName) : Space()
{
	initializeMap(mapName);
}

//Initialize the map object with a given file name
void Challenge::initializeMap(std::string mapName)
{
	this->spaceMap = new Map;
	this->spaceMap->loadMap(mapName);
}