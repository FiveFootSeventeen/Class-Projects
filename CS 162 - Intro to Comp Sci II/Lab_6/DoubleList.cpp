/*********************************************************************
** Class Name: doubleList
** Author: Jacob Leno
** Date: 11/03/17
** Description: This is the function implementation file for the 
** DoubleList class. Call the menu function on a DoubleList object
** to start the program for creating a doubly-linked list.
*********************************************************************/

#include "DoubleList.hpp"

/*********************************************************************
** DoubleList destructor: Deletes any dynamic memory still allocated
** to the DoubleList object when it goes out of scope.
*********************************************************************/
DoubleList::~DoubleList()
{
	Node *garbage;
	while (head)
	{
		garbage = head;
		head = head->getNext();
		delete garbage;
	}
}

/*********************************************************************
** menu function: Gets an integer value representing the user's choice
** and calls the appropriate function via a switch statement.
*********************************************************************/

void DoubleList::menu()
{
	static int userChoice;
	cout << "Welcome to my linked list!\n\n";

	do
	{
		userChoice = intMenu("1. Add an element to the head of the list\n" \
							 "2. Add an element to the end of the list\n" \
							 "3. Remove the first element of the list\n" \
							 "4. Remove the last element of the list\n" \
							 "5. Print out the list in reverse\n" \
							 "6. Print out the first element in the list\n" \
							 "7. Print out the last element in the list\n" \
							 "8. Quit", \
							 false, 8, 1, true, \
							 "Please make a selection");
		switch (userChoice)
		{
		case 1: addHead(intMenu("Please enter the integer you would like to add", false, 10000, -10000));
			break;
		case 2: addTail(intMenu("Please enter the integer you would like to add", false, 10000, -10000));
			break;
		case 3: removeHead();
			break;
		case 4: removeTail();
			break;
		case 5: traverseRev();
			break;
		case 6: printHead();
			break;
		case 7: printTail();
			break;
		}

	} while (userChoice != 8);
}

/*********************************************************************
** traverse function: Prints out the doubly-linked list from front
** to back.
*********************************************************************/

void DoubleList::traverse()
{
	Node* listA = head;
	int count = 0;

	if (!listA) { cout << "The list is empty" << endl; }	//If listA is equal to nullptr let the user know
	else { cout << "Your linked list is: "; }

	while (listA)	//Print out listA's contents while it is not equal to nullptr
	{

		cout << listA->getVal() << "  ";
		listA = listA->getNext();
		++count;
		if (count % 7 == 0) { cout << endl << "\t\t     "; }	//When 7 values have been printed to the screen create a new line.
	}
	cout << endl;

}

/*********************************************************************
** traverseRev function: Prints out the doubly-linked list from back
** to front.
*********************************************************************/

void DoubleList::traverseRev()
{
	Node *listZ = tail;
	int counter = 0;

	if (!listZ) { cout << "The list is empty" << endl; }	//If listA is equal to nullptr let the user know
	else { cout << "Your reversed linked list is: "; }

	while (listZ)		//Print out listZ's contents while it is not equal to nullptr
	{
		cout << listZ->getVal() << "  ";
		listZ = listZ->getPrev();
		++counter;
		if (counter % 7 == 0) { cout << endl << "\t\t     "; }		//When 7 values have been printed to the screen create a new line.
	}
	cout << endl;
}

/*********************************************************************
** addHead function: This function takes an integer parameter and 
** adds that value at the head of the list.
*********************************************************************/

void DoubleList::addHead(int value)
{
	if (head == nullptr && tail == nullptr)		//If the list is empty create a new node
	{											//and set the head and tail to point to that node
		head = new Node(value);	
		tail = head;
	}
	else
	{
		Node *prevHead = head;					
		head = new Node(value, nullptr, prevHead);	//Point head to a new node in memory, pointing to head's previous value as its *next ptr
		prevHead->setPrev(head);					//The original node now has it previous pointer set to the new node
	}
	traverse();
}

/*********************************************************************
** addTail function: This function takes an integer parameter and 
** adds that value at the tail of the list.
*********************************************************************/

void DoubleList::addTail(int value)
{
	if (head == nullptr && tail == nullptr)		//If the list is empty create a new node
	{											//and set the head and tail to point to that node
		tail = new Node(value);
		head = tail;
	}
	else
	{
		Node *prevTail = tail;
		tail = new Node(value, prevTail);		//Point tail to a new node in memory, pointing its *prev pointer to the previous tail.
		prevTail->setNext(tail);				//Set the previous tail's *next pointer to the newly created node.
	}
	traverse();
}

/*********************************************************************
** removeHead function: Removes the value currently pointed to by the 
** head pointer.
*********************************************************************/

void DoubleList::removeHead()
{
	if (!head) 
	{
		cout << "No elements to remove" << endl;	//head points to a nullptr output a message saying so
		return; 
	}

	if (head->getNext() == nullptr)					//If the *next ptr in the node head is pointing to is a nullptr
	{												//delete the memory in head and set both head and tail to nullptr
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node *oldHead = head;		//Create a pointer to head's node
		head = head->getNext();		//Set head equal to the next node
		head->setPrev(nullptr);		//Set head's *prev pointer to nullptr
		delete oldHead;				//delete the memory stored at head's original location
	}
	traverse();
}

/*********************************************************************
** removeTail function: Removes the value currently pointed to by the
** tail pointer.
*********************************************************************/

void DoubleList::removeTail()
{
	if (!tail)
	{
		cout << "No elements to remove" << endl;		//tail points to a nullptr output a message saying so
		return;
	}

	if (tail->getPrev() == nullptr)				//If the *prev ptr in the node tail is pointing to is a nullptr
	{											//delete the memory in head and set both head and tail to nullptr
		delete tail;
		tail = nullptr;
		head = nullptr;
	}
	else
	{
		Node *oldTail = tail;			//Create a pointer to tail's node
		tail = tail->getPrev();			//Set tail equal to the previous node
		tail->setNext(nullptr);			//Set tail's *next pointer to nullptr
		delete oldTail;					//delete memory stored at tail's original location
	}
	traverse();
}

/*********************************************************************
** printHead function:	Print the value currently stored at the 
** location that head is pointing to.
*********************************************************************/

void DoubleList::printHead()
{
	if (head)
	{
		cout << "Head node value is: " << head->getVal() << endl;
	}
}

/*********************************************************************
** printTail function: Print the value curretnly stored at the location
** that head is pointing to.
*********************************************************************/

void DoubleList::printTail()
{
	if (tail)
	{
		cout << "Tail node value is: " << tail->getVal() << endl;
	}
}

