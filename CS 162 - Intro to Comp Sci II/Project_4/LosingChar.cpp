/*********************************************************************
** Class Name: LosingChar
** Author: Jacob Leno
** Date: 11/17/17
** Description: This is the function implementation file for the LosingChar
** class it contains the function definitions for the class
*********************************************************************/

#include "LosingChar.hpp"

/*********************************************************************
**  LosingChar destructor : Deletes any DA mem allocated to the LosingChar
** object when it goes out of scope.
*********************************************************************/

LosingChar::~LosingChar()
{
	lostStack *garbage;
	while (top)
	{
		garbage = top;
		delete top->losingChar;
		top = top->next;
		delete garbage;
	}
}

/*********************************************************************
**  push : Pushes the character sent to it as a Character* argument onto
** its stack.
*********************************************************************/

void LosingChar::push(Character* characterIn)
{
	if (!top)
	{
		top = new lostStack(characterIn);
	}
	else
	{
		top = new lostStack(characterIn, top);
	}
}

/*********************************************************************
**  pop : Pops the current character pointed to by top off of the stack
*********************************************************************/

void LosingChar::pop(Character *&characterOut)
{
	if (top)
	{
		lostStack *temp = top;
		characterOut = top->losingChar;
		top = top->next;
		delete temp;
	}
}

/*********************************************************************
**  isEmpty : returns true if top is equal to nullptr
*********************************************************************/

bool LosingChar::isEmpty() const
{
	return top == nullptr;
}