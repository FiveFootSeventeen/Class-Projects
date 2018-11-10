/*********************************************************************
** Author: Jacob Leno
** Date: 07/19/17
** Description: Assignment 5a - This is the header file for the box class
** declaration. This class takes a height, width, and length and uses that
** information to calculate a boxes volume and surface area.
*********************************************************************/


#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:
	double height;
	double length;
	double width;

public:
	Box();													//Default constructor for the Box class
	Box(double heightIn, double widthIn, double lengthIn);	//Constructor that accepts the box's length, width and height
	void setHeight(double heightIn);
	void setWidth(double widthIn);
	void setLength(double lengthIn);
	double calcVolume();
	double calcSurfaceArea();

};

#endif