/*********************************************************************
** Class Name: doubleList
** Author: Jacob Leno
** Date: 11/03/17
** Description: This is the Header file for the DoubleList class Call 
** the menu function on a DoubleList object to start the program for 
** creating a doubly-linked list.
*********************************************************************/

#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP

#include "Node.hpp"
#include "menu.hpp"
#include <iostream>

using std::cout;
using std::endl;

class DoubleList
{
protected:
	Node *head, *tail;

public:
	DoubleList() : head(nullptr), tail(nullptr) {}
	~DoubleList();
	void menu();
	void addHead(int);
	void addTail(int);
	void removeHead();
	void removeTail();
	void traverse();
	void traverseRev();
	void printTail();
	void printHead();

};

#endif
