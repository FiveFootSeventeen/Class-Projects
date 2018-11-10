/*********************************************************************
** Class Name: FantasyGame
** Author: Jacob Leno
** Date: 11/02/17
** Description: Header file for the FantasyGame class. 
*********************************************************************/

#ifndef FANTASYGAMEHPP
#define FANTASYGAME_HPP

#include "Character.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"
#include "HarryPotter.hpp"
#include "menu.hpp"

#include <string>
#include <iostream>

using std::cout;
using std::endl;

class FantasyGame
{
protected:
	//Variables
	Character *playerOne, *playerTwo;
	enum player { P1, P2 };
	int strengthBefore, damage;

	//Functions
	void menu();
	void characterChoice(Character *&, int);
	void displayRound(int, int);
	int fight(int);
	Character* getPtr(int playerNum);
	std::string getType(int);
	std::string getPlayer(int player);
	
public:
	void gameplay();
	FantasyGame() {}
	~FantasyGame(){}

};

#endif