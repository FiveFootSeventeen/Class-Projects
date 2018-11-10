/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6b - This is the class implementation file for
** the EntreeSampler class, it contains the member functions for the class.
*********************************************************************/

#include "EntreeSampler.hpp"
#include <iostream>

using std::cout;
using std::endl;

EntreeSampler::EntreeSampler() //Default constructor for EntreeSampler class
{							   //the values for the individual Entree objects are initialized in the Entree class.

}

EntreeSampler::EntreeSampler(Entree ent1In, Entree ent2In, Entree ent3In, Entree ent4In)   //Initialize the four Entree objects in the EntreeSampler class
{
ent1 = ent1In;
ent2 = ent2In;
ent3 = ent3In;
ent4 = ent4In;
}


void EntreeSampler::listEntrees() //Output the four entrees in the class to the console
{
	cout << ent1.getEntree() << endl << ent2.getEntree() << endl << ent3.getEntree() << endl << ent4.getEntree() << endl;
}

int EntreeSampler::totalCalories() //Add together the total calories in the class and return the value as an integer
{
	return (ent1.getCalories() + ent2.getCalories() + ent3.getCalories() + ent4.getCalories());
}