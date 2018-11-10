/*********************************************************************
** Program Name: Zoo Tycoon
** Author: Jacob Leno
** Date: 10/17/17
** Description: This program is a simulation game that allows the user
** to run a zoo. The zoo is populated with several different animals
** and various events happen day to day that are either good or bad.
** To start the program a Zoo object is created and its beginGame()
** function is called
*********************************************************************/

#include <iostream>

#include "Zoo.hpp"
#include "Tiger.hpp"

using std::endl;
using std::cin;
using std::cout;


int main()
{
	Zoo zooGame;
	
	zooGame.beginGame();

	return 0;
}