/*********************************************************************
** Class Name: SearchSort
** Author: Jacob Leno
** Date: 11/16/17
** Description: Class implementation file for SearchSort. This file contains
** the function definitions for the SearchSort class
*********************************************************************/

#include "SearchSort.hpp"

/*********************************************************************
** loadSortedData: Load the data from the sorted data files into the
** corrosponding vectors
*********************************************************************/

bool SearchSort::loadSortedData()
{
	if (userNames[0].empty() || userNames[1].empty() || userNames[2].empty() || userNames[3].empty())
	{
		cout << "Sorted data has not been initialized" << endl;			//If the data has not been initialized output a message saying so
		return false;													//and return the value false
	}	
	else
	{
		vectorIn(noZero, userNames[0], inOutFile);
		vectorIn(early, userNames[1], inOutFile);
		vectorIn(middle, userNames[2], inOutFile);
		vectorIn(end, userNames[3], inOutFile);
	}
	return true;
}

/*********************************************************************
** loadUnsortedData: Load unsorted data from the files
** into the corrosponding vectors
*********************************************************************/

void SearchSort::loadUnsortedData()
{
	vectorIn(noZero, PROGNAMES[0], inOutFile);
	vectorIn(early, PROGNAMES[1], inOutFile);
	vectorIn(middle, PROGNAMES[2], inOutFile);
	vectorIn(end, PROGNAMES[3], inOutFile);
}

/*********************************************************************
** vectorIn: Input data from a given file name into a given vector.
*********************************************************************/

void SearchSort::vectorIn(vector<int> &vectData, string fileName, fstream& inFile)
{
	inFile.open(fileName, std::ios::in);

	if (inFile.fail())
	{
		cout << fileName << ".txt failed to open!" << endl;
	}

	unsigned i = 0;
	int input;
	while (inFile.peek() != EOF)		//Check to see if the next value is the end of the file, if it is
	{									//stop looping
		input = inFile.get();
		if (input != 32)
		{
			if (i >= vectData.size())			//If i is greater or equal to size then the vector isn't large enough
			{									//add another element to the vector with the value from the file
				vectData.push_back(input - 48);
				i++;
			}
			else 
			{ 
				vectData[i] = input - 48;
				i++; 
			}
		}
	}
	inFile.clear();
	inFile.close();
}

/*********************************************************************
** vectorOut: Take data from a given vector and output it to a given 
** file name, if the file does not exist create a new one.
*********************************************************************/

void SearchSort::vectorOut(vector<int> &vectData, string fileName, fstream& outFile)
{
	outFile.open(fileName, std::ios::out);

	for (unsigned i = 0; i < vectData.size(); i++)
	{
		outFile << vectData[i] << " ";
	}

	outFile.close();
}

/*********************************************************************
** startLinear: Start a linear search using a given string array of file names
** ask the user for a value to search for and use that value for each
** vector to be searched.
*********************************************************************/

void SearchSort::startLinear(const string fileName[])
{
	int key, position;
	key = intMenu("What value would you like to search for?", false, 1000, -1000);
	
	for (int i = 0; i < SIZE; i++)
	{
		position = linearSearch(*listVector[i], key);
		if (position >= 0)
		{
			cout << "Value found in " << fileName[i] << endl;
		}
		else
		{
			cout << fileName[i] << " does not contain the value" << endl;
		}
	}
}

/*********************************************************************
** linearSearch: Perform a linear search on a given vector using a user
** specified key.
*********************************************************************/

int SearchSort::linearSearch(vector<int> vectData, int key) 
{
	for (unsigned i = 0; i < vectData.size(); i++)
	{
		if (vectData[i] == key)
		{
			return i;
		}
	}
	return -1;
}

/*********************************************************************
** sortFile: Sort the unsorted file data using user-specified file names
** if the file names are already in use get another name from the user.
*********************************************************************/

void SearchSort::sortFile()
{
	string fileName;
	bool goodName;

	for (int i = 0; i < SIZE; i++)
	{
		cout << "For the sorted data of the \"" << PROGNAMES[i] << "\" file, what should the filename be?" << endl;
		getline(cin, fileName);
		goodName = true;
		for (int j = 0; j < SIZE; j++)
		{
			if (PROGNAMES[j] == fileName || userNames[j] == fileName) { goodName = false; }		//Check through all the file names, if the user has entered														//one that is already in use ask for another.
		}
		if (!goodName) 
		{ 
			cout << "Enter a different file name that is already in use." << endl; 
			i--;		//Decrement the loop counter to get a different file name.
		}
		else
		{
			quickSort(*listVector[i], 0, listVector[i]->size() - 1);		//A good filename has been found, perform quicksort, storing the data into the vector
			userNames[i] = fileName;										//Add the user specified file name to the array
			vectorOut(*listVector[i], fileName, inOutFile);					//Output the recently sorted vector to the file
			printVector(*listVector[i], i);									//Print the recently sorted vector to the screen
			cout << endl;
		}
	}
}

/*********************************************************************
** quickSort: Performs a recursive quicksort on a vector, must be sent
** the vector's starting location and the value of its final element.
*********************************************************************/

void SearchSort::quickSort(vector<int> &vectData, int start, int end)	//I found this algorithm in a video explaination of the quick sort 
{																		//algorithm on the mycodeschool youtube channel
	if (start < end)													//https://www.youtube.com/watch?v=COk73cpQbFQ&t=146s
	{
		int partitionIndex = partition(vectData, start, end);			//Get the partition value, sending the start and end values
		quickSort(vectData, start, partitionIndex - 1);					//Sort the left half of the partition index
		quickSort(vectData, partitionIndex + 1, end);					//Sort the right half of the partition index
	}
}

/*********************************************************************
** partition: set the pivot element in the array, if the data element
** being examined is less than or equal to the pivot element swap it
** with the partitionIndex value and increment the partitionIndex so 
** it points to the correct place in the vector. Finally swap the value
** at the partition index with the pivot value.
*********************************************************************/

int SearchSort::partition(vector<int> &vectData, int start, int end)
{
	int pivot = vectData[end];								//Initialize the pivot		
	int partitionIndex = start;
	for (int i = start; i < end; i++)
	{
		if (vectData[i] <= pivot)
		{
			swap(vectData[i], vectData[partitionIndex]);	//If the value being examined is less or equal to the pivot swap
			partitionIndex++;								//with the value at the partition index
		}
	}
	swap(vectData[partitionIndex], vectData[end]);			//Swap the partitionIndex value with the pivot value
	return partitionIndex;
}

/*********************************************************************
** swap: Takes two integer values by reference and swaps their value
*********************************************************************/

void SearchSort::swap(int &one, int &two)
{
	int temp = two;
	two = one;
	one = temp;
}

/*********************************************************************
** printVector: Prints the data in a vector sent as an argument to the
** console also displays its filename.
*********************************************************************/

void SearchSort::printVector(vector<int> vectData, int fileName)
{
	cout << userNames[fileName] << " now has ";
	for (unsigned i = 0; i < vectData.size(); i++)
	{
		cout << vectData[i] << " ";
	}
}

/*********************************************************************
** startBinary: Start a binary search using a string array of file names
** sent as an argument. Sorted values must be loaded into the vectors
** before this function is called.
*********************************************************************/

void SearchSort::startBinary(const string fileName[])
{
	int key, position;
	key = intMenu("What value would you like to search for?", false, 1000, -1000);

	for (int i = 0; i < SIZE; i++)
	{
		position = binarySearch(*listVector[i], key);
		if (position >= 0)
		{
			cout << "Value found in " << fileName[i] << endl;
		}
		else
		{
			cout << fileName[i] << " does not contain the value" << endl;
		}
	}
}

/*********************************************************************
** binarySearch: Performs a binary search on sorted data using a vector
** sent as an argument and a user-specified key.
*********************************************************************/

int SearchSort::binarySearch(vector<int> vectData, int key)	//Adapted from an article on binary searches found on 
{															//https://research.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html
	int position = -1;
	int mid, midVal, low = 0;
	int high = vectData.size() - 1;				

	while (low <= high)
	{
		mid = low + ((high - low) / 2);			//Half the high and the low values and set them equal to mid
		midVal = vectData[mid];					//Get the value at mid

		if (key == midVal)						//If the key is equal to the middle value then return its position
		{
			return mid;
		}
		else if (key < midVal)					//If the key is less than the mid value search the lower half of the
		{										//vector by setting high equal to one less than the mid
			high = mid - 1;			
			
		}
		else									//If the key is greater than the mid value than search the upper half
		{										//of the vector by setting low equal to one greater than mid
			low = mid + 1;
		}
	}
	return -1;
}