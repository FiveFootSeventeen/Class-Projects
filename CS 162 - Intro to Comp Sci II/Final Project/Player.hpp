/*********************************************************************
** Class Name: Player
** Author: Jacob Leno
** Date: 12/04/17
** Description: Header file for the Player class
*********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "names.hpp"

class Player
{
public:
	direction getCurrentDirection();
	void changeDirection(direction);
	void advanceDirection(direction);
	int getCharacterRow();
	int getCharacterColumn();
	int getGunRow();
	int getGunColumn();
	void playerStartLoc(int, int);

protected:
	int character[2];
	int gun[2];
	direction currentDirection;

};

#endif 