/*********************************************************************
** Program Name: War Game
** Author: Jacob Leno
** Date: 10/12/17
** Description: Main function for War Game. All that this function does
** is create a Game class object and call its startGame function. Once
** the game starts simply follow the prompts on the screen and enter all
** choices as integers.
*********************************************************************/

#include "intMenu.hpp"
#include "checkInt.hpp"
#include "Game.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Game warGame;
	

	warGame.startGame();


	return 0;
}