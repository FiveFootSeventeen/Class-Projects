/*********************************************************************
** Class Name: HarryPotter
** Author: Jacob Leno
** Date: 11/02/17
** Description: Implementation file for the HarryPotter class. Contains
** the function definitions for HarryPotter.
*********************************************************************/

#include "HarryPotter.hpp"

/*********************************************************************
** attack function: calculates the attack based on the dice and sides
** HarryPotter get and returns as an integer value
*********************************************************************/

int HarryPotter::attack()
{
	attackPts = rollDice(6, 2);
	return attackPts;
}

/*********************************************************************
** defense function: accepts an integer parameter that represents the
** amount of damage the defending player is being attacked with and
** calculates how much damage HarryPotter has taken based on the dice and
** sides HarryPotter gets.
*********************************************************************/

void HarryPotter::defense(int attackedWith)
{
	defenseRoll = rollDice(6, 2);
	totalDamage = attackedWith - defenseRoll - armor;
	if (totalDamage > 0) { strengthPoints -= totalDamage; }
	else { totalDamage = 0; }
	hogwarts();
}

/*********************************************************************
** hogwarts function: If HarryPotter's strength falls below 1 and he
** still has an extra life left hogwarts() will reset his strength to 
** 10 and set horcrux to true so that the FantasyGame function will 
** know to output a message that he's back from the dead.
*********************************************************************/

void HarryPotter::hogwarts()
{
	if (strengthPoints <= 0 && extraLife > 0)
	{
		extraLife -= 1;
		strengthPoints = 10;
		horcrux = true;
	}
	else
	{
		horcrux = false;
	}
}