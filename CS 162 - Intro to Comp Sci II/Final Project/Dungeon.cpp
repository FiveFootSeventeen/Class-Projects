/*********************************************************************
** Class Name: Dungeon
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the Dungeon
** class.
*********************************************************************/

#include "Dungeon.hpp"

//Destructor for the dungeon class
Dungeon::~Dungeon()
{
	if (spaceMap)
	{
		delete spaceMap;
		spaceMap = nullptr;
	}
}

//Constructor for the Dungeon class
Dungeon::Dungeon(std::string mapName, int level, Space *left, Space *right) : Space()
{
	initializeMap(mapName);
	this->level = level;
	this->right = right;
	this->left = left;
}

//Initialize the map object with a given file name
void Dungeon::initializeMap(std::string mapName)
{
	this->spaceMap = new Map;
	this->spaceMap->loadMap(mapName);
}