/*********************************************************************
** Class Name: Character
** Author: Jacob Leno
** Date: 11/02/17
** Description: Implementation file for the Character class. Contains
** the function definitions for Character.
*********************************************************************/

#include "Character.hpp"

/*********************************************************************
** rollDice function: Takes the number of sides on the dice as an integer
** argument and the amount of dice to roll as an integer argument in the 
** second amount. It returns a integer value as the total of all the dice
** rolled.
*********************************************************************/

int Character::rollDice(int sides, int diceAmount)
{
	static int diceRoll;		//Make diceRoll static so a new variable is not instantiated 
	diceRoll = 0;				//rollDice() is called
	
	for (int i = 0; i < diceAmount; i++)
	{
		diceRoll += rand() % sides + 1;
	}
	return diceRoll;
}

/*********************************************************************
** rollDice function: Takes a number at the highest number - 1 to return
** a value of and returns a random integer between 0 and (randomMax -1)
*********************************************************************/

int Character::randomNumZero(int randomMax)
{
	return rand() % randomMax;
}