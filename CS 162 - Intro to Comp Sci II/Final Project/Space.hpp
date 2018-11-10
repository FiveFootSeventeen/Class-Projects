/*********************************************************************
** Class Name: Space
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the header file for the Space class.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Map.hpp"
#include "names.hpp"

#include <string>

class Space
{
public:
	Space();
	virtual ~Space();
	virtual void initializeMap(std::string) = 0;
	virtual Space* getLeft() { return left; }
	virtual Space* getRight() { return right; }
	virtual Space* getTop() { return top; }
	virtual Space* getBottom() { return bottom; }
	virtual void setLeft(Space *left) { this->left = left; }
	virtual void setRight(Space *right) { this->right = right; }
	virtual void setTop(Space *top) { this->top = top; }
	virtual void setBottom(Space *bottom) { this->bottom = bottom; }
	virtual Map* getSpaceMap() { return spaceMap; }

protected:
	Space *top, *left, *right, *bottom;
	Map *spaceMap;

};

#endif