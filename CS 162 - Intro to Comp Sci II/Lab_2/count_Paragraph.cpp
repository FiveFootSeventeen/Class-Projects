/*********************************************************************
** Program name: File Input/Output
** Author:  Jacob Leno
** Date: 10/06/17
** Description: This function is sent an ifstream object with an open file
** and counts the amount of paragraphs in the open file. It does this by
** counting the amount of newlines. If it reaches the end of a paragraph 
** that does not end in a newline character but is the end of a file
** it will count that paragraph as well.
*********************************************************************/
#include "count_Paragraph.hpp"
#include <fstream>


int count_Paragraph(std::ifstream &inFile)
{
	char check = 0;
	int paragraphTot = 0;
	
	check = inFile.get();
	while (check != EOF) //Count the paragraphs in the file until the end of file is reached.
	{
		if (check == '\n')
		{
			paragraphTot += 1;
		}
		else if (inFile.peek() == EOF && check != '\n') //If the next character is the end of file and a \n character
		{												//hasnt been found count that as a paragraph
			paragraphTot += 1;
		}
		check = inFile.get();
	}

	inFile.clear();
	inFile.seekg(0L, std::ios::beg);

	return paragraphTot;
}