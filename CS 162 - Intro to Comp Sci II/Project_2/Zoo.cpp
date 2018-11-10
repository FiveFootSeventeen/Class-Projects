/*********************************************************************
** Class Name: Zoo
** Author: Jacob Leno
** Date: 10/17/17
** Description:This is the implementation file for the Zoo class of the 
** Zoo Tycoon game. This class contains the main functions for running 
** the game and using Animal type objects. The game is started by calling
** beginGame from main and for each day the newDay funcion loops until
** the user decides to quit.
*********************************************************************/

#include "Zoo.hpp"
#include "Tiger.hpp"
#include "Penguin.hpp"
#include "Turtle.hpp"
#include "intMenu.hpp"

#include <iostream>
#include <string>
#include <climits>

using std::cout;
using std::cin;
using std::endl;

Zoo::Zoo()//Default constructor
{
	ptrTiger = new Tiger[10];
	ptrPenguin = new Penguin[10];
	ptrTurtle = new Turtle[10];
	dayCount = 1;
	zooAccount = 100000;
	for (int i = 0; i < 3; i++)
	{
		totalAnimals[i] = 0;
	}

}

Zoo::~Zoo()//Destructor
{
	delete[] ptrTiger;
	delete[] ptrPenguin;
	delete[] ptrTurtle;
}

/*********************************************************************
** newDay Function: This function acts as a new day in the game every 
**time it is called. It outputs messages about the current status of the
**zoo, deducts feeding costs from the bank and loops until the player 
**chooses to stop
*********************************************************************/

void Zoo::newDay()
{
	int dailyEvent;
	int keepPlaying = 1;
	bool bankBalance;


	do {
		bonusReward = 0;

		cout << endl << "Today is day " << dayCount << endl;
		cout << userName << " you currently have " << totalAnimals[TIGER] << " tigers, " << totalAnimals[PENGUIN]
			<< " penguins, and " << totalAnimals[TURTLE] << " turtles." << endl;
		cout << "To start you must feed your animals." << endl;
		cout << "It will cost $" << feedingCost() << "." << endl;
		cout << "Press enter to feed animals . . .";
		cin.ignore(INT_MAX, '\n'); //Ignore any code the user inputs
		cin.clear();


		subBank(feedingCost());

		cout << "Current bank account balance: " << getBalance() << endl;
		dayCount += 1;

		dailyEvent = eventMakr(); //Get an event from eventMakr

		if (dailyEvent == 1)
		{
			if (randomEvent(dailyEvent) == true)	//If randomEvent returns true then display which animal died
			{
				cout << "Sickness has caused 1 " << getAnimalType(rndAnimal) << " to die! How sad..." << endl;
			}
			else
			{
				dailyEvent = 4;		//If randomEvent returns false then there are no animals to get sick, nothing happens.
			}
		}
		if (dailyEvent == 2)	//Display the reward and the animal that gets the bonus
		{
			randomEvent(dailyEvent);
			cout << "There has been a boom in attendance! This day " << getAnimalType(rndAnimal) << "s are now worth $"
				<< bonusReward << "!" << endl;
		}
		if (dailyEvent == 3)	
		{
			if (randomEvent(dailyEvent) == true) //If randomEvent returns true then there is a member of the chosen animal class
			{									 //that is old enough to have a baby. Display the chosen animal the the amount of babies.
				if (rndAnimal == TIGER)
				{
					cout << "A " << getAnimalType(rndAnimal) << " has given birth to " << ptrTiger->numberOfBabies << " baby." << endl;
				}
				if (rndAnimal == PENGUIN)
				{
					cout << "A " << getAnimalType(rndAnimal) << " has given birth to " << ptrPenguin->numberOfBabies << " babies." << endl;
				}
				if (rndAnimal == TURTLE)
				{
					cout << "A " << getAnimalType(rndAnimal) << " has given birth to " << ptrTurtle->numberOfBabies << " babies." << endl;
				}
			}
			else
			{
				dailyEvent = 4;
			}
		}
		if (dailyEvent == 4) //Nothing happens
		{
			cout << "Not much happened today!" << endl;		
		}

		cout << userName << " your zoo made $" << payoff(dailyEvent) << " today!" << endl; //Display the total profits for the day

		if (intMenu("Would you like to buy an adult animal?", true) == 1)
		{
			bankBalance = addAnimal((intMenu("What type would you like to buy?\n1. Tiger ($10,000)" \
				"\n2. Penguin ($1,000)\n3. Turtle ($100)", false, 3) - 1), 1, true, true);

			if (bankBalance == false) 
			{ 
				cout << "You cant do that you'll be broke!" << endl; 
			}
		}

		increaseAge(true);	//Increase the age off all the animals

		if (zooAccount < 0) //If the user runs out of money the game ends.
		{
			cout << "Sorry it appears you have run out of money! Game Over..." << endl;
			keepPlaying = 0;
		}
		else
		{
			keepPlaying = intMenu("Would you like to keep playing?", true);
		}
	} while (keepPlaying == 1);
}

/*********************************************************************
** beginGame Function: Called from main and used to begin the game.
** collects initial starting information and greets the user.
*********************************************************************/

void Zoo::beginGame()
{
	int animals;

	srand(seed);

	cout << "Welcome to Zoo Tycoon!" << endl << "You are the proud owner of a new zoo!" << endl <<
		"What is your name zoo owner ? " << endl;
	getline(cin, userName);

	cout << "To start out you have $100,000 in your account at the local bank." << endl <<
		"You will need to purchase a few animals to start up your zoo" << endl << endl;

	animals = intMenu("Tigers are $10,000. How many tigers would you like to add? (1 or 2)", false, 2);
	addAnimal(TIGER, animals, true);	
	animals = intMenu("Penguins are $1,000. How many penguins would you like to add? (1 or 2)", false, 2);
	addAnimal(PENGUIN, animals, true);
	animals = intMenu("Turtles are $100. How many turtles would you like to add? (1 or 2)", false, 2);
	addAnimal(TURTLE, animals, true);	 

	cout << endl;																										 

	newDay();
}

/*********************************************************************
** payoff Function: Takes an int as an argument which is the number
** of the daily event that took place. The funcion calculates the total
** profits for the day and if an attendance boom occured it will add
** the bonus to the total. The function returns total profits as int
*********************************************************************/

int Zoo::payoff(int dailyEvent)
{
	int deposit = 0;
	if (dailyEvent == 2)
	{
		deposit += bonusReward * totalAnimals[rndAnimal];
	}
	deposit += int(totalAnimals[TIGER] * ptrTiger->payoff * ptrTiger->cost);
	deposit += int(totalAnimals[PENGUIN] * ptrPenguin->payoff * ptrPenguin->cost);
	deposit += int(totalAnimals[TURTLE] * ptrTurtle->payoff * ptrTurtle->cost);

	addBank(deposit);

	return deposit;
}

/*********************************************************************
** getTotalAnimals Function: Takes a int as an argument which is the type
** of animal requested and returns the total of that kind of animal in the zoo
*********************************************************************/

int Zoo::getTotalAnimals(int animalType)
{
	if (animalType == TIGER)
	{
		return totalAnimals[TIGER];
	}
	else if (animalType == PENGUIN)
	{
		return totalAnimals[PENGUIN];
	}
	else
	{
		return totalAnimals[TURTLE];
	}

}

/*********************************************************************
** increaseAge Function: If a value of true is sent as the first argument
** increaseAge() will increase the age of all the animals in the zoo
** if a value of true is sent as the second argument increaseAge will
** increase the age of the most recently added animal by two days. This
** option is used in addAnimal when an adult animal is purchased by the user
*********************************************************************/

void Zoo::increaseAge(bool allAnimals, int animalType)
{
	if (allAnimals == true) //Increase the age of all animals in the zoo by one day
	{
		int i = 0;
		while (i != totalAnimals[TIGER])
		{
			ptrTiger[i].age += 1;
			i++;
		}
		i = 0;
		while (i != totalAnimals[PENGUIN])
		{
			ptrPenguin[i].age += 1;
			i++;
		}
		i = 0;
		while (i != totalAnimals[TURTLE])
		{
			ptrTurtle[i].age += 1;
			i++;
		}
	}
	else
	{
		if (animalType == TIGER) { ptrTiger[totalAnimals[TIGER]].age += 2; } //Increase the age of the most recently added animal by two days
		if (animalType == PENGUIN) { ptrPenguin[totalAnimals[PENGUIN]].age += 2; }
		if (animalType == TURTLE) { ptrTurtle[totalAnimals[TURTLE]].age += 2; }
	}

}

/*********************************************************************
** addAnimal Function: Takes 4 arguments. First an int is the type of animal
** too add, second an int is the number of new animals to add, third is
** a bool value indicating if it was a purchase (default is false), fourth
** is a bool value indicating if the animals should be adults. This function
** thats the appropriate amount of animals to the object type and returns
** false if the user tries to add animals with a purchase but does not
** have the funds.
*********************************************************************/

bool Zoo::addAnimal(int animalType, int newAnimals, bool purchase, bool adult) 
{
	if (animalType == TIGER)
	{	
		for (int i = 0; i < newAnimals; i++)
		{
			if ((totalAnimals[TIGER] % 10) == 9)
			{
				resizeAnimalCap(TIGER);
			}
			if (purchase == true)
			{
				if ((zooAccount - ptrTiger->cost) > 1)
				{
					totalAnimals[TIGER] += 1;
					if (adult == true) { increaseAge(false, TIGER); }
					subBank(ptrTiger->cost);
				}
				else
				{
					return false;
				}
			}
			else				//If purchase is false then it is a birth, add respective number of babies, set age equal to 1 day
			{ 
				totalAnimals[TIGER] += 1;
				ptrTiger[totalAnimals[TIGER]].age = 1;
			}
		}
	}

	if (animalType == PENGUIN)
	{
		for (int i = 0; i < newAnimals; i++)
		{
			if ((totalAnimals[PENGUIN] % 10) == 9)
			{
				resizeAnimalCap(PENGUIN);

			}
			if (purchase == true)
			{
				if ((zooAccount - ptrPenguin->cost) > 1)
				{
					totalAnimals[PENGUIN] += 1;
					if (adult == true) { increaseAge(false, PENGUIN); }
					subBank(ptrPenguin->cost);
				}
				else
				{
					return false;
				}
			}
			else				//If purchase is false then it is a birth, add respective number of babies, set age equal to 1 day
			{ 
				totalAnimals[PENGUIN] += 1;
				ptrPenguin[totalAnimals[PENGUIN]].age = 1;
			} 
		}
	}

	if (animalType == TURTLE)
	{
		for (int i = 0; i < newAnimals; i++)
		{
			if ((totalAnimals[TURTLE] % 10) == 9)
			{
				resizeAnimalCap(TURTLE);

			}
			if (purchase == true)
			{
				if ((zooAccount - ptrTurtle->cost) > 1)
				{
					totalAnimals[TURTLE] += 1;
					if (adult == true) { increaseAge(false, TURTLE); }
					subBank(ptrTurtle->cost);
				}
				else
				{
					return false;
				}
			}
			else 
			{				//If purchase is false then it is a birth, add respective number of babies, set age equal to 1
				totalAnimals[TURTLE] += 1;
				ptrTurtle[totalAnimals[TURTLE]].age = 1;
			} 
		}
	}
	return true;
}

/*********************************************************************
** resizeAnimalCap Function: For each animal object. Assign the original
** memory pointed too with the ptr(Animal) pointer to a temporary pointer
** then create a new array of objects 10 objects longer than the previous
** one. Copy the values in the temporary pointer into the new array and 
** delete the DA memory in the temporary pointer.
*********************************************************************/

void Zoo::resizeAnimalCap(int animalType)  
{										  
	if (animalType == TIGER)
	{
		ptrTemp = ptrTiger;

		ptrTiger = new Tiger[((int(totalAnimals[TIGER] / 10) + 1) * 10) + 10]; //Reassign ptrTiger to new mem 10 objects longer than it previously was

		for (int i = 0; i < (((int(totalAnimals[TIGER] / 10) + 1) * 10)); i++) //Loop through previous values in ptrTemp and copy them
		{																	   //to new memory
			ptrTiger[i] = ptrTemp[i];
		}
		delete[] ptrTemp;
	}

	if (animalType == PENGUIN)
	{
		ptrTemp = ptrPenguin;

		ptrPenguin = new Penguin[((int(totalAnimals[PENGUIN] / 10) + 1) * 10) + 10]; //Reassign ptrPenguin to new mem 10 objects longer than it previously was

		for (int i = 0; i < (((int(totalAnimals[PENGUIN] / 10) + 1) * 10)); i++) // Loop through previous values in ptrTemp and copy them
		{																		 // to new memory
			ptrPenguin[i] = ptrTemp[i];
		}
		delete[] ptrTemp;
	}

	if (animalType == TURTLE)
	{
		ptrTemp = ptrTurtle;

		ptrTurtle = new Turtle[((int(totalAnimals[TURTLE] / 10) + 1) * 10) + 10]; //Reassign ptrPenguin to new mem 10 objects longer than it previously was

		for (int i = 0; i < (((int(totalAnimals[TURTLE] / 10) + 1) * 10)); i++) // Loop through previous values in ptrTemp and copy them
		{																		// to new memory
			ptrTurtle[i] = ptrTemp[i];
		}
		delete[] ptrTemp;
	}
}

/*********************************************************************
** eventMakr Function: Generate a random event (1-4) and return it as
** an int.
*********************************************************************/

int Zoo::eventMakr()
{

	eventNum = (rand() % 4 + 1);
	return eventNum;
}

/*********************************************************************
** randomEvent Function: Takes an int as an argument and the random event
** is chosen based on that argument. If any of the functions randomEvent()
** call return false, randomEvent() will also return false to indicate
** no event took place.
*********************************************************************/

bool Zoo::randomEvent(int eventNum)
{
	if (eventNum == 1)
	{
		if (rndSickness() == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (eventNum == 2)
	{
		rndAttendBoom();
	}
	if (eventNum == 3)
	{
		if (rndNewBirth() == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*********************************************************************
** rndSickness Function: Generate random animal for the turn in the 
** member variable rndAnimal. If there are animals at the zoo of that
** type one will die and the function will return true, if not
** no animals will be subtracted and the function will return false.
*********************************************************************/

bool Zoo::rndSickness()
{
	rndAnimal = rand() % 3;

	if (rndAnimal == TIGER && totalAnimals[TIGER] > 0)
	{
		totalAnimals[TIGER] -= 1;
		return true;
	}
	if (rndAnimal == PENGUIN && totalAnimals[PENGUIN] > 0)
	{
		totalAnimals[PENGUIN] -= 1;
		return true;
	}
	if (rndAnimal == TURTLE && totalAnimals[TURTLE] > 0)
	{
		totalAnimals[TURTLE] -= 1;
		return true;
	}
	return false;

}

/*********************************************************************
** rndAttendBoom Function: Generate random animal for the turn in the 
** member variable rndAnimal and set member variable bonusReward equal
** to the random bonus ($10-$500 in $10 increments)
*********************************************************************/

void Zoo::rndAttendBoom()
{
	rndAnimal = rand() % 3;
	bonusReward = (rand() % 50 + 1) * 10;
}

/*********************************************************************
** rndNewBirth Function: Generates the random animal for the turn in
** member variable rndAnimal. If the corresponding animal in rndAnimal
** has an animal object with age >= 3 babies will be born to that animal
** type and addAnimal called with the appropriate values sent. If the
** animal does not have an object with age >= 3 then a value of false
** will be returned indicating no animals were born.
*********************************************************************/

bool Zoo::rndNewBirth()
{
	rndAnimal = rand() % 3;
	bool newBirth = false;
	int i = 0;	

	if (rndAnimal == TIGER)
	{
		while (i < totalAnimals[newBirth] && newBirth == false)	//Check through all the animals of type TIGER 
		{														//to see if one is old enough
			if (ptrTiger[i].age >= 3)
			{
				newBirth = true;								//If an animal old enough is found add that amount of babies
				addAnimal(rndAnimal, ptrTiger->numberOfBabies);
			}
			i++;
		}
	}

	if (rndAnimal == PENGUIN)
	{
		while (i < totalAnimals[newBirth] && newBirth == false) //Check through all the animals of type PENGUIN 
		{														//to see if one is old enough
			if (ptrPenguin[i].age >= 3)
			{
				newBirth = true;
				addAnimal(rndAnimal, ptrPenguin->numberOfBabies); //If an animal old enough is found add that amount of babies
			}
			i++;
		}
	}

	if (rndAnimal == TURTLE)
	{
		while (i < totalAnimals[newBirth] && newBirth == false) //Check through all the animals of type TURTLE 
		{														//to see if one is old enough
			if (ptrTurtle[i].age >= 3)
			{
				newBirth = true;
				addAnimal(rndAnimal, ptrTurtle->numberOfBabies); //If an animal old enough is found add that amount of babies
			}
			i++;
		}
	}
	return newBirth; //Return value indicates if an animal had babies
}

/*********************************************************************
** getAnimalType Function: Takes an int as an argument and returns the
** corresponding animal type as a string.
*********************************************************************/

std::string Zoo::getAnimalType(int type)
{
	if (type == TIGER) { return "tiger"; };
	if (type == PENGUIN) { return "penguin"; };
	if (type == TURTLE) { return "turtle"; };
	return 0;
}

/*********************************************************************
** feedingCost Function: Calculates the cost to feed all animals and
** returns the value as an integer.
*********************************************************************/

int Zoo::feedingCost()
{
	int totalCost;

	totalCost = int(ptrTiger->baseFoodCost * BASEFOOD * totalAnimals[TIGER]);
	totalCost += int(ptrPenguin->baseFoodCost * BASEFOOD * totalAnimals[PENGUIN]);
	totalCost += int(ptrTurtle->baseFoodCost * BASEFOOD * totalAnimals[TURTLE]);
	return totalCost;
}

/*********************************************************************
** addBank Function: Adds the integer given as an argument to zooAccount
*********************************************************************/

void Zoo::addBank(int deposit)
{
	zooAccount += deposit;

}

/*********************************************************************
** subBank Function: Subtracts the integer sent as an argument from zooAccount
*********************************************************************/

void Zoo::subBank(int withdrawal)
{
	zooAccount -= withdrawal;

}

/*********************************************************************
** getBalance Function: Returns the current zooAccount balance
*********************************************************************/

int Zoo::getBalance()
{
	return zooAccount;
}

