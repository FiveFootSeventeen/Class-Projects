/*********************************************************************
** Class Name: CharacterList
** Author: Jacob Leno
** Date: 11/17/17
** Description: This is the function implementation file for the CharacterList
** class. It contains the function definitions for the class.
*********************************************************************/

#include "CharacterList.hpp"

/*********************************************************************
**  CharacterList destructor : Delete any DA memory used by CharacterList
** when it goes out of scope
*********************************************************************/
CharacterList::~CharacterList()
{
	characterNode *garbage;
	while (head)
	{
		garbage = head;
		delete head->playerCharacter;
		head = head->next;
		delete garbage;
	}
}

/*********************************************************************
**  clear : Clear the CharacterList object of any nodes, delete all DA
** memory.
*********************************************************************/

void CharacterList::clear()
{
	characterNode *garbage;
	while (head)
	{
		garbage = head;
		delete head->playerCharacter;
		head = head->next;
		delete garbage;
	}
}


/*********************************************************************
** populate : Populate the CharacterList object with the number of 
** nodes specified by the int argument sent to the function.
*********************************************************************/

void CharacterList::populate(int numCharacters)
{
	for (int i = 0; i < numCharacters; i++)
	{
		if (!head)
		{
			head = new characterNode();
			tail = head;
		}
		else if(head == tail && head != nullptr)
		{
			tail = new characterNode(head);
			head->next = tail;
		}
		else 
		{
			characterNode* temp = tail;
			tail = new characterNode(tail);
			temp->next = tail;
		}
	}


}

/*********************************************************************
**  getCharacterUp : Return a pointer to the current character object
** pointed to by the head pointer.
*********************************************************************/

Character* CharacterList::getCharacterUp()
{
	if (head)
	{
		return head->playerCharacter;
	}
	else
	{
		return nullptr;
	}
}

/*********************************************************************
**  currentLost : This is called when the current character pointed to
** by head has lost the match. It sends the character in the node
** pointed to by the head pointer to the lostPlayerStack
*********************************************************************/

void CharacterList::currentLost()
{
	if (head)
	{
		lostPlayerStack->push(head->playerCharacter);
		characterNode *temp = head;
		head = head->next;
		delete temp;
	}
}

/*********************************************************************
**  currentWon : Called when the urrent character pointed to
** by head has won the match. It replenishes a random amount of health
** and places the node at the end of the list. It also returns the 
** amount of health replenished as an int.
*********************************************************************/

int CharacterList::currentWon()
{
	int replenished;
	if (head)
	{
		if (head->next == nullptr)
		{ 
			replenished = replenishHealth(head->playerCharacter);
		}
		else
		{
			replenished = replenishHealth(head->playerCharacter);
			characterNode *temp = head;
			head = head->next;
			head->prev = nullptr;
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			tail->next = nullptr;
		}
	}
	return replenished;
}

/*********************************************************************
**  replenishHealth : Replenishes health for the character sent as a
** Character* argument. The amount of health replenished will not exceed
** that character's max health. Health replenished is random. Returns
** an int representing the amound of health replenished.
*********************************************************************/

int CharacterList::replenishHealth(Character* playerCharacter)
{
	int addedStrength;
	int currentStrength = playerCharacter->getStrengthPoint();		//Get the current strength point
	int newStrength = playerCharacter->randomNumZero(playerCharacter->getMaxStr() / 2) + currentStrength;	//The amout of health replenished will 
																											//be between 0 and half of the max strength
	if (newStrength >= playerCharacter->getMaxStr())					//If max strength is exceeded, set to max strength.
	{
		playerCharacter->setStrengthPoint(playerCharacter->getMaxStr());
		addedStrength = playerCharacter->getMaxStr() - currentStrength;
	}
	else
	{
		playerCharacter->setStrengthPoint(newStrength);					//Otherwise use the new strength.
		addedStrength = newStrength - currentStrength;
	}
	return addedStrength;
}