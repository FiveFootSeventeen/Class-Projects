/*********************************************************************
** Program Filename: circularList.c
** Author: Jacob Leno
** Date: 02/05/18
** Description: This program demonstrates the circular list data type
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->size = 0;
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *temp = malloc(sizeof(struct Link));
	assert(temp != 0);
	temp->next = NULL;		//Create a new Link assign NULL to next and prev pointers and return the link
	temp->prev = NULL;
	temp->value = value;
	return temp;	
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link *temp = createLink(value);
	link->next->prev = temp;
	temp->next = link->next;
	temp->prev = link;
	link->next = temp;
	temp->value = value;
	list->size += 1;
	temp = 0;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	struct Link *temp = list->sentinel->next;
	while (temp != list->sentinel && link != 0) {
		if (temp == link) {
			temp = temp->next;
			link->prev->next = link->next;
			link->next->prev = link->prev;
			free(link);
			link = 0;
			list->size -= 1;
		}
		else
			temp = temp->next;
	}		
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while(!circularListIsEmpty(list)){
		circularListRemoveFront(list);
	}	
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	if (list->sentinel->next != list->sentinel)
		return list->sentinel->next->value;
	else
		return 0;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	if (list->sentinel->prev != list->sentinel)
		return list->sentinel->prev->value;
	else
		return 0;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if (list->sentinel->next == list->sentinel)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	struct Link *temp = list->sentinel->next;
	if (list->sentinel->next != list->sentinel){
		printf("Here are the values in the list: ");
		while(temp != list->sentinel){
			printf(" %.2f", temp->value);
			temp = temp->next;
		}		
		printf("\n");
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	struct Link *front = list->sentinel->next;
	struct Link *back = list->sentinel->prev;
	int swaps = list->size;
	TYPE temp;

	while (swaps > 0) {
		temp = front->value;
		front->value = back->value;
		back->value = temp;
		swaps -= 2;
		back = back->prev;
		front = front->next;
	}
}
