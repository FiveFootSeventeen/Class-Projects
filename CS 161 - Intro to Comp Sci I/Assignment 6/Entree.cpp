/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6b - This is the class implementation file for
** the Entree class, it contains the member functions for the class.
*********************************************************************/

#include "Entree.hpp"
#include <string>

Entree::Entree()		//Default constructor for Entree
{
	dish = "";
	calories = 0;
}

Entree::Entree(std::string dishIn, int caloriesIn)	//Initialize variables dish and calories
{
	dish = dishIn;
	calories = caloriesIn;
}

std::string Entree::getEntree()
{
	return dish;
}

int Entree::getCalories()
{
	return calories;
}