/*********************************************************************
** Class Name: Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Implementation file for the Game class. This class
** along with the Die class and LoadedDie class are used to play the
** "War Game" game. The game is started from main by calling the startGame
** function on a Game object. This class has functions for its menu, the
** gameplay and the printing of scores for each round and after the game
** is over. Each function is described in greater detail within the code.
*********************************************************************/

#include "Game.hpp"
#include "intMenu.hpp"
#include "Die.hpp"
#include "LoadedDie.hpp"

#include <iomanip>
#include <string>
#include <iostream>
#include <chrono> //used for chrono::milliseconds()
#include <thread> //used for this_thread::sleep_for()

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::right;
using std::setw;


Game::Game()
{
	rounds = 0;
	dieType1 = 1;
	dieType2 = 1;
	sides1 = 0;
	sides2 = 0;
	roundWin1 = 0;
	roundWin2 = 0;
	rollPlayer1 = 0;
	rollPlayer2 = 0;
}
Game::~Game()
{

}

/***************************************************************
**startGame function:: Calling this begins the game
***************************************************************/
void Game::startGame()
{
	int play = intMenu("Please make a choice\n1. Play game\n2. Exit game", true, 2, 1, true, "War with Dice\nThis is a war game between two players and is played with dice.\n"
		"The type of dice, sides on the dice, and number of rounds are up to you!");
	
	while (play == 1)
	{
		inputMenu();
		if (dieType1 == 1)					//Once the types of die each player wants are know, create 
		{									//DA objects and assign Die pointers to point to them
			player1Die = new Die(sides1, 1);
		}
		else
		{
			player1Die = new LoadedDie(sides1, 1);
		}

		if (dieType2 == 1)
		{
			player2Die = new Die(sides2, 2);
		}
		else
		{
			player2Die = new LoadedDie(sides2, 2);
		}

		gameplay(player1Die, player2Die); //Send the pointers to gameplay to begin the game
		
		play = intMenu("Would you like to play again?\n1. Yes\n2. No", true);

		delete player1Die; //Free dynamically allocated memory
		delete player2Die;
	} 
}

/***************************************************************
** inputMenu Function: called from startGame, this function collects
** info from the user.
***************************************************************/
void Game::inputMenu()
{
	setRounds();
	setDie();
	setSides();
}

/***************************************************************
**setDie function: called from inputMenu. This function sets the 
** die type for each player.
***************************************************************/
void Game::setDie()
{
	dieType1 = intMenu("What type of die will player 1 be using?\n1.Regular Die\n2.Loaded Die", true);
	dieType2 = intMenu("What type of die will player 2 be using?\n1.Regular Die\n2.Loaded Die", true);
}

/***************************************************************
** setSides function: called from inputMenu. This function sets the
** number of sides on the die for each player.
***************************************************************/
void Game::setSides()
{
	sides1 = intMenu("How many sides for player 1's die? 1-20", false, 20, 1);
	sides2 = intMenu("How many sides for player 2's die? 1-20", false, 20, 1);
}

/***************************************************************
** setRounds function: called from inputMenu. This function sets the
** number of rounds the game will last for.
***************************************************************/
void Game::setRounds()
{
	this->rounds = intMenu("How many rounds would you like to play?\nPlease enter an integer 1-100", false, 100, 1);
}


/***************************************************************
** gameplay function: This function takes two Die pointers as parameters.
** For each round in the game it determines the winner and calls
** appropriate functions to output the result.
***************************************************************/
void Game::gameplay(Die * player1Die, Die * player2Die)
{
	roundWin1 = 0;
	roundWin2 = 0;

	for (int i = 0; i < rounds; i++)
	{
		cout << endl << "Dice is being rolled";			//Wait a little over a second to give the user time to see the results of the
														//previous round and allow the system clock to advance so a new random number
														//is seeded
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		for (int j = 0; j < 4; j++)
		{
			cout << " . ";
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}

		cout << endl;

		//Get the roll for each player depending on what die type they chose
		rollPlayer1 = player1Die->diceRoll();
		rollPlayer2 = player2Die->diceRoll();

		//Decide who won and if the round was a tie. Add a point where appropriate
		//and call printRound to print results.
		if (rollPlayer1 > rollPlayer2)
		{
			roundWin1 += 1;
			printRound(1, i + 1);
		} 
		if (rollPlayer1 < rollPlayer2)
		{
			roundWin2 += 1;
			printRound(2, i + 1);
		}
		if (rollPlayer1 == rollPlayer2)
		{
			printRound(0, i + 1);
		}
	}


	//Print out the final score and the winner
	if (roundWin1 > roundWin2)
	{
		printFinalScore(1);
	}
	if (roundWin1 < roundWin2)
	{
		printFinalScore(2);
	}
	if (roundWin1 == roundWin2)
	{
		printFinalScore(0);
	}

}

/***************************************************************
** printRound function: This function takes the winner and the
** round number as integer parameters. It decides who was the 
** winner based on the number sent to it and prints appropriate
** results.
***************************************************************/
void Game::printRound(int winsRound, int roundNum)
{

	if (winsRound == 0)
	{
		cout << "This round was a tie!" << endl;
	} 
	else if (winsRound == 1)
	{
		cout << "Player 1 Wins the round!" << endl;
	}
	else if (winsRound == 2)
	{
		cout << "Player 2 Wins the round!" << endl;
	}

	//Print out the information from the round using member variables.
	cout << setw(12) << right << "Player 1 " << right << setw(30) << "Player 2 " << endl;
	cout << setw(12) << right << "Roll: " << setw(18) << left << rollPlayer1 << right << setw(12) << "Roll: " <<
		left << setw(18) << rollPlayer2 << endl;
	cout << setw(12) << right << "Score: " << setw(18) << left << roundWin1 << right << setw(12) << "Score: " <<
		left << setw(18) << roundWin2 << endl;
	cout << setw(12) << right << "Dice Type: " << setw(18) << left << player1Die->dieType() << right << setw(12) << "Dice Type: " <<
		left << setw(18) << player2Die->dieType() << endl;
	cout << setw(12) << right << "Sides: " << setw(18) << left << sides1 << right << setw(12) << "Sides: " <<
		left << setw(18) << sides2 << endl << endl;
	cout << setw(12) << right << "Round: " << setw(18) << left << roundNum << endl << endl;
}

/***************************************************************
** printFinalScore function: This function takes one int as a
** parameter and uses it to determine the winner. It then prints
** the appropriate output with the result.
***************************************************************/
void Game::printFinalScore(int winner)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	if (winner == 0)
	{
		cout << "The game ended in a tie!" << endl;
	}
	else if (winner == 1)
	{
		cout << "Player 1 Wins the game!" << endl;
	}
	else if (winner == 2)
	{
		cout << "Player 2 Wins the game!" << endl;
	}
	cout << setw(25) << left << "Player 1 final score: " << setw(10) << left << roundWin1 << right << setw(25) << "Player 2 final score: " <<
		left << setw(10) << roundWin2 << endl;
}