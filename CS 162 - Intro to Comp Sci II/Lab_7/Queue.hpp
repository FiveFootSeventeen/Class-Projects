/*********************************************************************
** Class Name: Queue
** Author: Jacob Leno
** Date: 11/07/17
** Description: This is the header file for the Queue class.
*********************************************************************/


#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
using std::cout;
using std::endl;

class Queue
{
protected:
	/*********************************************************************
	** QueueNode struct: This is a data structure that stores an integer value
	** and points to the QueueNode struct in front and behind it in a circular
	** linked list.
	*********************************************************************/
	struct QueueNode
	{
		QueueNode(int valIn, QueueNode *nextIn = nullptr, QueueNode *prevIn = nullptr)
		{
			val = valIn;
			next = nextIn;
			prev = prevIn;
		}
		QueueNode *next;
		QueueNode *prev;
		int val;
	};
	
	QueueNode *head;	//pointer to the first QueueNode object in the queue
	bool isEmpty();
public:
	~Queue();
	Queue() { head = nullptr; }		//Default constructor
	Queue(int val);
	void addBack(int val);
	int getFront();
	void removeFront();
	void printQueue();
};


#endif