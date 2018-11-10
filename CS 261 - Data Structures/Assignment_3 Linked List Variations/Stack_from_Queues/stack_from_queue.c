

/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Jacob Leno
 * Email: lenoja@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef TYPE
#define TYPE int
#endif


/**************************************
** Code from Worksheet 18
**************************************/

struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
};

//Initialize the sentinel link in the listQueue struct
void listQueueInit(struct listQueue *q) {
	struct link *lnk = (struct link *) malloc(sizeof(struct link));
	assert(lnk != 0); /* lnk is the sentinel */
	lnk->next = 0;
	q->firstLink = q->lastLink = lnk;
}

//Add a given value to the back of the listQueue struct
void listQueueAddBack(struct listQueue *q, TYPE e) {
	struct link * newLink = (struct link *) malloc(sizeof(struct link));
	assert(newLink != 0);
	q->lastLink->next = newLink;
	q->lastLink = newLink;
	newLink->value = e;
	newLink->next = NULL;
}

//Returns the value at the front of the queue
TYPE listQueueFront(struct listQueue *q) {
	assert(q->firstLink != q->lastLink);
	return q->firstLink->next->value;
}

//Removes the value at the front of the queue
void listQueueRemoveFront(struct listQueue *q) {
	struct link* temp = q->firstLink->next;
	if (q->firstLink->next == q->lastLink) {
		q->lastLink = q->firstLink;
		q->firstLink->next = NULL;
	}
	else {
		q->firstLink->next = q->firstLink->next->next;
	}
	free(temp);
	temp = NULL;
}

//Returns 1 if a given listQueue is empty and 0 if it is not
int listQueueIsEmpty(struct listQueue *q) {
	if (q->firstLink == q->lastLink) {
		return 1;
	}
	else {
		return 0;
	}
}

/***********************************************
**	Functions for implementing a stack data 
**	structure using a queue data structure
***********************************************/

//Struct for the stack built on a queue
struct linkedListStack {
	struct listQueue *queueStack;
};

//Initializes a given linkedListStack struct
void linkedListStackInit(struct linkedListStack * s) {
	s->queueStack = (struct listQueue *)malloc(sizeof(struct listQueue));
	listQueueInit(s->queueStack);
}

//Returns DA mem the size of a linkedListStack struct
struct linkedListStack* linkedListStackCreate() {
	return (struct linkedListStack *)malloc(sizeof(struct linkedListStack));
}

//Push a given value onto a linkedListStack struct
void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	assert(s != 0);
	listQueueAddBack(s->queueStack, d);
}

//Returns the top value in the given linkedListStack
TYPE linkedListStackTop(struct linkedListStack *s) {
	struct linkedListStack *tempStack = linkedListStackCreate();
	assert(tempStack != 0);
	assert(s->queueStack != 0);
	linkedListStackInit(tempStack);
	TYPE popVal;

	while (!listQueueIsEmpty(s->queueStack)) {		//Cycle through the whole stack copying the values at the bottom into a 
		popVal = listQueueFront(s->queueStack);		//temporary struct until the top value is found
		listQueueAddBack(tempStack->queueStack, popVal);
		listQueueRemoveFront(s->queueStack);
	}
	free(s->queueStack);
	s->queueStack = tempStack->queueStack;			//Copy the temp struct to s and return the top value
	tempStack->queueStack = NULL;
	free(tempStack);
	tempStack = NULL;
	return popVal;
}

//Removes the top value of a linked list stack
void linkedListStackPop(struct linkedListStack *s) {
	struct linkedListStack *tempStack = linkedListStackCreate();
	assert(tempStack != 0);
	assert(s->queueStack != 0);
	linkedListStackInit(tempStack);
	TYPE popVal;

	while (!listQueueIsEmpty(s->queueStack)) {		//Cycle through the entire stack until the final stack value is found
		popVal = listQueueFront(s->queueStack);		//Dont copy this final value into the temporary stack
		listQueueRemoveFront(s->queueStack);
		if (!listQueueIsEmpty(s->queueStack)) {
			listQueueAddBack(tempStack->queueStack, popVal);
		}
	}

	free(s->queueStack);							//Assign the temp stack to queueStack and set temp to NULL
	s->queueStack = tempStack->queueStack;
	tempStack->queueStack = NULL;
	free(tempStack);
	tempStack = NULL;
}

//Returns 1 if stack is empty and 0 if it is not
int linkedListStackIsEmpty(struct linkedListStack *s) {
	return listQueueIsEmpty(s->queueStack);
}

//Frees DA mem in the stack
void linkedListStackFree(struct linkedListStack *s) {
	while (!linkedListStackIsEmpty(s)) {
		linkedListStackPop(s);
	}
	free(s->queueStack->firstLink);
	free(s->queueStack);
	free(s);
	s = NULL;
}

//Prints out the values in the stack in the order they are stacked
void printStack(struct linkedListStack *s) {
	struct linkedListStack *tempStack = linkedListStackCreate();
	linkedListStackInit(tempStack);
	assert(tempStack != 0);
	int val;

	while (!listQueueIsEmpty(s->queueStack)) {
		val = linkedListStackTop(s);			//Cycle through the values in the stack and print them out
		printf("%d ", val);						//Store them in a temp stack
		linkedListStackPop(s);
		linkedListStackPush(tempStack, val);
	}
	while (!listQueueIsEmpty(tempStack->queueStack)) {
		val = linkedListStackTop(tempStack);	//The values now need to be reversed
		linkedListStackPop(tempStack);			//Cycle through them again and store them in the original
		linkedListStackPush(s, val);
	}

	free(tempStack->queueStack);
	free(tempStack);
	tempStack = NULL;
}


int main() {
	struct linkedListStack *myStack = linkedListStackCreate();
	linkedListStackInit(myStack);


	printf("Testing stack from queue implementation\n");
	printf("Stack is empty: %d\n", linkedListStackIsEmpty(myStack));
	printf("Push Stack:	5\n");
	linkedListStackPush(myStack, 5);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Push Stack:	4\n");
	linkedListStackPush(myStack, 4);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Push Stack:	3\n");
	linkedListStackPush(myStack, 3);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Push Stack:	2\n");
	linkedListStackPush(myStack, 2);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Push Stack:	1\n");
	linkedListStackPush(myStack, 1);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");


	printf("Pop Stack:	%d\n", linkedListStackTop(myStack));
	linkedListStackPop(myStack);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Pop Stack:	%d\n", linkedListStackTop(myStack));
	linkedListStackPop(myStack);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Pop Stack:	%d\n", linkedListStackTop(myStack));
	linkedListStackPop(myStack);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Pop Stack:	%d\n", linkedListStackTop(myStack));
	linkedListStackPop(myStack);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Pop Stack:	%d\n", linkedListStackTop(myStack));
	linkedListStackPop(myStack);
	printf("Stack Contents:	");
	printStack(myStack);
	printf("\n");
	printf("Stack is empty: %d\n", linkedListStackIsEmpty(myStack));
	printf("\nFreeing Stack\n");
	linkedListStackFree(myStack);
	return 0;
}