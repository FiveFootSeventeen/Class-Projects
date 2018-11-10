/*********************************************************************
** Program Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Class declaration file for the Die class. This class
** is used to return random dice rolls and dice types to the Game class.
*********************************************************************/

#include <string>
#include <cstdlib>
#include <ctime>

#ifndef DIE_HPP
#define DIE_HPP

class Die
{
protected:
	int sides, seed;
	int offset; //An offset that is multiplied by the random number seed
				//to generate seperate random numbers for player 1 and player 2

public:
	Die();
	~Die();
	virtual std::string dieType();
	Die(int, int);
	virtual int diceRoll();
};

#endif

