/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6b -This is the header file for the Entree class
** declaration. This class takes and stores the name of an Entree as a string
** and the amount of calories in that entree as an integer. It will also output
** the calories and entree.
*********************************************************************/

#ifndef ENTREE_HPP
#define ENTREE_HPP
#include <string>

class Entree
{
private:
	std::string dish;
	int calories;

public:
	Entree();	//Default constructor for Entree
	Entree(std::string dish, int calories);		//Initialize variables dish and calories
	std::string getEntree();
	int getCalories();
};


#endif