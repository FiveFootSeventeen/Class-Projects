/*********************************************************************
** Class Name: Barbarian
** Author: Jacob Leno
** Date: 11/02/17
** Description:Implementation file for the Barbarian class. Contains
** the function definitions for Barbarian.
*********************************************************************/

#include "Barbarian.hpp"

/*********************************************************************
** attack function: calculates the attack based on the dice and sides
** Barbarian get and returns as an integer value
*********************************************************************/
int Barbarian::attack()
{
	attackPts = rollDice(6, 2);
	return attackPts;
}

/*********************************************************************
** defense function: accepts an integer parameter that represents the 
** amount of damage the defending player is being attacked with and 
** calculates how much damage Barbarian has taken based on the dice and
** sides Barbarian gets.
*********************************************************************/

void Barbarian::defense(int attackedWith)
{
	defenseRoll = rollDice(6, 2);
	totalDamage = attackedWith - defenseRoll - armor;
	if (totalDamage > 0) { strengthPoints -= totalDamage; }
	else { totalDamage = 0; }
}
