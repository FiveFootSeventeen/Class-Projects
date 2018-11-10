/*********************************************************************
** Program Filename: linkedList.c
** Author: Jacob Leno
** Date: 01/26/18
** Description: This program demonstrates the deque and bag data types
*********************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to each other or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->next = 0;
	list->backSentinel->prev = list->frontSentinel;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(link->prev != 0);
	struct Link *temp = malloc(sizeof(struct Link));
	link->prev->next = temp;		//Create a temporary pointer to the new link and place the new
	temp->prev = link->prev;		//link before the given link
	temp->next = link;
	link->prev = temp;
	temp->value = value;
	list->size += 1;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != 0);
	assert(link != 0);
	struct Link *temp = list->frontSentinel;
	while(temp->next != link){
		temp = temp->next;
	}	
	temp->next = link->next;	//Change the next and prev pointers to point around the deleted link
	link->next->prev = temp;
	list->size -= 1;
	free(link);
	temp = 0;
}


/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))		
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	struct Link *temp = malloc(sizeof(struct Link));
	temp->next = list->frontSentinel->next;		
	list->frontSentinel->next->prev = temp;
	list->frontSentinel->next = temp;
	temp->prev = list->frontSentinel;
	temp->value = value;
	list->size += 1;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	struct Link *temp = malloc(sizeof(struct Link));
	temp->prev = list->backSentinel->prev;
	list->backSentinel->prev->next = temp;
	list->backSentinel->prev = temp;
	temp->next = list->backSentinel;
	temp->value = value;
	list->size += 1;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	struct Link *temp = list->frontSentinel->next;	
	assert(temp != 0);
	if(temp != list->backSentinel){				//Get the value at the front, reassign pointers to point around it
		list->frontSentinel->next = temp->next;	//and free the memory
		temp->next->prev = list->frontSentinel;
		list->size -= 1;
		free(temp);
		temp = 0;	
	}	
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	struct Link *temp = list->backSentinel->prev;
	assert(temp != 0);
	if(temp != list->frontSentinel){
		list->backSentinel->prev = temp->prev;	//Get the value at the back, reassign pointers to point around it
		temp->prev->next = list->backSentinel;	//and free the memory
		list->size -= 1;
		free(temp);
		temp = 0;
	}
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->frontSentinel->next == list->backSentinel){
		return 1;						//Check the list to see if any elements exist between the front
	} else {							//and back sentinel
		return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	struct Link *temp = list->frontSentinel->next;
	printf("Here are the values: ");
	while(temp != list->backSentinel){			//Loop though the list and print out the values in all the nodes
		printf("%d ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	struct Link *temp = list->frontSentinel;
	while(temp != list->backSentinel){				//Search through the entire bag for the given value
		if (temp->value == value)					//and return 1 if it is found
			return 1;	
		temp = temp->next;
	}	
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	struct Link *temp = list->frontSentinel;
	while (temp != list->backSentinel && temp != 0){		//Search through the entire bag for the given value
		temp = temp->next;									//and delete it if it is found
		if(temp->value == value){
			removeLink(list, temp);
			temp = 0;
		}	
	}
}
