/*********************************************************************
** Author: Jacob Leno
** Date: 07/19/17
** Description: Assignment 5b - This is the header file for the Taxicab
** class declaration. This class takes x and y coordinates that a taxicab
** has traveled, returns those coordinates, and the distance traveled.
*********************************************************************/

#ifndef TAXICAB_HPP
#define TAXICAB_HPP

class Taxicab
{
private:
	int x;
	int y;
	int traveled;

public:
	Taxicab();					//Default constructor
	Taxicab(int x, int y);		//Constructor that accepts an x and y coordinate
	int getXCoord();
	int getYCoord();
	int getDistanceTraveled();	//This member function will return the total distance traveled by the taxi
	void moveX(int x);
	void moveY(int y);

};


#endif