/*********************************************************************
** Program Name: Langton's Ant
** Author: Jacob Leno
** Date:10/04/17
** Description: Ant class implementation file. Contains the function 
** definitions for the ant class.
*********************************************************************/

#include <iostream>

#include "Ant.hpp"

using std::cout;
using std::endl;

/***************************************************************
**Ant default constructor function: initialize Ant class to 
**default values.
***************************************************************/
Ant::Ant()
{
	rows = 50;
	columns = 75;
	antLoc[0] = 25;
	antLoc[1] = 38;
	gameBoard = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		gameBoard[i] = new char[columns];
		for (int j = 0; j < columns; j++)
		{
			gameBoard[i][j] = 32; // Set all elements in the array equal to ' '
		}
	}
}

/***************************************************************
**Ant constructor function: used for initializing the ant class
***************************************************************/

Ant::Ant(int rowsIn, int columnsIn, int startingRowIn, int startingColumnIn)
{
	rows = rowsIn;
	columns = columnsIn;
	antLoc[0] = startingRowIn - 1;
	antLoc[1] = startingColumnIn - 1;
	gameBoard = new char*[rowsIn];
	for (int i = 0; i < rowsIn; i++)
	{
		gameBoard[i] = new char[columnsIn];
		for (int j = 0; j < columnsIn; j++)
		{
			gameBoard[i][j] = 32; // Set all elements in the array equal to ' '
		}
	}


}

/***************************************************************
**moveAnt function: For each direction moveAnt checks to see what 
**the ants current heading is and attempts to move the ant one in 
**that direction. If the ant encounters the limits of the array it 
**is wrapped around to the other side.
***************************************************************/

void Ant::moveAnt() 
{					
					
	setColor();
	if (antDir == 0) //If the direction is up move the ant up one
	{
		if (antLoc[0] == 0)
		{
			antLoc[0] = rows - 1;
		}
		else
		{
			antLoc[0] -= 1;
		}
	}

	if (antDir == 180) //If the direction is down move the ant down one
	{
		if (antLoc[0] == rows - 1)
		{
			antLoc[0] = 0;
		}
		else
		{
			antLoc[0] += 1;
		}
	}

	if (antDir == 90) //If the direction is right move the ant right one
	{
		if (antLoc[1] == columns - 1)
		{
			antLoc[1] = 0;
		}
		else
		{
			antLoc[1] += 1;
		}
	}

	if (antDir == 270) //If the direction is left move the ant left one
	{
		if (antLoc[1] == 0)
		{
			antLoc[1] = columns - 1;
		}
		else
		{
			antLoc[1] -= 1;
		}
	}
}

/***************************************************************
**changeDir function: This function changes the direction the ant 
**is heading in. It does this by checking the heading sent to it,
**adding 90 for right (270 for left), and then taking the remainder
**when its divided by 360 (sets it to 0 if its equal to 360)
***************************************************************/

void Ant::changeDir(char heading)
{
	if (heading == 'R')	//If ant takes a right add 90 degrees. If the direction if over 360 find the remainder after
	{					//dividing by 360. If it equals 360 set the direction to 0. (A value of 0 is up)
		antDir += 90;

		if (antDir > 360)
		{
			antDir = antDir % 360;
		}
		if (antDir == 360)
		{
			antDir = 0;
		}

	}
	if (heading == 'L')//If ant takes a left add 270 degrees. If the direction if over 360 find the remainder after	
	{					//dividing by 360. If it equals 360 set the direction to 0.
		antDir += 270;

		if (antDir > 360)
		{
			antDir = antDir % 360;
		}
		if (antDir == 360)
		{
			antDir = 0;
		}

	}
}

/***************************************************************
**displayBoard function: This function is called from main and 
**displays the current state of the board with the current
**location of the ant.
***************************************************************/

void Ant::displayBoard()
{
	cout << endl;
	for (int i = 0; i < (columns + 2); i++)
	{
		cout << "-";
	}
	for (int i = 0; i < rows; i++)
	{
		cout << endl << "|";
		for (int j = 0; j < columns; j++)
		{
			if (antLoc[0] == i && antLoc[1] == j) //For each pass check if its the ant's location, if it is display the
			{									  //ant, otherwise display the current board color.
				cout << '*';
			}
			else
			{
				cout << gameBoard[i][j];
			}
		}
		cout << "|";
	}
	cout << endl;
	for (int i = 0; i < (columns + 2); i++)
	{
		cout << "-";
	}
	cout << endl;
}

/***************************************************************
**setColor function: This function swaps the color of the board 
**location the ant is currently on and changes the ant's heading.
***************************************************************/
void Ant::setColor()
{
	if (gameBoard[antLoc[0]][antLoc[1]] == 32) // If gameboard is white set it to black
	{
		gameBoard[antLoc[0]][antLoc[1]] = 35;
		changeDir('R');	//Set heading to right
	}
	else	// If gameboard is black set it to white
	{
		gameBoard[antLoc[0]][antLoc[1]] = 32;
		changeDir('L');	//Set heading to left
	}
}

/***************************************************************
**Destructor that deletes the dynamically allocated array
***************************************************************/
Ant::~Ant()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] gameBoard[i];
	}
	delete[] gameBoard;
}