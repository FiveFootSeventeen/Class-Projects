/*********************************************************************
** Class Name: Person
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the header file for the Person class. The Instructor
** and Student classes inherit from this class.
*********************************************************************/

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

#ifndef PERSON_HPP
#define PERSON_HPP

class Person
{
public:
	Person() : age(25), name(" ") {}									//Default constructor w/ initialization list
	Person(std::string nameIn, int ageIn) : name(nameIn), age(ageIn) {}	//Constructor w/ intialization list
	~Person() {}														//Destructor

	virtual void do_work();
	//Set and Get functions for the Person class
	void setName(std::string nameIn) { name = nameIn; }
	std::string getName() { return name; }
	void setAge(int ageIn) { age = ageIn; }
	int getAge() { return age; }
	virtual int getType() { return TYPE; }

protected:
	unsigned seed = int(time(0));
	static const int TYPE = 0;
	std::string name;
	int age;

};

#endif