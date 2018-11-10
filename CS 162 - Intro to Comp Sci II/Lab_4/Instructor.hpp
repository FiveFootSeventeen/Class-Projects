/*********************************************************************
** Class Name: Instructor
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the header file for the Instructor class. This
** class inherits from the Person class.
*********************************************************************/

#include "Person.hpp"

#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

class Instructor : public Person
{
public:
	Instructor() : Person("", 30), rating(5.0) {}					//Default constructor w/ initialization list
	~Instructor() {}												//Destructor
	Instructor(double ratingIn, std::string nameIn, int ageIn) :	//Constructor w/ initialization list
		Person(nameIn, ageIn), rating(ratingIn) {}
	
	virtual void do_work();
	//Set and Get functions for the Instructor class
	void setRating(int ratingIn) { rating = ratingIn; }
	double getRating() { return rating; }
	int getType() { return TYPE; }

protected:
	static const int TYPE = 1;
	double rating;

};

#endif