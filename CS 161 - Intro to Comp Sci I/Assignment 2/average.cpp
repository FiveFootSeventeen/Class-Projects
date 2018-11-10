/*********************************************************************
** Author: Jacob Leno
** Date: 07/02/17
** Description: Assignment 2.a - This program prints out the average of five numbers
** input by the user
*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	double one, two, three, four, five, average;
	cout << "Please enter five numbers." << endl;
	cin >> one;
	cin >> two;
	cin >> three;
	cin >> four;
	cin >> five;
	average = (one + two + three + four + five) / 5; //Add together the five input numbers and compute the average
	cout << "The average of those numbers is:\n" << average << endl;

	return 0;

}
