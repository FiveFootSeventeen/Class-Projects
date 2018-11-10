/*********************************************************************
** Author: Jacob Leno
** Date: 08/07/17
** Description: Assignment 9 - This is the class implementation file for
** the Board class, it contains the member functions for the class.
*********************************************************************/

#include "Board.hpp"
#include <iomanip>
#include <iostream>
using std::cout;
using std::endl;

Board::Board() //Default constructor for Board class
{			   //this constructor fills the gameBoard array with the '.' character.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gameBoard[i][j] = '.';
		}
	}
}

bool Board::makeMove(int yCoord, int xCoord, char playerTurn) //This function records X or O at a specified coordinate and returns true
{																//if the space is already occupied it returns false.
	if(gameBoard[yCoord][xCoord] == 'X' || gameBoard[yCoord][xCoord] == 'O')
	{
		return false;
	}
	else
	{
		if(playerTurn == 'X')
		{
			gameBoard[yCoord][xCoord] = 'X';
		}
		if(playerTurn == 'O')
		{
			gameBoard[yCoord][xCoord] = 'O';
		}
		return true;
	}
}

State Board::gameState() //This function determines the current state of the game 
{						 // and returns X_WON, O_WON, DRAW, UNFINISHED as an enum type State
								
	bool keepPlaying = false;

	/****************************************************
	**This Block of code determines if there are three in 
	** a row of either X or O. If there are three in a row
	** it will return which player won.
	****************************************************/
	for (int i = 0; i < 3; i++)
	{
		if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2])
		{
			if (gameBoard[i][0] == 'X') { return X_WON;}
			else if (gameBoard[i][0] == 'O') { return O_WON; }
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i])
		{
			if (gameBoard[0][i] == 'X') { return X_WON; }
			else if (gameBoard[0][i] == 'O') { return O_WON; }
		}
	}
	if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2])
	{
		if (gameBoard[0][0] == 'X') { return X_WON; }
		else if (gameBoard[0][0] == 'O') { return O_WON; }
	}
	if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0])
	{
		if (gameBoard[0][2] == 'X') { return X_WON; }
		else if (gameBoard[0][2] == 'O') { return O_WON; }
	}

	/****************************************************
	** The following code checks to see if the '.' character
	** present anywhere in the gameBoard array. If it is
	** the program knows that it is still possible to play
	** and will return UNFINISHED if the character is not
	** present it returns DRAW.
	****************************************************/

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (gameBoard[i][j] == '.')
				keepPlaying = true;
		}
	}

	if (keepPlaying == true)
		return UNFINISHED;
	else
		return DRAW; 
}

void Board::print()
{
	cout << endl << "  0 1 2" << endl << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 3; j++)
		{
			cout << gameBoard[i][j] << " ";		
		}
		cout << endl << endl;
	}
}



