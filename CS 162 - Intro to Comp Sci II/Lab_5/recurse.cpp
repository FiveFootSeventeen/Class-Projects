/*********************************************************************
** Program Name: Recursion
** Author: Jacob Leno
** Date: 10/20/17
** Description: These are the function definitions for the recurse.hpp
** file used in the Recursion program.
*********************************************************************/

#include "recurse.hpp"

/*********************************************************************
** reverse Function: This function outputs the contents of a string
** one letter at a time by starting at the last letter in the string
** and calling itself using a substring of the string that is one letter
** less until it reaches its base case.
*********************************************************************/
void reverse(string reversed)
{
	int length = reversed.length() - 1;

	if (length == 0) //Base case
	{
		cout << reversed.at(length);
	}
	else
	{
		cout << reversed.at(length);
		reverse(reversed.substr(0, (reversed.length() - 1))); //Call itself with a substring that is one letter less and original
	}

}

/*********************************************************************
** arraySum Function: This function works by taking a pointer to an array
** and the amount of elements in that array and calling itself repeatedly
** until it reaches its base case. Each time is called it adds the current
** element in the array and calls itself giving the next smallest element
** as the argument.
*********************************************************************/
int arraySum(int * arr, int elements)
{
	int sum;
	if (elements == 1)	//Base case
	{
		sum = arr[0];
	}
	else
	{
		sum = arr[elements - 1] + arraySum(arr, elements - 1);
	}

	return sum;
}

/*********************************************************************
** triangleNumber Function: This takes an integer parameter and calculates
** the triangular number of that integer by calling itself until it reaches
** its base case. If the number is greater than 0 it adds the current number
** and calls itself giving the number less one as an argument. 
** If the number is less than 0 it adds the current number
** and calls itself giving the number plus one as an argument. 
*********************************************************************/
int triangleNumber(int num)
{
	int total;
	if (num == 0)	//Base case
	{
		return 0;
	}
	if (num > 0)
	{
		total = num + triangleNumber(num - 1);
	}
	if (num < 0)
	{
		total = num + triangleNumber(num + 1);
	}
	return total;
}


