/*********************************************************************
** Author: Jacob Leno
** Date: 08/07/17
** Description: Assignment 9 - Header file for the Board class. This class
** has two data members and enumerated data type that stores the state of the
** game and a char array that stores the state of the game board.
*********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

enum State { X_WON, O_WON, DRAW, UNFINISHED }; //Define enumerated data type State

class Board
{
private:
	char gameBoard[3][3];
	State stateOfGame;

public:
	Board();
	bool makeMove(int xCoord, int yCoord, char playerTurn);
	State gameState();
	void print();
};

#endif