/*********************************************************************
** Class Name: Player
** Author: Jacob Leno
** Date: 12/04/17
** Description: This file contains the function definitions for the 
** player class.
*********************************************************************/

#include "Player.hpp"

//Call with a heading to change the direction the player is facing
void Player::changeDirection(direction heading)
{
	switch (heading)
	{
	case NORTH:
		gun[ROW] = getCharacterRow() - 1;
		gun[COL] = getCharacterColumn();
		currentDirection = NORTH;
		break;
	case SOUTH:
		gun[ROW] = getCharacterRow() + 1;
		gun[COL] = getCharacterColumn();
		currentDirection = SOUTH;
		break;
	case EAST:
		gun[ROW] = getCharacterRow();
		gun[COL] = getCharacterColumn() + 1;
		currentDirection = EAST;
		break;
	case WEST:
		gun[ROW] = getCharacterRow();
		gun[COL] = getCharacterColumn() - 1;
		currentDirection = WEST;
		break;
	}
}

//Call with a heading to advance the player on the map
// in the direction of the heading, this should only be
// called if the player is already facing in the direction
// of the heading.
void Player::advanceDirection(direction heading)
{
	switch (heading)
	{
	case NORTH:
		character[ROW] -= 1;
		gun[ROW] -= 1;
		break;
	case SOUTH:
		character[ROW] += 1;
		gun[ROW] += 1;
		break;
	case EAST:
		character[COL] += 1;
		gun[COL] += 1;
		break;
	case WEST:
		character[COL] -= 1;
		gun[COL] -= 1;
		break;
	}
}

//Returns the current direction the player is facing
direction Player::getCurrentDirection()
{
	return currentDirection;
}

//Set the player's start location on the map
void Player::playerStartLoc(int playerRow, int playerColumn)
{
	character[ROW] = playerRow;
	character[COL] = playerColumn;
	gun[ROW] = playerRow - 1;
	gun[COL] = playerColumn;
	currentDirection = NORTH;
}

int Player::getCharacterRow()
{
	return character[ROW];
}

int Player::getCharacterColumn()
{
	return character[COL];
}

int Player::getGunRow()
{
	return gun[ROW];
}

int Player::getGunColumn()
{
	return gun[COL];
}