/*********************************************************************
** Program name: File Input/Output
** Author:  Jacob Leno
** Date: 10/06/17
** Description: Outputs letter frequencies to files with user specified
** file names. There will be one file for each paragraph in the original
** file. The file names will start with the user specified name and end
** with "_1", "_2", "_3" etc... The function must be sent a ofstream 
** object and a pointer to an array of integers.
*********************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include "output_Letters.hpp"

void output_Letters(std::ofstream &outFile, int* letterFreq)
{
	static std::string fileName;
	static int fileNum;
	fileNum += 1; 


	if (fileNum == 1) //The first time the function is run ask the user what name they would like to give the file.
	{
		do {
			std::cout << "What name would you like to give the file?" << std::endl \
				<< "Each file will have its number append to the end of the name" << std::endl \
				<< "depending on the order it was created in." << std::endl << "Enter file name without a file extension: ";
			getline(std::cin, fileName);

			outFile.clear();
			outFile.open(fileName + "_" + std::to_string(fileNum) + ".txt");
			if (outFile.fail())
			{
				std::cout << "Cannot create file with that file name, enter a new name." << std::endl;
			}
		} while (outFile.fail());
	}
	else //For each subsequent file append the number of the file to the end of its filename
	{
		outFile.open(fileName + "_" + std::to_string(fileNum) + ".txt");
	}

	for (int i = 0; i < 26; i++) //Output the letter frequencies to the file.
	{
		outFile << char(i + 97) << ": " << letterFreq[i] << std::endl << std::endl;
	}
	outFile.close();
}