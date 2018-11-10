/*********************************************************************
** Author: Jacob Leno
** Date: 07/09/17
** Description: Assignment 3.c - This program asks the user to enter a
** random number and then has a player try to guess that random number
*********************************************************************/

#include <iostream>
using namespace std;


int main()
{
	int numToGuess,		//Number that is to be guessed
		userNum,		//Player's guess
		tries = 0;

	cout << "Enter a random number for the player to guess." << endl;
	cin >> numToGuess;
	cout << "Enter your guess." << endl;

	do 
	{

		cin >> userNum;
		tries += 1;

		if (userNum > numToGuess)		
		{
			cout << "Too high - try again." << endl;
		}
		else if (userNum < numToGuess)
		{
			cout << "Too low - try again." << endl;
		}
		else if ((userNum == numToGuess) && (tries == 1)) //If the correct number is guessed on the first guess use "try"
		{
			cout << "You guessed it in " << tries << " try." << endl;
		}
		else if ((userNum == numToGuess) && (tries > 1)) //If it take more than one guess use "tries"
		{
			cout << "You guessed it in " << tries << " tries." << endl;
		}


	} while (userNum != numToGuess);		//Loop until the player guesses the number correctly


	return 0;
}

