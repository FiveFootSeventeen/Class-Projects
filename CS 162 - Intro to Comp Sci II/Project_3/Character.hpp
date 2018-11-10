/*********************************************************************
** Class Name: Character
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the Character class. The Barbarian,
** BlueMen, HarryPotter, Medusa, and Vampire classes derive from this
** class.
*********************************************************************/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <ctime>
#include <cstdlib>

class Character
{
protected:
	//Variables
	int armor, strengthPoints, diceRoll, defenseRoll;
	int totalDamage, attackPts;
	unsigned seed = int(time(0));

public:
	//Functions
	Character() : armor(1), strengthPoints(1), diceRoll(1) { srand(seed); }
	virtual ~Character() {}
	virtual int attack() = 0;
	virtual void defense(int) = 0;
	virtual int getArmor() { return armor; }
	virtual int getDefense() { return defenseRoll; }
	virtual int getStrengthPoint() { return strengthPoints; }
	virtual int getAttack() { return attackPts; }
	virtual int getTotalDamage() { return totalDamage; }
	int rollDice(int sides, int diceAmount);
	int randomNumZero(int randomMax);

};


#endif