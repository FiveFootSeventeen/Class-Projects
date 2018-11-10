/*********************************************************************
** Class Name: HarryPotter
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the HarryPotter class. This class derives
** from the Character class.
*********************************************************************/

#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP

#include "Character.hpp"

class HarryPotter : public Character
{
protected:
	//Variables
	int armor, strengthPoints, defenseRoll;
	int totalDamage, attackPts, extraLife;
	bool horcrux;

public:
	//Functions
	HarryPotter() : armor(0), strengthPoints(10), extraLife(1), horcrux(false) {}
	int attack();
	void defense(int);
	int getArmor() { return armor; }
	int getDefense() { return defenseRoll; }
	int getStrengthPoint() { return strengthPoints; }
	int getAttack() { return attackPts; }
	int getTotalDamage() { return totalDamage; }
	void hogwarts();
	bool getAbility() { return horcrux; }
};

#endif