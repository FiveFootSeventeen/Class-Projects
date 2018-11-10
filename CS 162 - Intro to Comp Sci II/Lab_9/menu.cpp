/*********************************************************************
** Function Name: menu
** Author: Jacob Leno
** Date: 10/20/17
** Description: Implementation for the menu() function. The intMenu function is a
** versitile utility function that returns an integer value. The function
** has the option to display a menu with a yes or no question which will
** return either a 1 or a 2. The function can also ask the user for an
** integer value. Menus can be customized with headers and max and minimum
** integer sizes. The decMenu takes a question, a max and min size, and
** the amount of decimal places to display the max and min as. It uses this
** info to retrieve a decimal value from the user.
*********************************************************************/

#include "menu.hpp"

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
			cout << question << endl << "1. Yes\n2. No" << endl;
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
		cout << endl;
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
			cout << question << endl;
			getline(cin, choice);
			goodNum = checkInt(choice);
			if (!goodNum)
			{												//Display max and min size of number.
				cout << endl << "Enter an integer between " << minSize << " and " << maxSize << endl;
			}
			else
			{
				userChoice = std::stoi(choice);
				if (userChoice > maxSize || userChoice < minSize) //If number entered not between max and min loop until it is.
				{
					cout << endl << "Enter an integer between " << minSize << " and " << maxSize << endl;
					goodNum = false;
				}
			}
		} while (!goodNum);
		return userChoice = std::stoi(choice);
	}
	return userChoice;
}


/***************************************************************
** Menu structure for asking for some decimal value
***************************************************************/
double decMenu(std::string question, double maxSize, double minSize, int precision)
{
	std::string choice;
	bool goodNum;
	double userNumber;

	do
	{
		cout << question << endl;
		getline(cin, choice);
		goodNum = checkDec(choice);
		if (!goodNum)
		{												//Display max and min size of number.
			cout << endl << "Enter an decimal between " << fixed << showpoint << setprecision(precision) << \
				minSize << " and " << fixed << showpoint << setprecision(precision) << maxSize << endl;
		}
		else
		{
			userNumber = std::stod(choice);
			if (userNumber > maxSize || userNumber < minSize) //If number entered not between max and min loop until it is.
			{
				cout << endl << "Enter an decimal between " << fixed << showpoint << setprecision(precision) << \
					minSize << " and " << fixed << showpoint << setprecision(precision) << maxSize << endl;
				goodNum = false;
			}
		}
	} while (!goodNum);
	userNumber = std::stod(choice);
	return userNumber;
}

void displayText(std::string text)
{
	cout << text << endl;
}

std::string getString(std::string question)
{
	std::string userInput;
	cout << question << endl;
	getline(std::cin, userInput);
	return userInput;
}