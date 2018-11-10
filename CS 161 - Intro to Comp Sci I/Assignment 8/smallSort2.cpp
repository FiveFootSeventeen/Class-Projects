/*********************************************************************
** Author: Jacob Leno
** Date: 08/03/17
** Description: Assignment 8a - This function takes three int pointer variables
** passed by reference as arguments and uses pointers to sort their addresses
** into ascending order.
*********************************************************************/


void smallSort2(int *a, int *b, int *c) //Function arguments must be passed by reference,
{										//it uses 3 integer pointers as parameters.
	int temp;	//Variable for storing values temporarily.						
										
	if (*b > *a && *b > *c)				
	{
		temp = *c;
		*c = *b;
		*b = temp;
	}
	if (*a > *c && a > b)
	{
		temp = *c;
		*c = *a;
		*a = temp;
	}
	if (*a > *b)
	{
		temp = *b;
		*b = *a;
		*a = temp;
	}

}