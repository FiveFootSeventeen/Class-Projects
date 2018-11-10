/*********************************************************************
** Class Name: Dungeon
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the header file for the Dungeon class.
*********************************************************************/

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "Space.hpp"

class Dungeon : public Space
{
public:
	~Dungeon();
	Dungeon() {} ;
	Dungeon(std::string mapName, int level, Space *right = nullptr, Space *left = nullptr);
	void initializeMap(std::string);
	Space* getLeft() { return left; }
	Space* getRight() { return right; }
	Space* getTop() { return top; }
	Space* getBottom() { return bottom; }
	int getLevel() { return level; }
	void setLeft(Space *left) { this->left = left; }
	void setRight(Space *right) { this->right = right; }
	void setTop(Space *top) { this->top = top; }
	void setBottom(Space *bottom) { this->bottom = bottom; }
	Map* getSpaceMap() { return spaceMap; }

protected:
	int level;

};

#endif