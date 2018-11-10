/*********************************************************************
** Function Name: checkInt
** Author: Jacob Leno
** Date: 09/29/17
** Description: checkInt is sent a string and checks it for an integer
** if the string contains an integer and nothing else it returns true
** if the string contains letters or anything else it returns false.
** The function will also return false if the number entered is greater
** than 9 digits long to avoid errors.
*********************************************************************/

#include <string>
#include <cstdlib>
#include "checkInt.hpp"
using std::string;



bool checkInt(string strValue)
{
	if (string::npos != strValue.find_first_of("0123456789"))	//Does the string contain a number
	{
		int pos = strValue.find_first_of("0123456789");		//If it does record its position in the string

		if (pos > 0)	
		{
			if (strValue.find_first_of("-") == (pos - 1))	//Check to see if there is a negative sign before the number found, 
			{												//if there is decrease the value of pos by 1
				pos -= 1;
			}
		}
		string sub = strValue.substr(pos, string::npos);	//Create a substring starting at the number to the end of the file 

		if (sub.length() < 10)								//Do not store the variable in firstInt if it is greater than 9 digits long
		{
			int firstInt = std::stoi(sub, nullptr, 10);			//so stoi can isolate the number and convert it to an integer

			if ((std::to_string(firstInt).length()) == strValue.length())	//Is this number the only thing in the string? If so return true
			{
				return true;
			}
		}
	}
	
	return false;
}