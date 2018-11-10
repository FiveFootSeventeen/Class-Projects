/*********************************************************************
** Author: Jacob Leno
** Date: 08/03/17
** Description: Assignment 8b - This function takes a pointer to a dynamically
** allocated array of doubles as a reference and the size of that array.
** It then creates a new dynamic array twice the size of the original with
** the original variables appearing twice and changes the pointer address of the
** old array to the new one.
*********************************************************************/
#include <iostream>


void repeatArray(double *&myArray, int size) //repeatArray accepts a dynamically allocated array by pointer reference and its size
{
	double *tempArray = new double[2 * size]; //Create a new DA array twice the size of myArray
	int accum = 0;

	for (int i = 0; i < 2; i++)				//Loop through myArray twice using an accumulator to assign the values
	{										//of myArray to tempArray
		for (int j = 0; j < size; j++)
		{
			tempArray[accum] = myArray[j];
			accum += 1;
		}
		
	}

	delete[]myArray;
	myArray = tempArray;		//Cause the address the myArray pointer is referencing to be equal to tempArray
	tempArray = NULL;		//Change the address of tempArray to null and delete


}