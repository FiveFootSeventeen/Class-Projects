/*********************************************************************
** Class Name: Instructor
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the implementation file for the Instructor class
** this class defines the member variables for Instructor objects.
*********************************************************************/

#include "Instructor.hpp"


/*********************************************************************
** do_work Function: This function prints a message with the name of the
** instructor and a random number of hours that they graded papers for.
*********************************************************************/
void Instructor::do_work()
{
	std::cout << this->name << " graded papers for " << (rand() % 40 + 1) << " hours." << std::endl;
}