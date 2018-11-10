/*********************************************************************
** Class Name: Barbarian
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the Barbarian class. This class derives
** from the Character class.
*********************************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "Character.hpp"

class Barbarian : public Character
{
protected:
	//Variables
	int armor, strengthPoints, defenseRoll;
	int totalDamage, attackPts;

public:
	//Functions
	Barbarian() : armor(0), strengthPoints(12) {}
	int attack();
	void defense(int);
	int getArmor() { return armor; }	
	int getDefense() { return defenseRoll; }
	int getStrengthPoint() { return strengthPoints; }
	int getAttack() { return attackPts; }
	int getTotalDamage() { return totalDamage; }
};

#endif