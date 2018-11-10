/*********************************************************************
** Class Name: BlueMen
** Author: Jacob Leno
** Date: 11/17/17
** Description: Implementation file for the BlueMen class. Contains
** the function definitions for BlueMen.
*********************************************************************/

#include "BlueMen.hpp"

/*********************************************************************
** attack function: calculates the attack based on the dice and sides
** BlueMen get and returns as an integer value
*********************************************************************/

int BlueMen::attack()
{
	attackPts = rollDice(10, 2);
	return attackPts;
}

/*********************************************************************
** defense function: accepts an integer parameter that represents the
** amount of damage the defending player is being attacked with and
** calculates how much damage BlueMen has taken based on the dice and
** sides BlueMen gets. It also factors into account BlueMen's mob ability
** and for every 4 strength BlueMen loses they lose a "Man" and a defense
** dice roll.
*********************************************************************/

void BlueMen::defense(int attackedWith)
{
	static int strBefore, menBefore;
	strBefore = strengthPoints;
	defenseRoll = rollDice(6, blueMen);
	totalDamage = attackedWith - defenseRoll - armor;
	menBefore = blueMen; 
	manDown = false;
	if (totalDamage > 0)		//If BlueMen lost strength subtract it from strengthPoints
	{
		strengthPoints -= totalDamage;
		if (strengthPoints > 0)
		{
			blueMen = strengthPoints / 4;						//If BlueMen lost strength this turn check
			if (strengthPoints % 4 > 0) { blueMen += 1; }		//to see if they also lost a man
			if (blueMen < menBefore)
			{
				manDown = true;									//If they did then manDown is true
				lostMen = menBefore - blueMen;
			}
		}
		else 
		{ 
			blueMen = 0;										//If blue men are dead check to see
			if (blueMen < menBefore)							//if they lost a man in the last turn
			{													//but set BlueMen to zero because 
				manDown = true;									//they can't lose more than 3 men in a game.
				lostMen = menBefore - blueMen;
			}
		}
	}
	else { totalDamage = 0; }
}