/*********************************************************************
** Program Filename: toDoList.c
** Author: Jacob Leno
** Date: 03/01/2018
** Description: Function implementations for the to do list.
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
	int i;

	for (i = 0; i < heap->size; i++) {		//Go through the entire heap and save each task
		TYPE tempType = heap->data[i];
		fprintf(filePtr, "%d", tempType.priority);
		fprintf(filePtr, "\t%s\n", tempType.description);
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	assert(filePtr != NULL);
	int priority;
	TYPE tempTask;

	freeDynArr(heap);
	heap->data = (TYPE *)malloc(sizeof(TYPE) * 10);
	assert(heap->data != 0);
	heap->size = 0;
	heap->capacity = 10;
	char buffer[128], description[TASK_DESC_SIZE] = "";
	char next;

	while (fscanf(filePtr, "%s", buffer) != EOF) {		//Check the next char of input and make a decision based on what it is
		next = fgetc(filePtr);
		ungetc(next, filePtr);

		if (next == '\t') {
			sscanf(buffer, "%d", &priority);		//If next input is a tab convert the priority to an int
			strcpy(buffer, "");
			strcpy(description, "");
		}
		else if (next == 32) {
			strcat(description, buffer);			//If it is a space add the buffer to the description and a space
			strcat(description, " ");
		}
		else if (next == '\n') {					//If a newline, then we've reached the end
			strcat(description, buffer);
			tempTask = createTask(priority, description);
			addHeap(heap, tempTask);
			strcpy(description, "");
			strcpy(buffer, "");
		}
	}
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
	int i;
	assert(heap != 0);
	TYPE tempType;
	DynArr tempArr;
	initDynArr(&tempArr, heap->capacity);
	copyDynArr(heap, &tempArr);

	for (i = heap->size; i > 0; i--) {				//Print out each item in the temporary list, starting with the smallest
		tempType = getMinHeap(&tempArr);
		removeMinHeap(&tempArr);
		printf("%d", tempType.priority);
		printf("\t%s\n", tempType.description);
	}

	free(tempArr.data);
	tempArr.data = 0;
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
