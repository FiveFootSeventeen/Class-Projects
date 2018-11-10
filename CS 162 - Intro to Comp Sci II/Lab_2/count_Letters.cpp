/*********************************************************************
** Program name: File Input/Output
** Author:  Jacob Leno
** Date: 10/06/17
** Description: This function is sent a ifstream object and a pointer
** to an array of integers. It counts up the letter frequencies in the
** ifstream object and stores them in the array.
*********************************************************************/

#include <fstream>
#include "count_Letters.hpp"

void count_Letters(std::ifstream &inFile, int* letterFreq)
{
	char check;
	int arrLoc = 0;

	for (int i = 0; i < 26; i++) //Clear the values in the array.
	{
		letterFreq[i] = 0;
	}

	check = inFile.get();

	while (check != EOF && check != '\n')	//Check through the file for each letter until an EOF or \n character is reached
	{										//storing the values in the letterFreq array.
		if (check >= 97 && check <= 122)
		{
			arrLoc = check - 97;
			letterFreq[arrLoc] += 1;
		}
		if (check >= 65 && check <= 90)
		{
			arrLoc = check - 65;
			letterFreq[arrLoc] += 1;
		}
		check = inFile.get();
	}

}