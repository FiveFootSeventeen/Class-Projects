/*********************************************************************
** Program Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Class declaration file for the LoadedDie class. The average 
** roll of this class is higher than the Die class.This class is used 
** to return random dice rolls and dice types to the Game class.
*********************************************************************/
#include "Die.hpp"
#include <cstdlib>
#include <ctime>
#include <string>

#ifndef LOADEDDIE_HPP
#define LOADEDDIE_HPP

class LoadedDie : public Die
{
protected:
	int randomNum1, randomNum2;

public:
	LoadedDie();
	~LoadedDie();
	virtual std::string dieType();
	LoadedDie(int, int);
	virtual int diceRoll();
};


#endif