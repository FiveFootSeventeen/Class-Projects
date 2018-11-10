/*********************************************************************
** Author: Jacob Leno
** Date: 08/07/17
** Description: Assignment 9 - Header file for the TicTacToe class. This class
** has two data members. A char variable that stores the current player's turn
** and a Board object that is used to access the functions in the Board class.
*********************************************************************/
#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include "Board.hpp"

class TicTacToe
{
private:
	Board gamePlay;
	char playerTurn;

public:
	TicTacToe(char firstPlayerTurn);
	void play();

};

#endif