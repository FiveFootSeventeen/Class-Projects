/*********************************************************************
** Author: Jacob Leno
** Date: 07/13/17
** Description: Assignment 4c - This program contain a function that takes a number as
** input and calculates the number of steps it takes to reach 1 following
** a hailstone sequence.
*********************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int hailstone(int userNum);

/*
int main()
{
	int userNum;

	cout << "Enter a number, the hailstone sequence will be performed" << endl;
	cout << "and I will tell you how many steps it took:" << endl;
	cin >> userNum;
	cout << "The hailstone sequence took " << hailstone(userNum) << " steps." << endl;

	return 0;
}
*/

int hailstone(int userNum)
{
	if (userNum == 1)		// If the user enters 1 return 0 as the number of steps
	{
		return 0;
	}
	else
	{
		int steps = 0;		// Initialize the step counter
		while (userNum > 1)
		{
			steps++;		//Each time the loop is run add one to the step counter
			if (userNum % 2 == 0)		//If the number is even divide by two
			{
				userNum /= 2;
			}
			else						//If the number is not even multiply by three then add one
			{
				userNum = (userNum * 3) + 1;
			}
		}
		return steps;		//Return the amount of steps it took to reach 1
	}

}