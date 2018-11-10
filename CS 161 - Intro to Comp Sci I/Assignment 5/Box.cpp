/*********************************************************************
** Author: Jacob Leno
** Date: 07/19/17
** Description: Assignment 5a - This is the class implementation file for
** the box class, it contains the member functions for the class.
*********************************************************************/


#include "Box.hpp"

Box::Box()
{
	setLength(1.0);
	setWidth(1.0);
	setHeight(1.0);
}

Box::Box(double heightIn, double widthIn, double lengthIn)
{
	setHeight(heightIn);
	setWidth(widthIn);
	setLength(lengthIn);
}

void Box::setHeight(double heightIn)
{
	height = heightIn;
}

void Box::setWidth(double widthIn)
{
	width = widthIn;
}

void Box::setLength(double lengthIn)
{
	length = lengthIn;
}

double Box::calcVolume()			//Calculate the volume of the box
{
	return height * width * length;
}

double Box::calcSurfaceArea()		//Calculate the surface area based on the values of the given variables
{
	return (height * width) * 2 + (width * length) * 2 + (height * length) * 2;
}


