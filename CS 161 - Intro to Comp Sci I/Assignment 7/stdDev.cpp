/*********************************************************************
** Author: Jacob Leno
** Date: 07/28/17
** Description: Assignment 7b - This is the stdDev function which takes 
** two parameters. One parameter is an array of class type Person and the other is
** the size of the array as an integer. This function computes the standard
** deviation of the ages in the Person class.
*********************************************************************/
#include "Person.hpp"
#include <cmath>


double stdDev(Person popInfo[], int size) // Find the standard deviation in the age data member and return as a double
{
	double totalDiffSquared = 0.0, //Accumulator for the squared differance of each value in age and the mean
		mean = 0.0; //Accumulator for the mean of each value in age


	for (int i = 0; i < size; i++)
	{
		mean += popInfo[i].getAge();
	}
	mean = mean / size;
	for (int i = 0; i < size; i++)
	{
		totalDiffSquared += std::pow((popInfo[i].getAge() - mean), 2);
	}

	return std::sqrt(totalDiffSquared / size);

}