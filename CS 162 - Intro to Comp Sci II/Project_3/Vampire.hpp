/*********************************************************************
** Class Name: Vampire
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the Vampire class. This class derives
** from the Character class.
*********************************************************************/

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

#include "Character.hpp"

class Vampire : public Character
{
protected:
	//Variables
	int armor, strengthPoints, defenseRoll;
	int totalDamage, attackPts;
	bool charm;

public:
	//Functions
	Vampire() : armor(1), strengthPoints(18) {}
	int attack();
	void defense(int);
	int getArmor() { return armor; }
	int getDefense() { return defenseRoll; }
	int getStrengthPoint() { return strengthPoints; }
	int getAttack() { return attackPts; }
	int getTotalDamage() { return totalDamage; }
	bool getCharm() { return charm; }
};

#endif
