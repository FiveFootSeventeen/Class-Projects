/*********************************************************************
** Class Name: CharacterList
** Author: Jacob Leno
** Date: 11/17/17
** Description: This is the header file for the CharacterList class
*********************************************************************/

#ifndef CHARACTERLIST_HPP
#define CHARACTERLIST_HPP

#include "Character.hpp"
#include "LosingChar.hpp"
#include <string>


class CharacterList
{
protected:
	//Variables
	struct characterNode
	{
		Character *playerCharacter;
		characterNode *next;
		characterNode *prev;
		characterNode() : playerCharacter(nullptr), prev(nullptr), next(nullptr) {};
		characterNode(characterNode *prev, characterNode *next = nullptr)
		{
			playerCharacter = nullptr;
			this->next = next;
			this->prev = prev;
		}
	};
	LosingChar *lostPlayerStack;
	characterNode *head;
	characterNode *tail;
	characterNode *scanner;
	int team;

public:
	//Functions
	~CharacterList();
	CharacterList() : head(nullptr), tail(nullptr), team(0) {}
	CharacterList(int teamIn, LosingChar* stack) : head(nullptr), tail(nullptr), team(teamIn), lostPlayerStack(stack) { }
	characterNode* getTail() { return tail; }
	characterNode* getScanner() { return scanner; }
	Character* getCharacterUp();
	int currentWon();
	int replenishHealth(Character*);
	int getTeam() { return team; }
	void setScanner() { scanner = head; }
	void advanceScanner() { if (scanner) { scanner = scanner->next; } }
	void setScannerChar(Character *type) { scanner->playerCharacter = type; }
	void setScannerCharName(std::string name) { scanner->playerCharacter->setName(name); }	
	void currentLost();	
	void clear();
	void populate(int);
};

#endif 
