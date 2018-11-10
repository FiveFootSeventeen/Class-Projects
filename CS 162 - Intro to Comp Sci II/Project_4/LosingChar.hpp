/*********************************************************************
** Class Name: LosingChar
** Author: Jacob Leno
** Date: 11/17/17
** Description: This is the header file for the LosingChar class
*********************************************************************/

#ifndef LOSINGCHAR_HPP
#define LOSINGCHAR_HPP

#include "Character.hpp"

class LosingChar
{
protected:
	//Variables
	struct lostStack
	{
		Character *losingChar;
		lostStack *next;
		lostStack(Character *losingChar, lostStack *next = nullptr)
		{
			this->next = next;
			this->losingChar = losingChar;
		}
	};

	lostStack *top;
public:
	//Functions
	~LosingChar();
	LosingChar() { top = nullptr; }
	void push(Character*);
	void pop(Character*&);
	bool isEmpty() const;
};

#endif