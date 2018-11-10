/*********************************************************************
** Function Name: checkNum
** Author: Jacob Leno
** Date: 10/20/17
** Description: checkInt is sent a string and checks it for an integer
** if the string contains an integer and nothing else it returns true
** if the string contains letters or anything else it returns false.
** The function will also return false if the number entered is greater
** than 9 digits long to avoid errors. checkDec is a function to check
** if a number is a good decimal. It is sent a string which it checks for 
** numbers and a decimal. If both portions before and after the decimal
** contain numbers it sends it to checkInt to make sure they dont contain
** any letters and returns true if it is a good number.
*********************************************************************/

#include "checkNum.hpp"

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
			int firstInt = std::stoi(sub);			//so stoi can isolate the number and convert it to an integer

			if ((std::to_string(firstInt).length()) == strValue.length())	//Is this number the only thing in the string? If so return true
			{
				return true;
			}
		}
	}
	
	return false;
}

bool checkDec(std::string strValue)
{
	if (strValue.length() < 16)		// Make sure the number is not too big
	{
		if (string::npos != strValue.find_first_of("0123456789"))		//Does the string have digits in it?
		{
			if (string::npos != strValue.find_first_of("."))			//Does the string have a decimal in it?
			{
				int decPoint = strValue.find_first_of(".");				//Where in the string is the decimal located?
				int firstNum = strValue.find_first_of("0123456789");	//Where in the portion is the first number located?
				std::string firstSub = strValue.substr(0, decPoint);	//Create a substing of the first part before the decimal
				if (firstNum < decPoint)								//Does the first number come before the decimal?
				{
					string secondSub = strValue.substr(decPoint + 1, string::npos);	//If it does make a second substring of the rest of the string after the decimal
					if (string::npos != secondSub.find_first_of("0123456789"))		//Does the second substring contain numbers?
					{
						if (checkInt(firstSub) && checkInt(secondSub))				//If the both contain numbers send the to checkInt
						{															//to make sure they both only have numbers and no letters.
							return true;	//If they both only contain numbers the number is a good decimal.
						}
					}
				}
			}
		}
	}
	return false;
}