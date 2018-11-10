/*********************************************************************
** Class Name: Medusa
** Author: Jacob Leno
** Date: 11/17/17
** Description: Implementation file for the Medusa class. Contains
** the function definitions for Medusa.
*********************************************************************/

#include "Medusa.hpp"

/*********************************************************************
** attack function: calculates the attack based on the dice and sides
** Medusa get and returns as an integer value. If Medusa rolls a 12
** attackPts will be set to 999 and glare will be set to true. This is
** an instant kill vs any player except the vampire if his charm
** ability is activated.
*********************************************************************/

int Medusa::attack()
{
	attackPts = rollDice(6, 2);

	if (attackPts == 12) 
	{ 
		attackPts = 999;
		glare = true; 
	}
	else { glare = false; }
	return attackPts;
}

/*********************************************************************
** defense function: accepts an integer parameter that represents the
** amount of damage the defending player is being attacked with and
** calculates how much damage Medusa has taken based on the dice and
** sides Medusa gets.
*********************************************************************/

void Medusa::defense(int attackedWith)
{
	defenseRoll = rollDice(6, 1);
	totalDamage = attackedWith - defenseRoll - armor;
	if (totalDamage > 0) { strengthPoints -= totalDamage; }
	else { totalDamage = 0; }
}