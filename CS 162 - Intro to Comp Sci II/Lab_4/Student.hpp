/*********************************************************************
** Class Name: Student
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the header file for the Student class. This
** class inherits from the Person class.
*********************************************************************/

#include "Person.hpp"

#ifndef STUDENT_HPP
#define STUDENT_HPP

class Student : public Person
{
public:
	Student() : Person("", 20), GPA(4.0) {}					//Default constructor w/ initialization list
	~Student() {}											//Destructor
	Student(double GPAIn, std::string nameIn, int ageIn) :	//Constructor w/ initialization list
		Person(nameIn, ageIn), GPA(GPAIn) {}

	virtual void do_work();
	//Set and Get functions for the Student class
	void setGPA(double GPAIn) { GPA = GPAIn; }
	double getGPA() { return GPA; }
	int getType() { return TYPE; }

protected:
	static const int TYPE = 2;
	double GPA;

};

#endif