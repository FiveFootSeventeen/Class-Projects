/*********************************************************************
** Author: Jacob Leno
** Date: 07/02/17
** Description: Assignment 2.b - This program takes a temperature in Celcius input 
** by the user and outputs a tempurature in Fahrenheit
*********************************************************************/

#include <iostream>
using namespace std;

int main() {
	double tempCel, tempFah;

	cout << "Please enter a Celcius tempurature.\n";
	cin >> tempCel;
	tempFah = ((9.0 / 5.0) * tempCel) + 32; // Conversion of Celcius tempurature to Fahrenheit
	cout << "The equivalent Fahrenheit temperature is:\n" << tempFah << endl;

	return 0;
}
