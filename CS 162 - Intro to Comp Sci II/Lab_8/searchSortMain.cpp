/*********************************************************************
** Program Name: Search and Sort
** Author: Jacob Leno
** Date: 11/16/17
** Description: This program will search through several unsorted files
** using a linear search, sort the file data using quick sort algorithm
** and once the data is sorted it will perform a binary search on the 
** sorted data for a user specified integer.
*********************************************************************/


#include "SearchSort.hpp"
#include "menu.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	SearchSort schSrt;
	int choice;

	cout << "Welcome to Search and Sort please make a selection";

	do
	{
		choice = intMenu("1. Perform linear search on unsorted data\n"
						 "2. Sort unsorted data\n"
				 		 "3. Perform a binary search on sorted data\n"
				  		 "4. Quit\n",
						 false, 4, 1, true);

		if (choice == 1) 
		{ 
			schSrt.loadUnsortedData();						//Load unsorted file data into the vectors and perform linear search
			schSrt.startLinear(schSrt.getUnsorted());		//Start the linear search using the unsorted file names
		}
		if (choice == 2)
		{
			schSrt.loadUnsortedData();						//Load the unsorted data into the vectors and then sort the file
			schSrt.sortFile();								//using quick sort
		}
		if (choice == 3)
		{	
			bool dataLoaded = schSrt.loadSortedData();						//Load the sorted data into the vectors and perform a binary search
			if (dataLoaded) { schSrt.startBinary(schSrt.getSorted()); }		//using the user entered file names.
		}

	} while (choice != 4);

	return 0;
}