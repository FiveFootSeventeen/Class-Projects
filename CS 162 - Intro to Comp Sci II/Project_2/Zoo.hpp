/*********************************************************************
** Class Name: Zoo
** Author: Jacob Leno
** Date: 10/17/17
** Description: This is the header file for the Zoo class of the 
** Zoo Tycoon game. 
*********************************************************************/

#include "Animal.hpp"

#include <ctime>
#include <cstdlib>
#include <string>


#ifndef ZOO_HPP
#define ZOO_HPP

class Zoo
{
public:
	void beginGame();
	Zoo();
	~Zoo();

private:
	//Variables
	enum animalTypes { TIGER, PENGUIN, TURTLE };
	const int BASEFOOD = 100;
	unsigned seed = int(time(0));

	int zooAccount, dayCount, rndAnimal, bonusReward;
	int eventNum;
	std::string userName;
	int totalAnimals[3];

	Animal * ptrTiger;
	Animal * ptrPenguin;
	Animal * ptrTurtle;
	Animal * ptrTemp;

	//Functions
	void resizeAnimalCap(int);
	bool addAnimal(int, int, bool purchase = false, bool adult = false);
	int getTotalAnimals(int);
	bool randomEvent(int);
	bool rndSickness();
	void rndAttendBoom();
	bool rndNewBirth();
	void addBank(int);
	void subBank(int);
	void increaseAge(bool, int animalType = 0);
	int getBalance();
	int feedingCost();
	void newDay();
	int eventMakr();
	std::string getAnimalType(int);
	int payoff(int);

};


#endif