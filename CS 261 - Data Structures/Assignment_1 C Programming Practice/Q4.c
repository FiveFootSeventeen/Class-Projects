/* CS261- Assignment 1 - Q.4*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: This program creates an array of student structures.
 * The structures are filled with random scores and unique ids then displayed. 
 * The array is then sorted in ascending order according to the scores and displayed.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

/*********************************************************************
** Function: swap
** Description: Swaps the student structure values of two parameters by reference
** Parameters: 'a' and 'b' - the memory location of student structures
** Pre-Conditions: 'a' and 'b' are not null pointers
** Post-Conditions: The values at the memory locations of 'a' and 'b' are swapped
*********************************************************************/
void swap(struct student *studA, struct student *studB) {
	struct student tempStud;
	tempStud = *studA;
	*studA = *studB;
	*studB = tempStud;
}

//Code for quickSort adapted from youtube channel 'mycodeschool'
//https://www.youtube.com/watch?v=COk73cpQbFQ

/*********************************************************************
** Function: partition
** Description: Partitions an array student structures with all the scores less than arr[end] on
** the left of the partition index and all the scores greater on the right of the index
** Parameters: arr[] is a pointer to an int array, the start of the partition, the end of
** the partition
** Pre-Conditions: arr[] is a pointer to an array of student structures
** Post-Conditions: The current location of the partition index is returned
*********************************************************************/
int partition(struct student studArr[], int start, int end) {
	int pIndex = start;
	int i;
	for (i = start; i < end; i++) {		//Move scores less than arr[end] to the left of arr[pIndex]
		if (studArr[i].score <= studArr[end].score) {
			swap(&studArr[pIndex], &studArr[i]);
			pIndex++;
		}
	}
	swap(&studArr[pIndex], &studArr[end]);		//Move the partition value to the partition index location
	return pIndex;
}

/*********************************************************************
** Function: quickSort
** Description: Sorts an array of student structures in ascending score order
** Parameters: arr[] is a pointer to an array of integers, start and end are
** the portions to be sorted
** Pre-Conditions: arr[] is not a null ptr, start and end are within the bounds
** of the array
** Post-Conditions: The array pointed to by arr is an array sorted in ascending
** score order
*********************************************************************/
void quickSort(struct student studArr[], int start, int end) {
	int pIndex;
	if (start < end) {
		pIndex = partition(studArr, start, end);	//Partition the array and get the index
		quickSort(studArr, start, pIndex - 1);		//Sort the left part of the partition
		quickSort(studArr, pIndex + 1, end);		//Sort the right part of the partition
	}
}

/*********************************************************************
** Function: sort
** Description: Calls a sorting algorithm to sort an array of student structures
** Parameters: students is a pointer to an array of student structures, n is
** the size of the array
** Pre-Conditions: students is not a null ptr, n is the size of the array
** Post-Conditions: students points to an array of student structures sorted
** in ascending order by scores
*********************************************************************/
void sort(struct student* students, int n){
	quickSort(students, 0, n - 1);
}

int main(){
	int i, n = 10;
	unsigned seed = (int)time(0);
	srand(seed);
	struct student *stud = malloc(sizeof(struct student) * n);

	for (i = 0; i < n; i++) {	//Fill the array with random score values and unique IDs
		stud[i].id = i + 1;
		stud[i].score = rand() % 100 + 1;
	}
    
	printf("\nThe unsorted array of students:\n");	//Display the unsorted array
	for (i = 0; i < 10; i++) {
		printf("Student ID: %d score: %d%%\n", stud[i].id, stud[i].score);
	}

	sort(stud, n);
    
	printf("\nThe sorted array of students:\n");	//Display the sorted array
	for (i = 0; i < 10; i++) {
		printf("Student ID: %d score: %d%%\n", stud[i].id, stud[i].score);
	}
	
	if (stud != 0)		// Free DA mem
	{
		free(stud);
		stud = 0;
	}
    
    return 0;
}
