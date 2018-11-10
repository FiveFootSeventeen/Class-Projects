/*********************************************************************
** Program name: File Input/Output
** Author:  Jacob Leno
** Date: 10/06/17
** Description: This program opens a file and checks counts the frequency
** of each letter in each seperate paragraph. It then outputs the letter
** frequencies to files with user specified names. One file is output 
** per paragraph in the original document.
*********************************************************************/

#include <fstream>
#include <iostream>

#include "count_Letters.hpp"
#include "output_Letters.hpp"
#include "count_Paragraph.hpp"


int main()
{
	const int LETTERS = 26;
	int letterFreq[LETTERS];
	std::ofstream outFile;
	std::ifstream inFile;
	int paragraphs;

	inFile.open("file_fun.txt");
	if (inFile.fail())				//If the file does not open the program closes.
	{
	std::cout << "File open failed, program will now terminate" << std::endl;
	std::cin.get();
	return 1;
	}

	paragraphs = count_Paragraph(inFile);

	for (int i = 0; i < paragraphs; i++) //Loop for each paragraph in the file.
	{
		count_Letters(inFile, letterFreq);
		output_Letters(outFile, letterFreq);
	}

	std::cout << paragraphs << " Files have been created, one for each paragraph." << std::endl \
		<< "Press any key to continue" << std::endl;
	std::cin.get();

	inFile.close();

	return 0;
}