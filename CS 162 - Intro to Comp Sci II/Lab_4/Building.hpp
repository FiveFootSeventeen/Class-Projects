/*********************************************************************
** Class Name: Building
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the header file for the Building class. There
** is no implementation file for this class. All the member functions
** for the Building class are defined within this header file.
*********************************************************************/

#include <string>

#ifndef BUILDING_HPP
#define BUILDING_HPP

class Building
{
public:
	Building() : size(50), address(" "), name(" ") {}				//Default Constructor w/ initialization list
	~Building() {}													//Destructor
	Building(int size, std::string address, std::string name) :		//Constructor w/ initialization list
		size(size), address(address), name(name){}

	//Set and Get functions for Building class
	void setSize(int sizeIn) { size = sizeIn; }
	int getSize() { return size; }
	void setAddress(std::string addressIn) { address = addressIn; }
	std::string getAddress() { return address; }
	void setName(std::string nameIn) { name = nameIn; }
	std::string getName() { return name; }
	int getType() { return TYPE; }

	
protected:
	static const int TYPE = 3;
	int size;
	std::string address, name;

};

#endif