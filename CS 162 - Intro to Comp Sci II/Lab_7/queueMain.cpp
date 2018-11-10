/*********************************************************************
** Program Name:My Queue
** Author: Jacob Leno
** Date: 11/07/17
** Description: This program creates a circular linked list which allows
** the user to create a queue. The user can add to the end of this 
** queue, remove from the front, print the front variable, and print
** the entire list.
*********************************************************************/

#include "menu.hpp"
#include "Queue.hpp"

#include <iostream>

void menu(Queue&);

int main()
{
	Queue myQueue;

	menu(myQueue);

	return 0;
}

/*********************************************************************
** menu Function: This funcion gets input from the user, calls the
** appropriate functions in the Queue class and display's the results.
*********************************************************************/

void menu(Queue &myQueue)
{
	int choice;
	cout << "Welcome to My Queue!" << endl;
	do
	{
		choice = intMenu("\nPlease make a selection:\n"
			"\n1. Add a value to the back of the queue"
			"\n2. Display the front value"
			"\n3. Remove the front node"
			"\n4. Display the queue's content"
			"\n5. Exit",
			false, 5, 1);

		if (choice == 1) 
		{
			myQueue.addBack(intMenu("Please enter a positive integer:", false, 1000000));
		}
		if (choice == 2)
		{
			if (myQueue.getFront() > 0) 
			{
				cout << "The first node value is : " << myQueue.getFront() << endl;
			}
			else
			{
				cout << "The queue is empty" << endl;
			}
		}
		if (choice == 3)
		{
			myQueue.removeFront();
		}
		if (choice == 4)
		{
			myQueue.printQueue();
		}


	} while (choice != 5);

}