/*********************************************************************
** Program Name: Fibonacci Implementation Testing
** Author: Jacob Leno
** Date: 11/27/17
** Description: Function implementations for the fibonacci functions 
** program
*********************************************************************/

#include "fibFunct.hpp"

//A menu function called from main that gets a choice from the user
//and calls the appropriate function.

void fibMenu()
{
	int fibChoice, terms;
	clock_t time;

	do
	{
		fibChoice = intMenu("1. Recursive Sequence"		//Get a choice from the user
			"\n2. Iterative Sequence"
			"\n3. Quit",
			false, 3, 1, true,
			"Welcome to the fibonacci implementation testing program"
			"\nThis program will test the runtime of both an iterative and a recursive"
			"\nfibonacci sequence, which type would you like to test?");

		if (fibChoice == 1)
		{
			terms = intMenu("How many terms would you like to test for? (1-40)", false, 40);
			time = clock();
			fibRecurse(terms);	//User chose recurse, call appropriate function
			time = clock() - time;											//Code adapted from http://www.cplusplus.com/reference/ctime/clock/
			printf("\nIt took %d clicks to run the recursive algorithm (%f seconds).\n", time, ((float)time) / CLOCKS_PER_SEC);
		}
		if (fibChoice == 2)
		{
			terms = intMenu("How many terms would you like to test for? (1-40)", false, 40);
			time = clock();
			fibIterate(terms);	//User choice iterative , call appropriate function
			time = clock() - time;											//Code adapted from http://www.cplusplus.com/reference/ctime/clock/
			printf("\nIt took %d clicks to run the iterative algorithm (%f seconds).\n", time, ((float)time) / CLOCKS_PER_SEC);
		}
	} while (fibChoice != 3);

}

//Calls the recursive algorithm function and prints its results.
//This function does this for the number of terms it is sent as an argument

void fibRecurse(int terms)
{
	for (int i = 0; i < terms; i++)
	{
		printNumber(recurse(i));
	}
}

//Recursive implementation of the algorithm to calculate the fibonacci sequence
//This function returns the final number in a fibonacci sequence from 0 to terms.

unsigned long recurse(unsigned long terms)	//The code for this recursive implementation of the fibonacci sequence was taken from 
{											//C++ early objects pg. 926
	if (terms <= 0)
	{
		return 0;
	}
	else if (terms == 1)
	{
		return 1;
	}
	else
	{
		return recurse(terms - 1) + recurse(terms - 2);
	}
}

//Iterative implementation of the algorithm to calculate the fibonacci sequence
//This algorithm prints out the fibonacci numbers from 1 to terms as it calculates them

void fibIterate(int terms)
{
	unsigned long firstTerm = 0;
	unsigned long secondTerm = 1;
	unsigned long temp;

	if (terms == 1)
	{
		printNumber(firstTerm);
	}
	else if (terms == 2)
	{
		printNumber(firstTerm);
		printNumber(secondTerm);
	}
	else
	{
		printNumber(firstTerm);
		printNumber(secondTerm);
		for (int i = 2; i < terms; i++)
		{
			temp = firstTerm;
			firstTerm = secondTerm;
			secondTerm += temp;
			printNumber(secondTerm);
		}
	}
}

//Prints out the number it is sent as an argument

void printNumber (unsigned long number)
{
	cout << number << " ";
}