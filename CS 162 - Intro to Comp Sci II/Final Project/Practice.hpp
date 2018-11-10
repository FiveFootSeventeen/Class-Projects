/*********************************************************************
** Class Name: Practice
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the header file for the practice class, this is
** a derived class from Space.
*********************************************************************/

#ifndef PRACTICE_HPP
#define PRACTICE_HPP

#include "Space.hpp"

class Practice :public Space
{
public:
	~Practice();
	Practice() {};
	Practice(std::string mapName);
	void initializeMap(std::string);
	Space* getLeft() { return left; }
	Space* getRight() { return right; }
	Space* getTop() { return top; }
	Space* getBottom() { return bottom; }
	void setLeft(Space *left) { this->left = left; }
	void setRight(Space *right) { this->right = right; }
	void setTop(Space *top) { this->top = top; }
	void setBottom(Space *bottom) { this->bottom = bottom; }
	Map* getSpaceMap() { return spaceMap; }

protected:

};

#endif