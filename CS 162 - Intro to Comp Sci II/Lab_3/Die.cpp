/*********************************************************************
** Program Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Implementation file for the Die class. This class
** is used to return random dice rolls and dice types to the Game class.
** Functions are further described within the code.
*********************************************************************/

#include "Die.hpp"


Die::Die()
{
	sides = 0;
	offset = 1;
}

Die::~Die()
{

}

/***************************************************************
** dieType function: Returns the die type. This is a virtual function.
***************************************************************/
std::string Die::dieType()
{
	return "Regular Die";
}

/***************************************************************
** Constructor for Die: Uses a member initialization list to set
** its member variables to the arguments passed to it.
***************************************************************/
Die::Die(int sideIn, int offset) : sides(sideIn), offset(offset)
{
}

/***************************************************************
** diceRoll function: Creates a random number and returns it. 
** the random number will differ dependin on the offset passed to
** it when the Die object is created.
***************************************************************/
int Die::diceRoll()
{
	seed = int(time(0));
	srand(seed * offset);
	return rand() % sides + 1;
}