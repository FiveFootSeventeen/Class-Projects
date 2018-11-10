/*********************************************************************
** queueStack Functions
** Author: Jacob Leno
** Date: 11/25/17
** Description: Header file for the queueStack functions.
*********************************************************************/

#include "menu.hpp"

#include <queue>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stack>
#include <list>

using std::cout;
using std::endl;

#ifndef QUEUESTACK_HPP
#define QUEUESTACK_HPP

void queueMenu();
void stackMenu();

void beginQueue(int, int, int, std::queue<int>&);
void displayValues(std::queue<int>);
void displayLengths(int, double);
void emptyQueue(std::queue<int> &);
void beginStack(std::string);
void displayPalindrome(std::string);

#endif


