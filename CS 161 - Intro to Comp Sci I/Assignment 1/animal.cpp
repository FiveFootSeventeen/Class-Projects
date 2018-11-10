/***************************************
** Author: Jacob Leno
** Date: 06/26/17
** Description: Assignment 1, simple program
that asks the user for favorite animal as 
input and outputs a string with that animal 
***************************************/

#include <iostream>
#include <string>

// a simple example program
int main()
{
	std::string faveAnimal;

	std::cout << "Please enter your favorite animal." << std::endl;
	std::cin >> faveAnimal;
	std::cout << "Your favorite animal is the " << faveAnimal;
	std::cout << "." << std::endl;


	return 0;
}

