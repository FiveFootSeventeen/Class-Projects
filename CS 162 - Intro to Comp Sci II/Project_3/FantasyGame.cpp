/*********************************************************************
** Class Name: FantasyGame
** Author: Jacob Leno
** Date: 11/02/17
** Description: Implementation file for the FantasyGame class. Contains
** the function definitions for FantasyGame. Call gameplay() on a 
** FantasyGame object from main to start the game.
*********************************************************************/

#include "FantasyGame.hpp"
#include <typeinfo>
#include <climits>

/*********************************************************************
**  gameplay function: This function is called on a FantasyGame object
** from main() to start the game.
*********************************************************************/
void FantasyGame::gameplay()
{
	
	int alive, playGame, playerUp;

	do
	{
		cout << "Welcome to Fantasy Combat!" << endl << endl;
		menu();	

		playerUp = intMenu("Who would like to go first? (Player 1 or 2)", false, 2, 1);
		playerUp -= 1;	//Set playerUp to 1 less than the input so players can be switched by subtracting
		do				//current player from 1
		{
			strengthBefore = getPtr(1 - playerUp)->getStrengthPoint();
			alive = fight(playerUp);				//Get the current strength of defending player and call fight()
			displayRound(alive, playerUp);			//Output round information
			playerUp = 1 - playerUp;				//Swap the player's turn
		} while (alive > 0);						//If alive is less than zero the defending character is dead
		delete playerOne;
		delete playerTwo;
		playGame = intMenu("What would you like to do?\n1.Play Again\n2.End Game", false, 2);
	} while (playGame == 1);
}

/*********************************************************************
**  fight function: This function is sent the current attacking player
** as an int (0 or 1 - 0 = player 1, 1 = player 2) and returns the outcome
** of the fight as in integer value of the defender's remaining strength
** points.
*********************************************************************/

int FantasyGame::fight(int attacker)
{
	damage = getPtr(attacker)->attack();
	getPtr(1 - attacker)->defense(damage);
	return getPtr(1 - attacker)->getStrengthPoint();
}

/*********************************************************************
**  menu function: When this function is called it will ask the player 
** choose from one of five characters and will call characterChoice() to
** assign the characters to the appropriate pointers.
*********************************************************************/

void FantasyGame::menu()
{
	int player1, player2;

	cout << "Please select a character." << endl;
	cout << "1. Barbarian		\"Big sword, big muscles\"" << endl;
	cout << "2. Vampire		\"Nasty big pointy teeth\"" << endl;
	cout << "3. Blue Men		\"Fast and small\"" << endl;
	cout << "4. Medusa		\"Her looks can kill\"" << endl;
	cout << "5. Harry Potter		\"Yer a wizard Harry\"" << endl << endl;;
	player1 = intMenu("Please choose a character for player one", false, 5);
	player2 = intMenu("Please choose a character for player two", false, 5);
	characterChoice(playerOne, player1);
	characterChoice(playerTwo, player2);
}

/*********************************************************************
**  characterChoice function: When called it is sent a Character pointer
** which it accepts as a pointer reference and an integer representing
** the players choice. It assigns the correct character choice to the
** corresponding pointer as a DA object of that type.
*********************************************************************/

void FantasyGame::characterChoice(Character *&playerChoicePtr, int choiceNum)
{
	switch (choiceNum)
	{
	case 1: playerChoicePtr = new Barbarian();
		break;
	case 2: playerChoicePtr = new Vampire();
		break;
	case 3: playerChoicePtr = new BlueMen();
		break;
	case 4: playerChoicePtr = new Medusa();
		break;
	case 5: playerChoicePtr = new HarryPotter();
		break;
	}
}

/**************************************************************************************
**  displayRound function: Its first parameter is an integer value representing
** the defending character's strength value which it uses to determine
** if that character is still alive. The second parameter is an integer
** which represents which player is currently attacking.
** (note (playerUp) denotes the attacking player and (1 - playerUp) the defending player)
****************************************************************************************/

void FantasyGame::displayRound(int stillAlive, int playerUp)
{
	cout << endl << getPlayer(playerUp) << " attacks with " << getType(playerUp) << endl;
	if ((typeid(*getPtr(playerUp)) == typeid(Medusa)) && (static_cast<Medusa*>(getPtr(playerUp))->getGlare() == true))			//If attacking player is Medusa
	{																															//check to see if glare was used
		cout << getPlayer(playerUp) << " uses glare! " << getType(1 - playerUp) << " is turned to stone!" << endl;				//if it was output a message to the screen
	}
	else
	{
		cout << getPlayer(playerUp) << " attacks with " << getPtr(playerUp)->getAttack() << " points of damage!" << endl;
	}

	if ((typeid(*getPtr(1 - playerUp)) == typeid(Vampire)) && (static_cast<Vampire*>(getPtr(1 - playerUp))->getCharm() == true)) //If the defending player is
	{																															 //a vampire and charm is activated
			cout << "Vampire uses charm! The attack causes no harm!" << endl;													 //output it to the screen
	}

	cout << getPlayer(1 - playerUp) << " defends with " << getPtr(1 - playerUp)->getDefense() << " points of defense." << endl;
	cout << getPlayer(1 - playerUp) << "'s " << getType(1 - playerUp) << \
		" has a " << getPtr(1 - playerUp)->getArmor() << " armor defense rating" << endl;
	cout << getPlayer(1 - playerUp) << "'s " << getType(1 - playerUp) << \
		" had " << strengthBefore << " strength points before the attack" << endl;
	cout << getPlayer(playerUp) << "'s " << getType(playerUp) << " did " << \
		getPtr(1 - playerUp)->getTotalDamage() << " total points of damage to " << getType(1 - playerUp) << endl;

	if ((typeid(*getPtr(1 - playerUp)) == typeid(BlueMen)) && (static_cast<BlueMen*>(getPtr(1 - playerUp))->getManDown() == true))	//If defending player is BlueMen 
	{																																//and they recently lost a man
																																	//output how many to the screen
		cout << getPlayer(1 - playerUp) << "'s Blue Men have lost " \
			<< static_cast<BlueMen*>(getPtr(1 - playerUp))->getLostMen() << " of their members!" << endl;
	}
	if ((typeid(*getPtr(1 - playerUp)) == typeid(HarryPotter)) && (static_cast<HarryPotter*>(getPtr(1 - playerUp))->getAbility() == true))
	{																										//If defending player is HarryPotter
		cout << getType(1 - playerUp) << " used Hogwarts! He's back from the dead!" << endl;				//and he used Hogwarts this round
	}																										//output a message saying so

	if(stillAlive <= 0) 
	{
		cout << getPlayer(1 - playerUp) << "'s " << getType(1 - playerUp) << " now has 0 (" << getPtr(1 - playerUp)->getStrengthPoint() \
			<< ") points of strength remaining." << endl << endl;
		if (playerUp == P1) { cout << "Player 1 has won the game!" << endl << endl; }
		else { cout << "Player 2 has won the game!" << endl << endl; }
	}
	else
	{
	cout << getPlayer(1 - playerUp) << "'s " << getType(1 - playerUp) << " now has " << getPtr(1 - playerUp)->getStrengthPoint() \
		<< " points of strength remaining." << endl << endl;
		cout << "Press enter to roll dice..." << endl; 
		std::cin.ignore(INT_MAX, '\n');
	}

}

/*********************************************************************
**  getPlayer function: Sent the integer or enum value of the corresponding
** player and returns a string of that player.
*********************************************************************/

std::string FantasyGame::getPlayer(int player)
{
	if (player == P1) { return "Player 1"; }
	else { return "Player 2"; }
}

/*********************************************************************
**  getPtr function: Sent the integer or enum value of the corresponding
** player and returns a pointer to that player's derived character object.
*********************************************************************/

Character* FantasyGame::getPtr(int playerNum)
{
	if (playerNum == P1) { return playerOne; }
	else { return playerTwo; }
}

/*********************************************************************
**  getType function: Sent the integer or enum value of the corresponding
** player and returns a string of that player's character type.
*********************************************************************/

std::string FantasyGame::getType(int playerNum)
{
	std::string type;
	if (typeid(*getPtr(playerNum)) == typeid(Barbarian)) { return "Barbarian"; }
	if (typeid(*getPtr(playerNum)) == typeid(Vampire)) { return "Vampire"; }
	if (typeid(*getPtr(playerNum)) == typeid(BlueMen)) { return "Blue Men"; }
	if (typeid(*getPtr(playerNum)) == typeid(Medusa)) { return "Medusa"; }
	if (typeid(*getPtr(playerNum)) == typeid(HarryPotter)) { return "Harry Potter"; }
}
