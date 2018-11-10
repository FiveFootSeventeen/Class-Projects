/*********************************************************************
** Author: Jacob Leno
** Date: 07/13/17
** Description: Assignment 4b - This program contains a function that 
** sorts three reference integer variables passed as arguments from smallest
** to largest with "a" being the lowest and "c" being the highest
*********************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void smallSort(int &a, int &b, int &c);

/*
int main() {
	int one, two, three;

	cout << "Enter three numbers and I will rearrange them according to their size:" << endl;
	cin >> one >> two >> three;
	smallSort(one, two, three);
	cout << "The numbers in ascending order are " << one << " " << two << " " << three << endl;

	return 0;
}
*/

void smallSort(int &a, int &b, int &c)	// smallSort accepts three reference variables as parameters
{										// it checks to see if b and a are the largest, if they are not
	int temp;							// it assumes c is largest. Finally it checks to see which is larger
										// between a and b and sorts them accordingly. The variables are sorted so 
	if (b > a && b > c)					// that c is largest and a is smallest.
	{
		temp = c;
		c = b;
		b = temp;
	}
	else if (a > c && a > b)
	{
		temp = c;
		c = a;
		a = temp;
	}
	else if (a > b)
	{
		temp = b;
		b = a;
		a = temp;
	}
}
