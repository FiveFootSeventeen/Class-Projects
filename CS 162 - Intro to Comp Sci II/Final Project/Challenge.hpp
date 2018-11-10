/*********************************************************************
** Class Name: Challenge
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the header file for the Challenge class.
*********************************************************************/

#ifndef CHALLENGE_HPP
#define CHALLENGE_HPP

#include "Space.hpp"

class Challenge : public Space
{
public:
	~Challenge();
	Challenge() {};
	Challenge(std::string mapName);
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