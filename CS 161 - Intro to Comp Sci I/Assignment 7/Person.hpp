/*********************************************************************
** Author: Jacob Leno
** Date: 07/28/17
** Description: Assignment 7b - Header file for the person class. This class
** has two data members that store the age and name of a person.
*********************************************************************/

#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>

class Person
{
private:
	std::string name;
	double age;

public:
	Person(); //Default Constructor
	Person(std::string name, double age); //Constructor that sets the age and name to variables assigned at initialization.
	std::string getName(); //Returns the name data member
	double getAge(); //Returns the age data member

};


#endif