/*********************************************************************
** Class Name: Queue
** Author: Jacob Leno
** Date: 11/07/17
** Description: This is the function implementation file for the
** Queue class. It contains the function definitions for the class.
** The functions in this class are called from main and are used to 
** create a circular linked list where each node in the list contains
** a integer value and a pointer to the next and previous node.
*********************************************************************/

#include "Queue.hpp"

#include <iostream>
using std::cout;
using std::endl;

/*********************************************************************
** addBack Function: adds a a node to the back of the circular linked
** list (The node pointed to by the *prev pointer in head).
*********************************************************************/

void Queue::addBack(int val)
{
	if (!head)				//If head is equal to nullptr
	{
		head = new QueueNode(val);
		head->next = head;
		head->prev = head;
	}
	else if (head == head->next)			//If there is only one value pointed to by head and its pointer members (itself)
	{
		head->prev = new QueueNode(val, head, head);
		head->next = head->prev;
	}
	else
	{
		QueueNode *temp = head->prev;							//Temp pointer equals the node previous to head
		head->prev = new QueueNode(val, head, head->prev);		//Head's prev pointer points to the new node and the new node(*next = head, *prev = head's prev)
		temp->next = head->prev;								//The original previous node's *prev pointer equals the new node.
	}

}

/*********************************************************************
** getFront Function: This function returns the value at the front of 
** the linked list. If there isn't anything in the list it returns -1.
** the My Queue program will never enter values other than positive integers
** so this is okay.
*********************************************************************/

int Queue::getFront()
{
	if (isEmpty())
	{
		return -1;
	}
	else
	{
		return head->val;
	}
}

/*********************************************************************
** removeFront Function:  Removes the node found at the beginning of the
** list. If there isn't anything in the linked list the function output's
** a message to the console.
*********************************************************************/

void Queue::removeFront()
{
	if (isEmpty())			//isEmpty returns true
	{
		cout << "The queue is empty" << endl;
	}
	else if (head == head->next)	//If there is one value in the queue
	{
		delete head;
		head = nullptr;
	}
	else if (head->prev == head->next)		//If there are two values in the queue
	{
		QueueNode *temp = head;
		head = head->next;
		head->prev = head;				//Delete the first value. Now head points to the last remaining
		head->next = head;				
		delete temp;
	}
	else								//If there are more than two values in the queue
	{
		QueueNode *temp = head;			//Temp equal's head
		head = head->next;				//Head is equal to the next value in the list
		(temp->prev)->next = head;		//Match up the *next and *prev pointers in the 
		head->prev = temp->prev;		//nodes before and after the recently deleted one
		delete temp;					//Delete the original next node.
	}
}

/*********************************************************************
** printQueue Function: Prints out the queue to the console
*********************************************************************/

void Queue::printQueue()
{

	if (isEmpty())		//If the queue is empty print out a message saying so
	{
		cout << "The queue is empty" << endl;
	}
	else
	{
		QueueNode *temp = head->next;
		cout << "Your queue is: " << head->val;

		while (temp != head)
		{
			cout << "  " << temp->val;
			temp = temp->next;
		}
		cout << endl;
	}

}

/*********************************************************************
** isEmpty Function: 
*********************************************************************/

bool Queue::isEmpty()
{
	return head == nullptr;
}

/*********************************************************************
** Queue Destructor: Deallocates any memory allocated to the queue that
** was not destroyed while the class object was in scope.
*********************************************************************/

Queue::~Queue()
{
	QueueNode *garbage = head;
	if (head)						//If head does not point to nullptr
	{
		if (head == head->next)		//If there is only one value pointed to by head
		{
			delete head;
			head = nullptr;
		}
		else if (head->prev == head->next)		//If there are only two value pointed to by head.
		{
			garbage = head->next;
			delete garbage;
			delete head;
		}
		else
		{
			(head->prev)->next = nullptr;
			while (head)
			{
				garbage = head;
				head = head->next;
				delete garbage;
			}
		}
	}

}

Queue::Queue(int val)
{ 
	head = new QueueNode(val);
	head->next = head;
	head->prev = head;
}