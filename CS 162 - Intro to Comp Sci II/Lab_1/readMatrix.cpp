/*********************************************************************
** Function name: readMatrix
** Author:  Jacob Leno
** Date: 09/29/17
** Description: This function accepts a pointer to a array of integer
** pointers and the size of the matrix (either 3 for 3x3 or 2 for 2x2)
** and fills the array with integer input from the user.
*********************************************************************/

#include "readMatrix.hpp"
#include "checkInt.hpp"
#include <iostream>
#include <cstdlib>
#include <string>


void readMatrix(int **arr, int size)
{
	std::string temp;
	bool goodNum, tooBig;

	for(int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//Continue to ask the user for input until checkInt returns a falue of true
			//and the number is small enough to be stored as an integer when it does 
			//convert the value to and int and store it in the array.
			do { 
				getline(std::cin, temp);
				goodNum = checkInt(temp);
				tooBig = false;

				if (temp.length() > 9)
				{
					tooBig = true;
					std::cout <<  "Enter a smaller value!" << std::endl;
				}

				if(goodNum == false && tooBig == false)
				{
					std::cout << "Enter an integer!" << std::endl;
				}
				
				if(goodNum == true && tooBig == false)
				{
					arr[i][j] = std::stoi(temp);
				}
			} while (goodNum == false || tooBig == true);
		}
	}
}

