/*********************************************************************
** Author: Jacob Leno
** Date: 07/19/17
** Description: Assignment 5b - This is the class implementation file for
** the Taxicab class, it contains the member functions for the class. 
*********************************************************************/

#include "Taxicab.hpp"
#include <cmath>

Taxicab::Taxicab()
{
	x = 0;
	y = 0;
	traveled = 0;
}

Taxicab::Taxicab(int xIn, int yIn)
{
	x = xIn;
	y = yIn;
	traveled = 0;
}

int Taxicab::getXCoord()
{
	return x;
}

int Taxicab::getYCoord()
{
	return y;
}

int Taxicab::getDistanceTraveled()
{
	return traveled;
}

void Taxicab::moveX(int xIn)
{
	x += xIn;						//Add the distance moved in the x coordinate to x
	traveled += std::abs(xIn);		//Add the absolute value of the x distance to the traveled function
}

void Taxicab::moveY(int yIn)
{
	y += yIn;						//Add the distance moved in the y coordinate to y
	traveled += std::abs(yIn);		//Add the absolute value of the y distance to the traveled function
}