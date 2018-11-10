/*********************************************************************
** Class Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Class declaration file for the Game class. This class
** is the main class for the "War Game" game. Call the startGame function 
** from main to begin a game.
*********************************************************************/
#include "Die.hpp"
#include <string>

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
public:
	Game();
	~Game();
	void startGame();


protected:
	int rounds, dieType1, dieType2, sides1, sides2;
	int roundWin1, roundWin2, rollPlayer1, rollPlayer2;
	Die *player1Die, *player2Die;
	void inputMenu();
	void setDie();
	void setSides();
	void setRounds();
	void gameplay(Die*, Die*);
	void printRound(int, int);
	void printFinalScore(int);

};


#endif