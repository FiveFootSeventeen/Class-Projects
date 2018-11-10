/*********************************************************************
** Project Name: Stack and Queue STL Demo
** Author: Jacob Leno
** Date: 11/25/17
** Description: Demonstrates the use of the stack and queue ATD in the
** Standard Template Library.
*********************************************************************/

#include "queueStack.hpp"
#include "menu.hpp"

#include <queue>

using std::queue;


int main(int argc, char **argv)
{
	int choice;

	do {
		choice = intMenu("1. Queue Container"
					   "\n2. Stack Container"
					   "\n3. End Program",
					   false, 3, 1, true,
					   "This is a demonstration of STL containers,\nwhich would you like to see demonstrated?");
		
		if (choice == 1)
		{
			queueMenu();
		}
		if (choice == 2)
		{
			stackMenu();
		}

	} while (choice != 3);

	return 0;
}