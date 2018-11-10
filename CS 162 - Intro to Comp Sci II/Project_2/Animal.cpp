/*********************************************************************
** Class Name: Animal
** Author: Jacob Leno
** Date: 10/17/17
** Description: This is the implementation file for the Animal class
** this class defines the member variables for Animal objects. The
** Tiger, Penguin, and Turtle classes inherit from this class.
*********************************************************************/

#include "Animal.hpp"

Animal::Animal()
{
	age = 1;
	cost = 100;
	numberOfBabies = 1;
	baseFoodCost = 1;
	payoff = 1;
}

Animal::~Animal()
{

}