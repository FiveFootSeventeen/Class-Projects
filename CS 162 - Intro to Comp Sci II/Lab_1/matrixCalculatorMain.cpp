/*********************************************************************
** Program name: Matrix Calculator
** Author:  Jacob Leno
** Date: 09/29/17
** Description: This program asks the user what size matrix they would like
** to enter, prompts the user to input matrix values, and then outputs 
** the matrix and its determinant.
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "readMatrix.hpp"
#include "determinant.hpp"
#include "checkInt.hpp"

using std::cout;
using std::cin;
using std::endl;


int main()
{
	int matrixSize, dtmnt, largestNum, smallestNum, maxWidth;
	std::string whichMatrix;
	bool isGood = true;


	//Continue to ask the user for correct input until isGood is true
	do {	
		cout << "What size of matrix?" << endl << "1. 2x2" << endl << "2. 3x3" << endl << "Enter the number of your choice: ";
		getline(cin, whichMatrix);
		isGood = checkInt(whichMatrix);
		
		if (isGood) //If it is an integer check to see if it is 1 or 2
		{
			if (std::stoi(whichMatrix) != 1 && std::stoi(whichMatrix) != 2)
			{
				isGood = false;

			}
		}
		if (isGood == false)
		{
			cout << endl << "Enter an integer value of 1 or 2!" << endl << endl;
		}
	} while (isGood == false);

	matrixSize = (std::stoi(whichMatrix)) + 1;


	//Dynamically allocate a pointer to an array of int pointers
	int ** arr = new int*[matrixSize];			
	for (int i = 0; i < matrixSize; i++)
	{
		arr[i] = new int[matrixSize];
	}


	cout << endl <<  "Please enter " << matrixSize * matrixSize << " numbers to fill the matrix." << endl;
	readMatrix(arr, matrixSize);
	dtmnt = determinant(arr, matrixSize);
	

	cout << endl <<  "The determinant of the matrix entered is: " << dtmnt << endl << endl;
	

	largestNum = smallestNum = arr[0][0];
	for (int i = 0; i < matrixSize; i++)		//Find the largest or smallest integer in order to set a proper field width in the ouput
	{
		for (int j = 0; j < matrixSize; j++)
		{
			if (arr[i][j] > largestNum)
			{
				largestNum = arr[i][j];
			}
			if (arr[i][j] < smallestNum)
			{
				smallestNum = arr[i][j];
			}
		}
	}
	if (std::to_string(largestNum).length() > std::to_string(smallestNum).length())	//Decide which number is the longest
	{
		maxWidth = (std::to_string(largestNum)).length();
	}
	else
	{
		maxWidth = (std::to_string(smallestNum)).length();
	}
	

	cout << "Matrix entered: " << endl;
	for (int i = 0; i < matrixSize; i++)				//Display the matrix
	{
		for (int j = 0; j < matrixSize; j++)
		{
			cout << std::setw(maxWidth) << arr[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < matrixSize; i++)				//Delete dynamically allocated array and pointer to array
	{
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}