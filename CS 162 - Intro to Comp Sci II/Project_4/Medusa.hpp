/*********************************************************************
** Class Name: Medusa
** Author: Jacob Leno
** Date: 11/17/17
** Description: Header file for the Medusa class. This class derives
** from the Character class.
*********************************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include "Character.hpp"

class Medusa : public Character
{
protected:
	//Variables
	int armor, strengthPoints, defenseRoll;
	int totalDamage, attackPts;
	bool glare;


public:
	//Functions
	Medusa() : armor(3), strengthPoints(8), glare(false) { setMaxStr(8); }
	int attack();
	void defense(int);
	int getArmor() { return armor; }
	int getDefense() { return defenseRoll; }
	int getStrengthPoint() { return strengthPoints; }
	int getAttack() { return attackPts; }
	int getTotalDamage() { return totalDamage; }
	bool getGlare() { return glare; }
	void setStrengthPoint(int strengthIn) { strengthPoints = strengthIn; }
	
};

#endif