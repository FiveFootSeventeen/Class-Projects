/*********************************************************************
** Author: Jacob Leno
** Date: 07/29/17
** Description: Assignment 7a - This is the findMedian function it takes 
** two integer parameters. One parameter is an array of numbers and the other
** is the size of the array. From these two parameters it finds the median
** and returns that number as a double.
*********************************************************************/

#include <algorithm>


double findMedian(int numList[], int size) //Takes two parameters as input an int array and its size as an int
{										   //and returns the median of the numbers stored in the array.
	std::sort(numList, numList + size);
	if (size % 2 == 0)
	{
		return ((numList[size / 2] + numList[(size / 2) - 1]) / 2.0);
	}
	else
	{
		return numList[size / 2];
	}

}