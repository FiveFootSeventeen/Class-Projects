/*********************************************************************
** Class Name: Gameplay
** Author: Jacob Leno
** Date: 12/04/17
** Description: This is the function implementation file for the Gameplay
** class.
*********************************************************************/

#include "Gameplay.hpp"

//Loads the game menu and asks the player to make a selection.
void Gameplay::gameMenu()
{
	startScreen();	//Display the instructions
	int choice;
	do
	{
		createSpace();	//Create DA memory for each space object and load the maps.
		playing = true;
		cout << "Please make a selection" << endl << endl;
		choice = intMenu("1. Practice\n2. Challenge\n3. Dungeon\n4. Instructions\n5. Quit", false, 5);
		switch (choice)
		{
		case 1:
			currentSpace = practice;
			currentSpace->getSpaceMap()->initializePlayer(&playerOne);	//Initialize current map with a reference to the player object
			playerOne.playerStartLoc(25, 15);
			difficulty = 0;
			gameloop();
			break;
		case 2:
			currentSpace = challenge;
			currentSpace->getSpaceMap()->initializePlayer(&playerOne);
			currentSpace->getSpaceMap()->setStartDoor();		//Set the player's starting location to the unlocked door
			difficulty = 3;
			gameloop();
			break;
		case 3:
			difficulty = intMenu("1. Easy\n2. Medium\n3. Hard", false, 3, 1, true, "Choose a difficulty:");
			currentSpace = chooseStart();
			currentSpace->getSpaceMap()->initializePlayer(&playerOne);
			currentSpace->getSpaceMap()->setStartDoor();
			gameloop();
			break;
		case 4:
			startScreen();		//Display the instructions
			break;
		}
		deleteMem();		//Delete DA memory
	} while (choice != 5);

}

//Called once currentSpace has been set with the player's choice. Runs a loop that continues until
//the player chooses to exit by pressing 'q' or they run out of time.
void Gameplay::gameloop()
{
	int time = 0;
	currentMap = currentSpace->getSpaceMap();	//Set the current map to the one held by currentSpace
	setDifficulty();				//Set the difficulty level based on value of member variable 'difficulty'
	while (playing)					//Loop until playing is false
	{
		CLEAR();
		time++;
		currentMap->update();						//Update the current map based on changed player location, portals, gun energy or tiles
		currentEvent = currentMap->getEvent();		//Set the current event
		if (currentEvent != NOEVENT) { processEvent(); }		//Check to see if there are any events, if there are deal with them
		if (time % 5 == 0) { currentMap->decrementTime(); }		//Decrement time once every second
		currentMap->printMap();		//Print out the updated map
		poll(currentMap);			//Get input from play using curses
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Wait for 1/5th second
	}
	CLEAR();
	gameOver();		//Display a game end message based on the current event
}

//This function takes a pointer to the current map and gets input from the user
//The player's position on the map is modified based on user input. Portal gun fire
//is also detected as well as the player's choice to quit.
void Gameplay::poll(Map *currentMap)	//Most of this code for curses was adapted from info on pg. 7 and 29 of this guide on ncurses
{										//http://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/pdf/NCURSES-Programming-HOWTO.pdf#page=34&zoom=100,-133,767
	initscr();						//Start curses mode
	nodelay(stdscr, TRUE);			//Dont wait for input
	raw();                          // Line buffering disabled     
	noecho();						//Dont echo input to the console
	cbreak();						//No buffering, key is immediatly returned to getch
	int c = getch();				//Get a key from the user
	
	switch (c)
	{
	case 'a':
		if (playerOne.getCurrentDirection() == WEST && currentMap->playerGetNext(WEST))
		{
			playerOne.advanceDirection(WEST);
			currentMap->teleportOK();					//Now that the player has moved out of the portal
		}											//Its okay for them to enter and teleport again
		else { playerOne.changeDirection(WEST); }
		break;
	case 'd':
		if (playerOne.getCurrentDirection() == EAST && currentMap->playerGetNext(EAST))
		{ 
			playerOne.advanceDirection(EAST);
			currentMap->teleportOK();
		}
		else { playerOne.changeDirection(EAST); }
		break;
	case 'w':
		if (playerOne.getCurrentDirection() == NORTH && currentMap->playerGetNext(NORTH))
		{ 
			playerOne.advanceDirection(NORTH);
			currentMap->teleportOK();
		}
		else { playerOne.changeDirection(NORTH); }
		break;
	case 's':
		if (playerOne.getCurrentDirection() == SOUTH && currentMap->playerGetNext(SOUTH))
		{ 
			playerOne.advanceDirection(SOUTH); 
			currentMap->teleportOK();
		}
		else { playerOne.changeDirection(SOUTH); }
		break;
	case 'f' :
		currentMap->gunFired(playerOne.getCurrentDirection());
		break;
	case 'q':
		playing = false;
		break;
	}
	endwin();		//End curses mode
}

//Called in the game loop. Checks the status of the currentEvent member variable
//and modifies the current map or the state of the playing member variable based
//on its value.
void Gameplay::processEvent()
{
	if (currentEvent == PREVMAP && currentSpace->getLeft())
	{
		currentMap->setEvent(NOEVENT);				//Set the event back to NOEVENT
		currentSpace = currentSpace->getLeft();		//Get the previous Space
		currentMap = currentSpace->getSpaceMap();	//Get the new Space's map
		currentMap->initializePlayer(&playerOne);	//Initialize the map to the Player object and set
		currentMap->setStartLockedDoor();			//the start location to the locked door
		setDifficulty();							//Set the player specified time difficulty
	}
	if (currentEvent == NEXTMAP && currentSpace->getRight())
	{
		currentMap->setEvent(NOEVENT);
		currentSpace = currentSpace->getRight();	//Get the next map
		currentMap = currentSpace->getSpaceMap();
		currentMap->initializePlayer(&playerOne);
		currentMap->setStartDoor();					//Set the player's start location to the unlocked door
		setDifficulty();
	}
	if (currentEvent == NOTIME || currentEvent == WINGAME)
	{
		playing = false;
	}

}

//Called in gameMenu to find out if the player wants to start at a certial level
//if they do return the corrosponding space
Space* Gameplay::chooseStart()
{
	int choice;
	choice = intMenu("Would you like to choose a start location?\n1. Yes\n2. No", true);
	if (choice == 2) { return head; }
	choice = intMenu("What level would you like to start at? (1-5)", false, 5);
	return chooseDungeonLevel(choice);
}

//Return the Space corrosponding with the level number sent as an argument
Space* Gameplay::chooseDungeonLevel(int levelNum)
{
	Space *temp = head;
	while (static_cast<Dungeon*>(temp)->getLevel() != levelNum)
	{
		temp = temp->getRight();
	}
	return temp;
}

//Called when the game has ended, display's a message based on the outcome.
void Gameplay::gameOver()
{
	if (currentEvent == NOTIME)
	{
		cout << "You have run out of time, you'll have to start over" << endl;
	}
	if (currentEvent == WINGAME)
	{
		cout << "You have won the game, the cake is yours!" << endl;
	}
}

//Create new DA Space memory and call appropriate functions to load the maps
void Gameplay::createSpace()
{
	practice = new Practice("practice.txt");
	challenge = new Challenge("challenge.txt");
	for (int i = 0; i < 5; i++)
	{
		createList(i);
	}
}

//Create a linked list of Dungeon objects
void Gameplay::createList(int mapNum)
{
	if (dungeons == nullptr)
	{
		dungeons = new Dungeon(mapList[mapNum], (mapNum +1));
		head = dungeons;
	}
	else
	{
		Space *temp = dungeons;
		dungeons = new Dungeon(mapList[mapNum], (mapNum + 1), dungeons);
		temp->setRight(dungeons);
		temp = nullptr;
	}
}

//Delete all DA memory
void Gameplay::deleteMem()
{
	if (practice) 
	{ 
		delete practice; 
		practice = nullptr;
	}
	if (challenge) 
	{ 
		delete challenge; 
		challenge = nullptr;
	}
	if (dungeons)
	{
		dungeons = head;
		while (dungeons)
		{
			Space *garbage = dungeons;
			dungeons = dungeons->getRight();
			delete garbage;
		}
		dungeons = nullptr;
	}
}

//Gameplay destructor
Gameplay::~Gameplay()
{
	deleteMem();
}

//Called to display the game instructions, it loads these instructions
//from a file
void Gameplay::startScreen()
{
	inFile.open("instructions.txt", std::ios::in);
	std::string input;
	CLEAR();
	while (inFile.peek() != EOF)
	{
		input = inFile.get();
		if (input == "%")
		{
			cout << "Press enter to continue..." << endl;
			std::cin.ignore(INT_MAX, '\n');
			CLEAR();
		}
		else
		{
			cout << input;
		}
	}
	inFile.clear();
	inFile.close();
}

//Sets the time allowed for the game level based on the player's
//difficulty choice.
void Gameplay::setDifficulty()
{
	if (difficulty == 0)
	{
		currentMap->setTime(60, 0);
	}
	if (difficulty == 1)
	{
		currentMap->setTime(10, 0);
	}
	if (difficulty == 2)
	{
		currentMap->setTime(3, 0);
	}
	if (difficulty == 3)
	{
		currentMap->setTime(2, 0);
	}
}