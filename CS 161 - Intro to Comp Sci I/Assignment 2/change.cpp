/*********************************************************************
** Author: Jacob Leno
** Date: 07/03/17
** Description: Assignment 2.c - This program takes an input from the user 
** in cents and outputs the fewest coins of each amount to make that much in 
** change.
*********************************************************************/

#include <iostream>
using namespace std;

int main() {
	int cents;
	cout << "Enter an amount in cents less than a dollar.\n";
	cin >> cents;

	// Calculate the amount of each denomination of change and output the amount.
	cout << "\nYour change will be:\n" << "Q: " << (cents / 25); 
	cents -= (cents / 25) * 25;
	cout << "\nD: " << (cents / 10);
	cents -= (cents / 10) * 10;
	cout << "\nN: " << (cents / 5);
	cents -= (cents / 5) * 5;
	cout << "\nP: " << cents << endl;

	return 0;
}
