/*********************************************************************
** Program Name: Recursion
** Author: Jacob Leno
** Date: 10/20/17
** Description: This is a program that utilizes the properties of recursion
** to print the reverse of a string of user input, sum an array of integers,
** and calculate the triangular number of an integer. An initial menu
** asks the user to input a number and after a prompt for input it displays
** the result.
*********************************************************************/
#include <iostream>
#include <string>

#include "recurse.hpp"
#include "menu.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int selection, size, sum, triNum;
	string inputBuffer;
	int * intArr;

	do
	{
		selection = intMenu("1. Print an input in reverse"  
						   "\n2. Calculate the sum of several integers" 
						   "\n3. Calculate the triangular number of an integer"
						   "\n4. Quit Program", \
							false, 4, 1, true, \
							"Please make a selection:");

		if (selection == 1)
		{
			cout << "Please enter the text you would like reversed:" << endl;
			getline(cin, inputBuffer);	//Use getline so spaces are included
			reverse(inputBuffer);
		}
		if (selection == 2)
		{
			size = intMenu("How may integers would you like to enter? (1 - 50)", false, 50, 1);
			intArr = new int[size];			//Create a new int array and assign intArr to it

			for (int i = 0; i < size; i++)	//Get integers from user
			{
				intArr[i] = intMenu("Enter integer number " + std::to_string(i + 1) + " ", false, 10000, -10000);
			}

			sum = arraySum(intArr, size);
			cout << "The total of the numbers you entered is: " << sum << endl;
			delete[] intArr;
		}
		if (selection == 3)
		{
			triNum = intMenu("Enter the number to calculate the triangular number of: ", false, 1000, -1000);
			cout << "The triangular number of " << triNum << " is " << triangleNumber(triNum) << endl;
		}
	} while (selection != 4);

	return 0;
}
