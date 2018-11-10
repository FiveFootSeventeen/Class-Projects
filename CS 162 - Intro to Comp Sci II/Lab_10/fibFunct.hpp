/*********************************************************************
** Fibonacci Functions
** Author: Jacob Leno
** Date: 11/27/17
** Description: Header file for the functions in the fibonacci functions 
** program
*********************************************************************/

#ifndef FIBFUNCT_HPP
#define FIBFUNCT_HPP

#include "menu.hpp"

#include <time.h>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

void fibMenu();
void fibRecurse(int terms);
void fibIterate(int terms);
void printNumber(unsigned long number);
unsigned long  recurse(unsigned long  terms);

#endif 
