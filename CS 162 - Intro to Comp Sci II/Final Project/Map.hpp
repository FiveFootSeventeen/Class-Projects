/*********************************************************************
** Class Name: Map
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the header file for the Map class
*********************************************************************/

#ifndef MAP_HPP
#define MAP_HPP

#include "Player.hpp"
#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Map
{
public:
	Player *playerOne;
	std::fstream inFile;
	static const int MAX_Y = 33;
	static const int MAX_X = 35;
	char currentMap[MAX_Y][MAX_X];
	char backpack[4][27];
	int lockedDoor[2], door[2];
	
	Map();
	int getEnergyRow();
	int getEnergyColumn();
	eventType getEvent() { return currentEvent; }
	void setEvent(eventType newEvent) { currentEvent = newEvent; }
	void setTime(int minutes, int seconds);
	bool playerGetNext(direction);
	void getEnergyTile(direction heading);
	void setStartLockedDoor();
	void setStartDoor();
	void loadMap(std::string);
	void update();
	void printMap();
	void decrementTime();
	void initializePlayer(Player*);
	void gunFired(direction heading);
	portalUp getPortalUp();
	void teleportOK() { teleport = true; }

protected:
	bool gunFire, teleport;
	int redPortal[2], bluePortal[2];
	int gunEnergy[2], cPlayerLoc[2], cGunLoc[2];
	int flipFlop[2];
	int seconds, minutes, keys, portalsMade;
	char prevRed, prevBlue;
	portalUp portalColor = BLUE;
	direction gunEnergyHeading;
	eventType currentEvent;
	bool checkNext(char, char);
	void flipTile();
	void displayMin();
	void displaySec();
	void setLockedDoor(int row, int column);
	void setDoor(int row, int column);
	void changeEnergyPos();
	void makePortal(int, int);
	void checkPlayerTile(int, int);
};

#endif