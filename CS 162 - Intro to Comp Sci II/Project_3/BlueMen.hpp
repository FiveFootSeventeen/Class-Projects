/*********************************************************************
** Class Name: BlueMen
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the BlueMen class. This class derives
** from the Character class.
*********************************************************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

#include "Character.hpp"

class BlueMen : public Character
{
protected:
	//Variables
	int armor, strengthPoints, defenseRoll;
	int totalDamage, attackPts, blueMen, lostMen;
	bool manDown;

public:
	//Functions
	BlueMen() : armor(3), strengthPoints(12), blueMen(3), lostMen(0) {}
	int attack();
	void defense(int);
	int getArmor() { return armor; }
	int getDefense() { return defenseRoll; }
	int getStrengthPoint() { return strengthPoints; }
	int getAttack() { return attackPts; }
	int getTotalDamage() { return totalDamage; }
	bool getManDown() { return manDown; }
	int getLostMen() { return lostMen; }
};

#endif