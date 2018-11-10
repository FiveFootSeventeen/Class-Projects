/*********************************************************************
** Class Name: FantasyTournament
** Author: Jacob Leno
** Date: 11/17/17
** Description: Header file for the FantasyTournament class.
*********************************************************************/

#ifndef FANTASYTOURNAMENT_HPP
#define FANTASYTOURNAMENT_HPP

#include "Character.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"
#include "HarryPotter.hpp"
#include "menu.hpp"
#include "CharacterList.hpp"
#include "LosingChar.hpp"

#include <string>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

class FantasyTournament
{
protected:
	//Variables
	LosingChar *lostStack = new LosingChar();
	CharacterList teamA{0, lostStack}, teamB{1, lostStack};
	enum player { tA, tB };
	int strengthBefore, damage, round;
	int teamAPoints, teamBPoints;

	//Functions
	Character* getPtr(int playerNum);
	std::string getTeam(int);
	CharacterList& getTeamObj(int team);
	void getSpecial(int, int);
	void assignPlayers(CharacterList&);	
	void addPoints(int);
	void characterChoice(CharacterList&, int);
	void clearTeamObj() {teamA.clear(), teamB.clear();}
	void clearScore() { teamAPoints = 0, teamBPoints = 0; }	
	void menu();
	void displayRound(int, int);
	void fight(int);
	void displayDefeated();
	void currentScore();
	void finalScore();
	void roundOutcome(int, int, int, int, string);

public:
	//Functions
	void gameplay();
	FantasyTournament() : teamAPoints(0), teamBPoints(0) {}
	~FantasyTournament();
};


#endif
