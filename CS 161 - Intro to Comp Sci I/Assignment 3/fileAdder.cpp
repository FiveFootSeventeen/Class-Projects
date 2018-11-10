/*********************************************************************
** Author: Jacob Leno
** Date: 07/08/17
** Description: Assignment 3.b - This project reads numbers from a 
** text file specified by the user, adds each number, then outputs
** the sum to a text file names sum.txt
*********************************************************************/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	ofstream outputFile("sum.txt"); //Define ofstream object outputFile and create sum.txt
	ifstream inputFile;				//Define ifstream object inputFile
	string fileName;				//String used to get file path from user
	int number, 
		sum =  0;
	

	cout << "Enter the filepath of the file you would like to use: ";
	cin >> fileName;

	inputFile.open(fileName.c_str());

	if (inputFile)	//Check if the file was successfully opened
	{
		while (inputFile >> number)	//Check to see if there is data on the next line of the file
		{							//if there is add it to sum.
			sum += number;
		}
		outputFile << sum;			//Once all the data is read output the sum to sum.txt

		outputFile.close();
	}
	else
	{
		cout << "\nCould not access file";
	}
	inputFile.close();

	return 0;
}