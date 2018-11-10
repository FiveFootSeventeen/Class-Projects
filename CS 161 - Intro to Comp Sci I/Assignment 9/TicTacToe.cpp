/*********************************************************************
** Author: Jacob Leno
** Date: 08/07/17
** Description: Assignment 9 - This is the class implementation file for
** the TicTacToe class, it contains the member functions for the class.
*********************************************************************/

#include "TicTacToe.hpp"
#include "Board.hpp"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

TicTacToe::TicTacToe(char firstPlayerTurn) //Default constructor for TicTacToe, takes first player as a char
{
	playerTurn = toupper(firstPlayerTurn);
}

void TicTacToe::play()			//If this function is called on a TicTacToe object and a
{								//default constructor has been initialized with a starting player
	bool unoccupied = false,		//it will begin a game.
		keepPlaying = true;
	int yCoord, xCoord;

	do {
		do {
			/****************************************************
			**This block of code takes a players move and sends it to 
			** the makeMove function in the Board class. If the space
			** is occupied it asks for another coordinate.
			****************************************************/
			gamePlay.print();

			cout << "Player " << playerTurn << " please enter your move." << endl << endl;
			cin >> yCoord >> xCoord;
			cout << endl;
			unoccupied = gamePlay.makeMove(yCoord, xCoord, playerTurn);
			if (unoccupied == false)
			{
				cout << endl << "That square is already taken." << endl << endl;
			}

		} while (unoccupied == false);

		if (playerTurn == 'X') //Change the current player's turn
			playerTurn = 'O';
		else
			playerTurn = 'X';

		/****************************************************
		**This switch statement prints out the current state 
		** of the game based on the value returned from the 
		** gameState function in the Board class.
		****************************************************/
		switch (gamePlay.gameState())
		{
		case X_WON:
			gamePlay.print();
			cout << "X has won the game!" << endl;
			keepPlaying = false;
			break;
		case O_WON:
			gamePlay.print();
			cout << "O has won the game!" << endl;
			keepPlaying = false;
			break;
		case DRAW:
			gamePlay.print();
			cout << "There has been a draw." << endl;
			keepPlaying = false;
			break;
		case UNFINISHED:
			keepPlaying = true;
			break;
		}

	} while (keepPlaying == true);
}

int main() //Main function for the TicTacToe game.
{
	char firstPlayer;
	cout << "Which player should go first? (X/O):";
	cin >> firstPlayer;
	TicTacToe gameStart(firstPlayer);
	gameStart.play();

	return 0;
}