/*********************************************************************
** Program Name: Langton's Ant
** Author: Jacob Leno
** Date: 10/04/17
** Description: This is a simulation of Langton's Ant. This program will 
** ask the user for a number of rows, columns, steps, a starting row, and
** a starting column for the ant. The user also has the option to choose
** a random starting location for the ant. The ant follows two simple rules
** if it lands on a white space it will turn right 90 degrees and turn the space
** to black. If it lands on a black space it will turn left 90 degrees
** the space to white.
*********************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>//used for time()
#include <ctime>  //used for rand()
#include <chrono> //used for chrono::milliseconds()
#include <thread> //used for this_thread::sleep_for()

#include "checkInt.hpp"
#include "Ant.hpp"
#include "intMenu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


int main()
{
	unsigned seed = time(0);
	srand(seed);
	int rows, columns, steps, startingRow, startingColumn;
	int menuOutput, isRand, playAgain;
	

	/***************************************
	**		Input Section
	***************************************/

	menuOutput = intMenu("1. Start Langton's Ant simulation \n2. Quit program\n", true, 2, 1, true, \
		"This is the Langton's Ant simulation, please choose an option:");

	if (menuOutput == 2) //If the user has chosen to quit return 0 to end the program
	{
		return 0;
	}

	do {
		isRand = intMenu("1. Yes \n2. No\n", true, 2, 1, true, "Would you like to use a random starting location for the ant?");

		rows = intMenu("Enter the number of rows (Max 40): ", false, 40);		//Max of 40 rows and 75 columns so the animation
		columns = intMenu("Enter the number of columns (Max 75): ", false, 75); //will display properly when window is maximized

		steps = intMenu("Enter the number of steps (Max 100,000): ", false, 100000); //This number is arbitrary but I felt it should 
																					 //have a max so things didnt get too out of hand.

		if (isRand == 1) //If user has chosen to have the ants starting location randomized, set it to a random location
		{
			startingRow = rand() % rows + 1;
			startingColumn = rand() % columns + 1;
		}
		else			 //Otherwise ask the user where they would like the ant to start
		{
			startingRow = intMenu("Enter the row the ant should start in (1-" + std::to_string(rows) + "): ", false, rows);
			startingColumn = intMenu("Enter the column the ant should start in (1-" + std::to_string(columns) + "): ", false, columns);
		}

		/***************************************
		**		Simulation Section
		***************************************/

		Ant antGame(rows, columns, startingRow, startingColumn);

		for (int i = 0; i < steps; i++)
		{
			antGame.moveAnt();
			antGame.displayBoard();
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Add a 1/2 second delay
		}
		playAgain = intMenu("1. Yes \n2. No\n", true, 2, 1, true, "Would you like to play again?");
	} while (playAgain == 1);




	return 0;
}