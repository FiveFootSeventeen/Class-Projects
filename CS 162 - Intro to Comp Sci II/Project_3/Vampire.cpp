/*********************************************************************
** Class Name: Vampire
** Author: Jacob Leno
** Date: 11/02/17
** Description: Implementation file for the Vampire class. Contains
** the function definitions for Vampire.
*********************************************************************/

#include "Vampire.hpp"

/*********************************************************************
** attack function: calculates the attack based on the dice and sides
** Vampire get and returns as an integer value
*********************************************************************/

int Vampire::attack()
{
	attackPts = rollDice(12, 1);
	return attackPts;
}

/*********************************************************************
** defense function: accepts an integer parameter that represents the
** amount of damage the defending player is being attacked with and
** calculates how much damage Vampire has taken based on the dice and
** sides Vampire gets. However Vampire has a 50% chance of activating
** his charm ability. If charm is activated he takes not damage at all.
*********************************************************************/

void Vampire::defense(int attackedWith)
{
	charm = randomNumZero(2);	//With 2 as an argument randomNumZero returns a random Num between 0-1.
	defenseRoll = rollDice(6, 1);
	totalDamage = attackedWith - defenseRoll - armor;
	if (totalDamage > 0 && !charm) { strengthPoints -= totalDamage; }
	else { totalDamage = 0; }
}
