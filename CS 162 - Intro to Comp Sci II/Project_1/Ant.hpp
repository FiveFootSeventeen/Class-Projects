/*********************************************************************
** Program Name: Langton's Ant
** Author: Jacob Leno
** Date: 10/04/17
** Description: Header file for the Ant class
*********************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

class Ant
{
private:
	int rows, columns;
	int antLoc[2];
	int antDir = 0;
	char ** gameBoard = nullptr;
	void changeDir(char heading);
	void setColor();	

public:
	Ant();
	Ant(int rowsIn, int columnsIn, int startingRowIn, int startingColumnIn);
	void moveAnt();
	void displayBoard();
	~Ant();
};


#endif