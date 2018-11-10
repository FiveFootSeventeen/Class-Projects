/*********************************************************************
** Class Name: Map
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the map
** class. This class contains all the functions for loading and using 
** a map in the Cake game.
*********************************************************************/

#include "Map.hpp"

//Default constructor for the Map class
Map::Map()
{
	teleport = false;
	gunFire = false;
	currentEvent = NOEVENT;
	portalsMade = 0;
	keys = 0;
	seconds = 30;
	minutes = 3;
	redPortal[COL] = -1;
	redPortal[ROW] = -1;
	bluePortal[COL] = -1;
	bluePortal[ROW] = -1;
	gunEnergy[ROW] = -1;
	gunEnergy[COL] = -1;
	flipFlop[ROW] = -1;
	flipFlop[COL] = -1;
}

//Set the time the player has to complete the level
void Map::setTime(int minutesIn, int secondsIn)
{
	minutes = minutesIn;
	seconds = secondsIn;
}

//Call to flip the 'X' tile to a '#' tile for vice versa
void Map::flipTile()	//X's are flipflop tiles the alternate between # and X when they are
{						//X they cannot have a portal generated on them.
	if (seconds % 2 == 0 && flipFlop[ROW] >= 0)
	{
		int row = flipFlop[ROW];
		int col = flipFlop[COL];
		if (currentMap[row][col] == 'X')
		{
			currentMap[row][col] = '#';
		}
		else if (currentMap[row][col] == '#')
		{
			currentMap[row][col] = 'X';
		}

	}
}

//Decrement game time by one second. If time is left set current event to NOTIME
void Map::decrementTime()
{
	seconds--;
	flipTile();
	if (seconds == -1)
	{
		seconds = 59;
		minutes -= 1;
	}
	if (minutes == 0 && seconds == 0)
	{
		currentEvent = NOTIME;
	}
}

//Call to output current minutes
void Map::displayMin()
{
	cout << minutes;
}

//Call to output current seconds
void Map::displaySec()
{
	cout << seconds;
}

//Load a map file with a given file name
void Map::loadMap(std::string mapName)
{
	inFile.open(mapName, std::ios::in);
	if (!inFile)
	{
		cout << "The map " << mapName << " failed to open" << endl;
	}
	
	int y = 0, x = 0;
	char cChar;
	while (inFile.peek() != EOF)	//Load the map from the file and initialize data members with location of
	{								//important characters on the map
		if (inFile.peek() == '\n') { y++; x = 0; }
		currentMap[y][x] = inFile.get();
		cChar = currentMap[y][x];
		if (cChar == 'L' || cChar == '$') { setLockedDoor(y, x); }
		if (cChar == 'D') { setDoor(y, x); }
		if (cChar == 'X')			//X's are flip flop tiles, find their location
		{							//as the map is being loaded
			flipFlop[ROW] = y;
			flipFlop[COL] = x;
		}
		x++;
	}
	inFile.clear();
	inFile.close();

	inFile.open("backpack.txt", std::ios::in);	//Initialize the backpack data member which will hold the 
	for (int y = 0; y < 4; y++)					//time and inventory
	{
		for (int x = 0; x < 27; x++)
		{
			backpack[y][x] = inFile.get();
		}
	}
	inFile.clear();
	inFile.close();
}

//Print out the current map and backpack to the console
void Map::printMap()
{

	for (int y = 0; y < MAX_Y - 1; y++)
	{
		for (int x = 0; x < MAX_X - 1; x++)
		{

			if (cPlayerLoc[ROW] == y && cPlayerLoc[COL] == x) { cout << '8'; }	//Print out player
			else if (cGunLoc[ROW] == y && cGunLoc[COL] == x) { cout << '*'; }	//Print out portal gun
			else if (gunFire)
			{
				if (gunEnergy[ROW] == y && gunEnergy[COL] == x) { cout << "o"; } //Print out portal energy
				else { cout << currentMap[y][x]; }
			}
			else { cout << currentMap[y][x]; }
		}
	}

	cout << endl;
	char prev = ' ';
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 27; x++)
		{
			if (prev == '-')	//If a '-' was printed previously then print out a key if the player has one
			{
				if (keys > 0) { cout << '~'; }
				else { cout << ' '; }
				prev = ' ';
			}
			else
			{
				prev = backpack[y][x];
				cout << backpack[y][x];
			}
			
			if (backpack[y][x] == ':')
			{
				if (backpack[y][x - 1] == 'n') { displayMin(); }
				if (backpack[y][x - 1] == 'c') { displaySec(); }
			}
		}
	}

	cout << endl;
}

//Update the player location, gun location, energy location and any portals.
void Map::update()
{
	checkPlayerTile(playerOne->getCharacterRow(), playerOne->getCharacterColumn());
	cPlayerLoc[COL] = playerOne->getCharacterColumn();
	cPlayerLoc[ROW] = playerOne->getCharacterRow();
	cGunLoc[COL] = playerOne->getGunColumn();
	cGunLoc[ROW] = playerOne->getGunRow();
	if (gunFire) //If there is portal energy then change its position.
	{ 
		getEnergyTile(gunEnergyHeading);
		changeEnergyPos();
	}
}

//Call to advance the position of the portal gun energy based on its heading
void Map::changeEnergyPos()
{
	switch (gunEnergyHeading)
	{
	case NORTH:
		gunEnergy[ROW] -= 1;
		if (gunEnergy[ROW] == 0) { gunFire = false; }
		break;
	case SOUTH:
		gunEnergy[ROW] += 1;
		if (gunEnergy[ROW] == MAX_X) { gunFire = false; }
		break;
	case EAST:
		gunEnergy[COL] += 1;
		if (gunEnergy[COL] == MAX_Y) { gunFire = false; }
		break;
	case WEST:
		gunEnergy[COL] -= 1;
		if (gunEnergy[COL] == -1) { gunFire = false; }
		break;
	}
}

//Initialize the Player pointer with a Player object reference
void Map::initializePlayer(Player *playerOneIn)
{
	playerOne = playerOneIn;
}

int Map::getEnergyRow()
{
	return gunEnergy[ROW];
}

int Map::getEnergyColumn()
{
	return gunEnergy[COL];
}

//Called when player has fired the portal gun using 'f' it sets the 
//heading of the energy and places it on the map one tile in front of
//the portal gun.
void Map::gunFired(direction heading )
{
	gunFire = true;
	gunEnergyHeading = heading;
	switch (heading)
	{
	case NORTH :
		gunEnergy[COL] = playerOne->getGunColumn();
		gunEnergy[ROW] = playerOne->getGunRow() - 1;
		break;
	case SOUTH:
		gunEnergy[COL] = playerOne->getGunColumn();
		gunEnergy[ROW] = playerOne->getGunRow() + 1;
		break;
	case EAST:
		gunEnergy[COL] = playerOne->getGunColumn() + 1;
		gunEnergy[ROW] = playerOne->getGunRow();
		break;
	case WEST:
		gunEnergy[COL] = playerOne->getGunColumn() - 1;
		gunEnergy[ROW] = playerOne->getGunRow();
		break;
	}
}

//Called to check the tile that is one beyone that of the player's location or
// the location of their gun, if they are allowed to step onto that tile the function
//returns true.
bool Map::playerGetNext(direction heading)
{
	int gunRow = playerOne->getGunRow();
	int gunCol = playerOne->getGunColumn();
	int playRow = playerOne->getCharacterRow();
	int playCol = playerOne->getCharacterColumn();
	char nextGun;
	char nextPlayer;
	switch (heading)
	{
	case NORTH:
		nextGun = currentMap[gunRow - 1][gunCol];				//Check to see if the player is about to move into a 
		nextPlayer = currentMap[playRow - 1][playCol];			//block that it not allowed to be stepped on. If they
		if (!checkNext(nextGun, nextPlayer)) { return false; }	//are return false.
		break;
	case SOUTH:
		nextGun = currentMap[gunRow + 1][gunCol];
		nextPlayer = currentMap[playRow + 1][playCol];
		if (!checkNext(nextGun, nextPlayer)) { return false; }
		break;
	case EAST:
		nextGun = currentMap[gunRow][gunCol + 1];
		nextPlayer = currentMap[playRow][playCol + 1];
		if (!checkNext(nextGun, nextPlayer)) { return false; }
		break;
	case WEST:
		nextGun = currentMap[gunRow][gunCol - 1];
		nextPlayer = currentMap[playRow][playCol - 1];
		if (!checkNext(nextGun, nextPlayer)) { return false; }
		break;
	}
	return true;
}

//Sent the char values of the player's or their gun's next tile. If they are traversable tiles
//return true
bool Map::checkNext(char gun, char player)
{
	if (player == '+' || player == '#' || player == '_' || player == '|' || player == 'X') { return false; }
	if (gun == '#' || gun == '_' || gun == '|' || gun == 'X') { return false; }
	return true;
}

//Get the current location of the gun energy if it is on a '#' tile create a portal
//if it is on a '+' or '/' tile remove it from the map
void Map::getEnergyTile(direction heading)
{
	if (currentMap[gunEnergy[ROW]][gunEnergy[COL]] == '#')
	{
		gunFire = false;
		makePortal(gunEnergy[ROW], gunEnergy[COL]);
	}
	if (currentMap[gunEnergy[ROW]][gunEnergy[COL]] == '+')	//If energy comes in contact with + it stops
	{
		gunFire = false;
	}
	if (currentMap[gunEnergy[ROW]][gunEnergy[COL]] == '/') //If energy comes in contact with / it stops
	{
		gunFire = false;
	}
}

//Return the color of the current portal to be created
portalUp Map::getPortalUp()
{
	if (portalColor == BLUE)
	{
		portalColor = RED;
		return BLUE;
	}
	else
	{
		portalColor = BLUE;
		return RED;
	}
}

//Called when the gun energy has encountered a valid tile for a portal, it creates a portal on 
//that tile. It is sent the row and column of the tile the portal is to be created on as
//arguments.
void Map::makePortal(int row, int column)
{
	portalUp currentPortal = getPortalUp();

	if (currentPortal == RED)
	{
		if (redPortal[COL] != -1) { currentMap[redPortal[ROW]][redPortal[COL]] = prevRed; }
		redPortal[COL] = column;
		redPortal[ROW] = row;
		prevRed = currentMap[row][column];
		currentMap[row][column] = 'O';
		portalsMade++;						//Keep track of the portals made so 
	}										//The player cant teleport when there is only one portal
	if (currentPortal == BLUE)
	{
		if (redPortal[COL] != -1) { currentMap[bluePortal[ROW]][bluePortal[COL]] = prevBlue; }
		bluePortal[COL] = column;
		bluePortal[ROW] = row;
		prevBlue = currentMap[row][column];
		currentMap[row][column] = 'O';
		portalsMade++;
	}
}

//Call and send the current row and column the player is on as arguments
//this function will check to see if the player is standing on a key or a 
//portal and call appropriate functions.
void Map::checkPlayerTile(int row, int column)
{
	if (currentMap[row][column] == 'L' && keys > 0 && teleport)
	{
		currentEvent = NEXTMAP;
		teleport = false;
	}
	if (currentMap[row][column] == 'D' && teleport)
	{ 
		currentEvent = PREVMAP; 
		teleport = false;
	}
	if (currentMap[row][column] == '$')
	{
		currentEvent = WINGAME;
	}
	if (currentMap[row][column] == '~')//If a player is standing on a key put it in the inventory and change the tile to a blank
	{
		keys += 1;
		currentMap[row][column] = ' ';
		teleport = false;
	}									//In order for a teleport to take place the player must be standing in a portal
										//location, teleport must be true (the player must move at least once after teleporting)
										//and there must be at least 2 portals.
	if (redPortal[ROW] == row && redPortal[COL] == column && teleport && portalsMade > 1)
	{
		playerOne->playerStartLoc(bluePortal[ROW], bluePortal[COL]);		//Teleport the player
		teleport = false;
	}
	if (bluePortal[ROW] == row && bluePortal[COL] == column && teleport && portalsMade > 1)
	{
		playerOne->playerStartLoc(redPortal[ROW], redPortal[COL]);
		teleport = false;
	}
}

//Set member variable lockedDoor equal to the location of the
//locked door on the map
void Map::setLockedDoor(int row, int column)
{
	lockedDoor[ROW] = row;
	lockedDoor[COL] = column;
}


//Set member variable door equal to the location of the
//door on the map
void Map::setDoor(int row, int column)
{
	door[ROW] = row;
	door[COL] = column;
}

void Map::setStartLockedDoor()
{
	playerOne->playerStartLoc(lockedDoor[ROW], lockedDoor[COL]);
}

void Map::setStartDoor()
{
	playerOne->playerStartLoc(door[ROW], door[COL]);
}


