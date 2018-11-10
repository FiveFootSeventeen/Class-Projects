/*********************************************************************
** Class Name: FantasyTournament
** Author: Jacob Leno
** Date: 11/17/17
** Description: This is the implementation file for the FantasyTournament
** class, it contains the function definitions for the class.
*********************************************************************/

#include "FantasyTournament.hpp"

/*********************************************************************
**  gameplay : This function is called from main and it starts the Fantasy
** Tournament game.
*********************************************************************/

void FantasyTournament::gameplay()
{
	int playGame, playerUp, displayLost;

	do
	{
		round = 0;
		cout << "Welcome to Fantasy Tournament!" << endl << endl;
		menu();

		playerUp = intMenu("Who would like to go first? (Player 1 or 2)", false, 2, 1);
		playerUp -= 1;				//Set playerUp to 1 less than the input so players can be switched by subtracting
		cout << endl << endl;		//current player from 1
		do					
		{
			fight(playerUp);								
			playerUp = 1 - playerUp;						//Swap the player's turn
		} while (teamA.getCharacterUp() != nullptr && teamB.getCharacterUp() != nullptr);	

		finalScore();
		displayLost = intMenu("Would you like to see the characters that have died?\n1. Yes\n2. No", true);
		if (displayLost == 1) { displayDefeated(); }

		clearTeamObj();
		clearScore();

		playGame = intMenu("What would you like to do?\n1.Play Again\n2.End Game", false, 2);
	} while (playGame == 1);
}

/*********************************************************************
**  fight : This function is sent an integer value representing who will
** be attacking first this round. The function cycles through each character
** alternation who is attacking and subtracts strength points when necessary.
*********************************************************************/

void FantasyTournament::fight(int attacker)
{
	++round;
	std::string winner;
	int defendStr, replenStr;			
	int originalAttacker = attacker;	//Set up original attacker and starting defender
	int defender = 1 - attacker;
	
	damage = getPtr(attacker)->attack();			//Start the first attack and defend
	getPtr(defender)->defense(damage);
	defendStr = getPtr(defender)->getStrengthPoint();
	cout << "Round " << round << " Special abilities:" << endl;		//Display the special ability heading for the round
	getSpecial(attacker, defender);
	while (defendStr > 0)							//Loop until a character is defeated
	{
		defender = attacker;						//Switch who is attacking and defending
		attacker = 1 - attacker;	
		damage = getPtr(attacker)->attack();		
		getPtr(defender)->defense(damage);					//Calculate the outcome of subsequent rounds
		defendStr = getPtr(defender)->getStrengthPoint();
		getSpecial(attacker, defender);
	} 
	
	displayRound(originalAttacker, attacker);		//Display the round outcome
	addPoints(attacker);							//Add points for the winner, subtract for the loser
	currentScore();									//Display the current score
	winner = getPtr(attacker)->getName();
	int priorStr = getPtr(attacker)->getStrengthPoint();
	replenStr = getTeamObj(attacker).currentWon();
	roundOutcome(attacker, defender, replenStr, priorStr, winner);		//Display the round outcome
	getTeamObj(defender).currentLost();									//Move the defeated character to the lost player stack
}

/*********************************************************************
**  roundOutcome : Display the outcome of the round
*********************************************************************/

void FantasyTournament::roundOutcome(int attacker, int defender, int replenStr, int priorStr, string winner)
{
	cout << winner << " ended with " << priorStr << " strength points" << endl;
	cout << winner << " was placed in the back of the lineup  " << endl \
		<< "and had " << replenStr << " points of strength restored!" << endl;
	cout << winner << " now has " << getTeamObj(attacker).getTail()->playerCharacter->getStrengthPoint() \
		<< " strength!" << endl << endl;
}

/*********************************************************************
**  menu : Populates the TeamA and TeamB characterList pointers with 
** enough nodes to hold the player's choice of characters for each team.
** Also calls assignPlayers for each team to get the character choices
** for both teams.
*********************************************************************/

void FantasyTournament::menu()
{
	teamA.populate(intMenu("How many characters for Team A? (1-10)", false, 10));
	teamB.populate(intMenu("How many characters for Team B? (1-10)", false, 10));
	assignPlayers(teamA);
	assignPlayers(teamB);
}

/*********************************************************************
**  assignPlayers : gets a choice for each CharacterList node for the 
** team pointer it was sent as an argument.
*********************************************************************/

void FantasyTournament::assignPlayers(CharacterList &team)
{
	cout << endl << getTeam(team.getTeam()) << endl;
	cout << "Please select a characters for your team" << endl;
	cout << "1. Barbarian		\"Big sword, big muscles\"" << endl;
	cout << "2. Vampire		\"Nasty big pointy teeth\"" << endl;
	cout << "3. Blue Men		\"Fast and small\"" << endl;
	cout << "4. Medusa		\"Her looks can kill\"" << endl;
	cout << "5. Harry Potter		\"Yer a wizard Harry\"" << endl << endl;;
	
	int i = 0;
	int currentChoice;
	std::string name;
	team.setScanner();			//Set the scanner to point to the head node
	while (team.getScanner())	//get where the scanner is pointing to
	{
		++i;
		currentChoice = intMenu("Team member " + std::to_string(i) + ":", false, 5);
		characterChoice(team, currentChoice);									//Assign the character choice to the node the scanner is currently pointing to
		cout << "What name would you like to give this character?" << endl;
		getline(std::cin, name);	
		team.getScanner()->playerCharacter->setName(name);		//Set the name of the character stored in the node the scanner is pointing to
		team.advanceScanner();									//advance the scanner to the next node
	}
	team.setScanner();
}

/*********************************************************************
**  characterChoice : Assigns a character derived class to the character
** pointer in the node that the scanner is currently pointing to.
*********************************************************************/

void FantasyTournament::characterChoice(CharacterList &team, int choiceNum)
{
	switch (choiceNum)
	{
	case 1: team.setScannerChar(new Barbarian);
		break;
	case 2: team.setScannerChar(new Vampire);
		break;
	case 3: team.setScannerChar(new BlueMen);
		break;
	case 4: team.setScannerChar(new Medusa);
		break;
	case 5: team.setScannerChar(new HarryPotter);
		break;
	}
}

/*********************************************************************
**  getTeamObj : Returns the team object specified by the integer sent
** as an argument
*********************************************************************/

CharacterList& FantasyTournament::getTeamObj(int team)
{
	if (team == tA) { return teamA; }
	else { return teamB; }
}

/*********************************************************************
**  getTeam : Returns the team name as a string. Specified by the integer sent
** as an argument
*********************************************************************/

std::string FantasyTournament::getTeam(int team)
{
	if (team == tA) { return "Team A"; }
	else { return "Team B"; }
}

/*********************************************************************
**  getPtr : Returns a pointer to the current character pointed to by 
** the head node.
*********************************************************************/

Character* FantasyTournament::getPtr(int team)
{
	if (team == tA) { return teamA.getCharacterUp(); }
	else { return teamB.getCharacterUp(); }
}

/*********************************************************************
**  displayRound : Displays the round outcome. Sent the original attacker
** as the first parameter and the winner of the round as the second parameter
*********************************************************************/

void FantasyTournament::displayRound(int originalAttacker, int winner)
{
	int originalDefender = 1 - originalAttacker;
	cout << endl << "Round " << round << " :" << getTeam(originalAttacker) << " " << getPtr(originalAttacker)->getName() << " vs. " \
		 << getTeam(originalDefender) << " " << getPtr(originalDefender)->getName() << ", " \
		 << getPtr(winner)->getName() << " Won!" << endl;
}

/*********************************************************************
**  addPoints : Adds 2 points to the winner's score and subtracts 1 from 
** the loser's score.
*********************************************************************/

void FantasyTournament::addPoints(int winner)
{
	if (winner == tA) {  teamAPoints += 2, teamBPoints -= 1; }
	else {  teamBPoints += 2, teamAPoints -= 1; }
}

/*********************************************************************
**  currentScore : Displays the current score for both teams.
*********************************************************************/

void FantasyTournament::currentScore()
{
	cout << "Team A: " << teamAPoints << endl;
	cout << "Team B: " << teamBPoints << endl;
}

/*********************************************************************
**  displayDefeated : Displays the characters stored in the lostStack.
** As these characters are displayed the DA memory associated with them
** deleted.
*********************************************************************/

void FantasyTournament::displayDefeated()
{
	cout << endl <<  "Defeated Characters:" << endl;
	while (!lostStack->isEmpty())
	{
		Character *tempPtr;
		lostStack->pop(tempPtr);				//Pop character off the stack
		cout << tempPtr->getName() << endl;
		delete tempPtr;							//Delete DA memory
		tempPtr = nullptr;
	}
	cout << endl;

}

/*********************************************************************
**  FantasyTournament Destructor : Deletes the DA lostStack memory
*********************************************************************/

FantasyTournament::~FantasyTournament()
{
	delete lostStack;
}

/*********************************************************************
**  finalScore : Display the final score of the match
*********************************************************************/

void FantasyTournament::finalScore()
{

		cout << "Team A final score: " << teamAPoints << endl;
		cout << "Team B final score: " << teamBPoints << endl;

	if (teamAPoints == teamBPoints)
	{
		cout << "The match was a tie!" << endl;
	}
	else if (teamAPoints > teamBPoints)
	{
		cout << "Team A won!" << endl;
	}
	else
	{
		cout << "Team B won!" << endl;
	}
	cout << endl;

}

/*********************************************************************
**  getSpecial : Find out if any specials were used by the attacking
** and defending players, if they were output a message saying so.
*********************************************************************/

void FantasyTournament::getSpecial(int attacker, int defender)
{
	if ((typeid(*getPtr(attacker)) == typeid(Medusa)) && (static_cast<Medusa*>(getPtr(attacker))->getGlare() == true))				//If attacking player is Medusa
	{																																//check to see if glare was used
		cout << getPtr(attacker)->getName() << " uses glare! " << getPtr(defender)->getName() << " is turned to stone!" << endl;						//if it was output a message to the screen
	}
	if ((typeid(*getPtr(defender)) == typeid(Vampire)) && (static_cast<Vampire*>(getPtr(defender))->getCharm() == true))			//If the defending player is
	{																																//a vampire and charm is activated
		cout << getPtr(defender)->getName() << " uses charm!" << endl;																//output it to the screen
	}
	if ((typeid(*getPtr(defender)) == typeid(BlueMen)) && (static_cast<BlueMen*>(getPtr(defender))->getManDown() == true))			//If defending player is BlueMen 
	{																																//and they recently lost a man
																																	//output how many to the screen
		cout << getPtr(defender)->getName() << " lost " \
			<< static_cast<BlueMen*>(getPtr(defender))->getLostMen() << " of their members!" << endl;
	}
	if ((typeid(*getPtr(defender)) == typeid(HarryPotter)) && (static_cast<HarryPotter*>(getPtr(defender))->getAbility() == true))
	{																																//If defending player is HarryPotter
		cout << getPtr(defender)->getName() << " used Hogwarts!" << endl;															//and he used Hogwarts this round
	}
}

