/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6a - This is the header file for the quadric class
** declaration. This class takes values for a, b, and c and uses them to 
** calulate the number of real zeros. It also takes a value for x and 
** uses it to determine the value of the quadratic function at that value for x.
*********************************************************************/

#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

class Quadratic
{
private:
	double a;
	double b;
	double c;

public:
	Quadratic();	//Default constructor for Quadratic, sets all values edual to 1.0
	Quadratic(double a, double b, double c);	//Constructor for Quadratic, takes three values as parameters and sets a, b, and c equal to them.
	double getA();
	double getB();
	double getC();
	void setA(double a);
	void setB(double b);
	void setC(double c);
	double valueFor(double x);	//Calculate the value of the quadratic function for the given value of x.
	int numRealRoots();	// This function takes the variables a, b, and c and uses them to determine how many real roots the quadratic function has.

};

#endif