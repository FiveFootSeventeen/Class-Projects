/*********************************************************************
** Class Name: Gameplay
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the headerfile for the Gameplay class
*********************************************************************/


#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#ifdef _WIN32					
#include <stdlib.h>				
#include <curses.h>
#define CLEAR()	system("CLS")
#elif __linux__
#include <stdio.h>
#include <ncurses.h>
#define CLEAR()	printf("\033[2J");
#else
#warning "Console clearing not supported for this operating system!"
#define CLEAR()	((void) 0)
#endif

#include "Player.hpp"
#include "Map.hpp"
#include "names.hpp"
#include "Practice.hpp"
#include "Challenge.hpp"
#include "Dungeon.hpp"
#include "Space.hpp"
#include "menu.hpp" 

#include <iostream>
#include <chrono>
#include <thread>
#include <climits>
#include <fstream>

class Gameplay
{
public:
	~Gameplay();
	Gameplay() : currentEvent(NOEVENT), dungeons(nullptr){}
	void gameMenu();

private:
	std::fstream inFile;
	Player playerOne;
	Space *currentSpace, *practice, *challenge, *dungeons, *head;
	eventType currentEvent;
	Map* currentMap;
	std::string mapList[5] = { "level_1.txt", "level_2.txt", "level_3.txt", "level_4.txt", "level_5.txt" };
	int key, difficulty;
	bool playing;
	void gameloop();
	void poll(Map*);
	void createSpace();
	void createList(int);
	void deleteMem();
	void processEvent();
	void startScreen();
	void setDifficulty();
	void gameOver();
	Space* chooseDungeonLevel(int);
	Space* chooseStart();
};

#endif
