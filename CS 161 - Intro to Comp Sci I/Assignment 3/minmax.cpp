/*********************************************************************
** Author: Jacob Leno
** Date: 07/08/17
** Description: Assignment 3.a - This program asks the user how many
** numbers to enter, gets those numbers from input and displays
** a minimum and maximum.
*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	int min,
		max,
		numbers,	// Amount of numbers the user wants to enter
		userNum;	

	cout << "How many integers would you like to enter?" << endl; //Get amount of numbers from user
	cin >> numbers;
	cout << "Please enter " << numbers << " integers." << endl;
	cin >> userNum;
	min = max = userNum; //Set value of min and max equal to the first number

	if (numbers > 1) //If there is only one number min and max are set to the first integer entered, if not
	{				 //they are checked against each subsequent number entered.
		for (int i = 1; i < numbers; i++)
		{
			cin >> userNum;		
		
			if (userNum > max)
			{
				max = userNum;
			}
			else if (userNum < min)
			{
			min = userNum;
			}
		}
	}

	cout << "min: " << min << endl << "max: " << max << endl; //Display the min and max numbers
	
	return 0;
}
