/*********************************************************************
** Function Name: IntMenu
** Author: Jacob Leno
** Date: 10/04/17
** Description: Implementation for the intMenu function. This function is a
** versitile utility function that returns an integer value. The function
** has the option to display a menu with a yes or no question which will
** return either a 1 or a 2. The function can also ask the user for an
** integer value. Menus can be customized with headers and max and minimum
** integer sizes.
*********************************************************************/

#include <iostream>
#include <string>

#include "intMenu.hpp"
#include "checkInt.hpp"


using std::cout;
using std::cin;
using std::endl;

int intMenu(std::string question, bool isYorN, int maxSize, int minSize, bool isHeading, std::string heading)
{
	std::string choice;
	bool goodNum;
	int userChoice = 0;

	/***************************************************************
	** Menu structure for displaying a yes or no question.
	***************************************************************/
	if (isYorN == true)
	{
		if (isHeading == true)
		{
			cout << endl << heading << endl << endl; //Display the heading if the user chooses
		}
		
		do		//Loop until the user chooses on of two correct choices
		{
			cout << endl << question << endl;
			cout << "1. Yes" << endl << "2. No" << endl;
			getline(cin, choice);
			goodNum = checkInt(choice);
			if (!goodNum)
			{
				cout << endl << "Enter either a 1 or 2!" << endl << endl;
			}
			else
			{
				userChoice = std::stoi(choice);
				if (userChoice != 1 && userChoice != 2)
				{
					cout << endl << "Enter either a 1 or 2!" << endl << endl;
					goodNum = false;
				}
			}
		} while (!goodNum);
		return userChoice;
		
	}

	/***************************************************************
	** Menu structure for asking for some integer value
	***************************************************************/
	if (isYorN == false)
	{

		if (isHeading == true)
		{
			cout << endl << heading << endl << endl; //Display the heading if the user chooses
		}
		do
		{
			cout << endl << question << endl;
			getline(cin, choice);
			goodNum = checkInt(choice);
			if (!goodNum)
			{												//Display max and min size of number.
				cout << endl << "Enter an integer between " << minSize << " and " << maxSize << endl << endl;
			}
			else
			{
				userChoice = std::stoi(choice);
				if (userChoice > maxSize || userChoice < minSize) //If number entered not between max and min loop until it is.
				{
					cout << endl << "Enter an integer between " << minSize << " and " << maxSize << endl << endl;
					goodNum = false;
				}
			}
		} while (!goodNum);
		return userChoice = std::stoi(choice);
	}
	return userChoice;
}