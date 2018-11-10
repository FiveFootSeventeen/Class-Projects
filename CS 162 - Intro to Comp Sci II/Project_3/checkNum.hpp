/*********************************************************************
** Function Name: checkNum
** Author: Jacob Leno
** Date: 10/20/17
** Description: checkInt is sent a string and checks it for an integer
** if the string contains an integer and nothing else it returns true
** if the string contains letters or anything else it returns false.
** checkDec is sent a string and checks it to make sure it is a good 
** decimal number. If it is it returns true.
*********************************************************************/

#include <string>
#include <cstdlib>

using std::string;

#ifndef CHECKINT_HPP
#define CHECKINT_HPP

bool checkInt(std::string strValue);

bool checkDec(std::string strValue);


#endif