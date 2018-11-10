/*********************************************************************
** Author: Jacob Leno
** Date: 07/28/17
** Description: Assignment 7b - This is the class implementation file for
** the Person class, it contains the member functions for the class.
*********************************************************************/

#include "Person.hpp"
#include <string>

Person::Person() //Default constructor
{
	name = "";
	age = 0;
}

Person::Person(std::string nameIn, double ageIn) //Constructor that sets the age and name to variables assigned at initialization.
{
	name = nameIn;
	age = ageIn;
}

double Person::getAge() //Returns the age data member
{
	return age;
}

std::string Person::getName() //Returns the name data member
{
	return name;
}