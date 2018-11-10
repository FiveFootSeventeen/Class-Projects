/*********************************************************************
** Class Name: Student
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the implementation file for the Student class
** this class defines the member variables for Student objects.
*********************************************************************/

#include "Student.hpp"

/*********************************************************************
** do_work Function: This function prints a message with the name of the
** Student and a random number of hours that they did homework for.
*********************************************************************/
void Student::do_work()
{
	std::cout << this->name << " did " << (rand() % 40 + 1) << " hours of homework." << std::endl;
}
