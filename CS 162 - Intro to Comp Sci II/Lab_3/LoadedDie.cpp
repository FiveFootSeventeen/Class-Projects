/*********************************************************************
** Program Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Implementation file for the LoadedDie class. This class
** is used to return random dice rolls and dice types to the Game class.
** The average roll of this class is higher than the Die class. Functions 
** are further described within the code.
*********************************************************************/

#include "LoadedDie.hpp"


LoadedDie::LoadedDie() // Default constructor for LoadedDie
{
	sides = 0;
	offset = 1;
}

LoadedDie::~LoadedDie()
{

}

/***************************************************************
** dieType function: Returns the die type. This is a virtual
** function and will automatically override dieType() in the
** Die class.
***************************************************************/
std::string LoadedDie::dieType()
{
	return "Loaded Die";
}

/***************************************************************
** Constructor for LoadedDie: sets inherited variables in Die class 
** equal to the int arguments passed to this constructor.
***************************************************************/
LoadedDie::LoadedDie(int sideIn, int offsetIn) : Die(sideIn, offsetIn)
{
}

/***************************************************************
** diceRoll function: Creates two random numbers and returns
** the larger of the two. On average it returns a number higher
** than diceRoll() in the Die class. This function is virtual
** and will automatically override diceRoll() in the Die class.
***************************************************************/
int LoadedDie::diceRoll()
{
	seed = int(time(0));
	srand(seed * offset);
	randomNum1 = rand() % sides + 1;
	randomNum2 = rand() % sides + 1;
	if (randomNum1 > randomNum2)
	{
		return randomNum1;
	}
	else
	{
		return randomNum2;
	}
	
}
