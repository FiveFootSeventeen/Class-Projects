/*********************************************************************
** Author: Jacob Leno
** Date: 07/13/17
** Description: Assignment 4a - This program contains a function fallDistance
** that accepts the seconds an object has been falling for as a double value
** and outputs the distance that object has fallen in meters.
*********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::showpoint;
using std::setprecision;

double fallDistance(double);	// Function prototype for fallDistance

/*
int main()
{
	double seconds;
	char again;

	do
	{
		cout << "Please enter how long the object has been falling in seconds:" << endl;
		cin >> seconds;
		cout << endl << "The object has fallen ";
		cout << fixed << showpoint << setprecision(2); //Fix the amount of decimal places in the output value to 2
		cout << fallDistance(seconds) << " meters" << endl;
		cout << "If you would like to calculate another distance enter \"Y\"" << endl;
		cin >> again;
	} while (again == 'Y' || again == 'y');

	return 0;
}
*/


double fallDistance(double time) // This function accepts a time in seconds as a double and ouputs the 
{								 // distance an object has fallen as a double.
	return 0.5 * 9.8 * time * time;
}

