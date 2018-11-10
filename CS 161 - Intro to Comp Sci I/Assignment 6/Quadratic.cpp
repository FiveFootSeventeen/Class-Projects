/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6a - This is the class implementation file for
** the Quadric class, it contains the member functions for the class.
*********************************************************************/

#include <cmath>
#include "Quadratic.hpp"
using std::abs;
using std::pow;

Quadratic::Quadratic() //Default constructor for Quadratic, sets all values edual to 1.0
{
	a = 1.0;
	b = 1.0;
	c = 1.0;
}

Quadratic::Quadratic(double aIn, double bIn, double cIn) //Constructor for Quadratic, takes three values as parameters and sets a, b, and c equal to them.
{
	a = aIn;
	b = bIn;
	c = cIn;
}

double Quadratic::getA()
{
	return a;
}

double Quadratic::getB()
{
	return b;
}

double Quadratic::getC()
{
	return c;
}

void Quadratic::setA(double aIn)
{
	a = aIn;
}

void Quadratic::setB(double bIn)
{
	b = bIn;
}

void Quadratic::setC(double cIn)
{
	c = cIn;
}

double Quadratic::valueFor(double x)	//Calculate the value of the quadratic function for the given value of x.
{
	return (a * (pow(x, 2)) + (b * x) + c);		
}

int Quadratic::numRealRoots()							// This function takes the variables a, b, and c and uses them to 
{														// determine how many real roots the quadratic function has.
	double discriminant = pow(b, 2) - (4 * a * c);

	if (abs(discriminant <= 0.00001 && discriminant >= -0.00001))
	{
		return 1;				//If the discriminant is 0 return 1 root.
	}
	if (discriminant > 0.00001)
	{
		return 2;				//If the discriminant is greater than 0 return 2 roots.
	}
	if (discriminant < -0.00001)
	{
		return 0;				//If the discriminant is negative the function has no real roots.
	}
}