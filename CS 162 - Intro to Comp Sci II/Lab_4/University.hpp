/*********************************************************************
** Class Name: University
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the header file for the University class.
*********************************************************************/

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <climits>
#include <fstream>
#include <iomanip>

#include "Building.hpp"
#include "Person.hpp"
#include "Student.hpp"
#include "Instructor.hpp"
#include "menu.hpp"

using std::vector;
using std::shared_ptr;
using std::cout;
using std::cin;
using std::endl;

#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP

class University
{
public:
	University();
	~University() {}
	void menu();

protected:
	//Member Variables
	vector<shared_ptr<Building>> buildingVector;
	vector<shared_ptr<Person>> personVector;
	std::ofstream outFile;
	std::ifstream inFile;

	std::string name = "Oregon State University";
	int buildings, people;

	int length, type, tempSize, tempAge;  //Scratch space variables
	std::string tempName, tempAddress;	  //used for reading and writing
	double tempRating, tempGPA;			  //information to files



	//Member Functions
	void doWork();
	void storeData();
	void loadData();
	void printBuildings();
	void printPeople(bool withNumbers = false);
	void addBuildings();
	void addPeople();

};


#endif