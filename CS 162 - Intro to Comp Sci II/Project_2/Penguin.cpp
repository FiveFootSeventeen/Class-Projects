/*********************************************************************
** Class Name: Penguin
** Author: Jacob Leno
** Date: 10/17/17
** Description: This is the implementation file for the Penguin class
** this class defines the member variables for Penguin objects. The
** Penguin class inherits from the Animal class.
*********************************************************************/

#include "Penguin.hpp"

Penguin::Penguin()
{
	age = 1;
	cost = 1000;
	numberOfBabies = 5;
	baseFoodCost = 1.0;
	payoff = 0.10;

}

Penguin::~Penguin()
{

}