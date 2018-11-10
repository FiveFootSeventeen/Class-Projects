/*********************************************************************
** Author: Jacob Leno
** Date: 07/22/17
** Description: Assignment 6b - This is the header file for the EntreeSampler class
** declaration. This class takes four objects of type Entree. It will 
** output the entrees stored, one on each line, using the listEntrees function.
** It will also add up and return the total calories in each entree stored
** using the totalCalories function.
*********************************************************************/

#include "Entree.hpp"
#include <string>

class EntreeSampler
{
private:
	Entree ent1;
	Entree ent2;
	Entree ent3;
	Entree ent4;

public:
	EntreeSampler();	//Default constructor for EntreeSampler class
	EntreeSampler(Entree ent1In, Entree ent2In, Entree ent3In, Entree ent4In);	//Initialize the four Entree objects in the EntreeSampler class
	void listEntrees();		//Output the four entrees in the class to the console
	int totalCalories();	//Add together the total calories in the class and return the value as an integer

};