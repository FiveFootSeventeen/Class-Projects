/*********************************************************************
** Function name: determinant
** Author: Jacob Leno
** Date: 09/29/17
** Description: This function accepts a pointer to a array of integer
** pointers and the size of the matrix (either 3 for 3x3 or 2 for 2x2)
** and uses the values found in the array to calculate its determinant
** which it returns as an integer.
*********************************************************************/

#include "determinant.hpp"

int determinant(int **arr, int size)
{
	int dtmnt;
	if (size == 2)
	{
		dtmnt = ((arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]));
	}
	else
	{ //Equation for 3x3 determinant  |B|=a(ek-fh)-b(dk-fg)+c(dh-eg)
		dtmnt = (arr[0][0] * (arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1])) -
			(arr[0][1] * (arr[1][0] * arr[2][2] - arr[1][2] * arr[2][0])) +
			(arr[0][2] * (arr[1][0] * arr[2][1] - arr[1][1] * arr[2][0]));
	}
	return dtmnt;
}
