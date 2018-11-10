/* CS261- Assignment 1 - Q.3*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: This is a demonstration of a sorting algorithm.
 * An array of integers is created and filled with random values then these
 * values are displayed in the console. Then a sorting function is called which
 * sorts the array finally the sorted array is displayed.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

 /*********************************************************************
 ** Function: swap
 ** Description: Swaps the integer values of two parameters by reference
 ** Parameters: 'a' and 'b' - the memory location of integers
 ** Pre-Conditions: 'a' and 'b' are not null pointers
 ** Post-Conditions: The values at the memory locations of 'a' and 'b' are swapped
 *********************************************************************/
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//Code for quickSort adapted from youtube channel 'mycodeschool'
//https://www.youtube.com/watch?v=COk73cpQbFQ

/*********************************************************************
** Function: partition
** Description: Partitions an array with all the values less than arr[end] on
** the left of the partition index and all the values greater on the right of the index 
** Parameters: arr[] is a pointer to an int array, the start of the partition, the end of
** the partition
** Pre-Conditions: arr[] is a pointer to an array
** Post-Conditions: The current location of the partition index is returned
*********************************************************************/
int partition(int arr[], int start, int end) {
	int pIndex = start;
	int i;
	for (i = start; i < end; i++) {		//Move values less than arr[end] to the left of arr[pIndex]
		if (arr[i] <= arr[end]) {
			swap(&arr[pIndex], &arr[i]);
			pIndex++;
		}
	}
	swap(&arr[pIndex], &arr[end]);		//Move the partition value to the partition index location
	return pIndex;
}

/*********************************************************************
** Function: quickSort
** Description: Sorts an array of integers in ascending order
** Parameters: arr[] is a pointer to an array of integers, start and end are
** the portions to be sorted
** Pre-Conditions: arr[] is not a null ptr, start and end are within the bounds
** of the array
** Post-Conditions: The array pointed to by arr is an array sorted in ascending
** order
*********************************************************************/
void quickSort(int arr[], int start, int end) {
	int pIndex;
	if (start < end) {
		pIndex = partition(arr, start, end);	//Partition the array and get the index
		quickSort(arr, start, pIndex - 1);		//Sort the left part of the partition
		quickSort(arr, pIndex + 1, end);		//Sort the right part of the partition
	}
}

/*********************************************************************
** Function: sort
** Description: Calls a sorting algorithm to sort an array of integers
** Parameters: number a pointer to an array of integers, n is the size
** of the array
** Pre-Conditions: number is not a null ptr, n is the size of the array
** Post-Conditions: number points to a sorted array
*********************************************************************/
void sort(int* number, int n){
	quickSort(number, 0, n - 1);
}

int main(){
	int i, n = 20;
	int *arr = malloc(sizeof(int) * n);
	unsigned seed = (int)time(0);			//Seed rand() with system time
	srand(seed);
    
	for (i = 0; i < n; i++) {	//Fill with random numbers from 1-100
		arr[i] = rand() % 100 + 1;
	}
    
	printf("The contents of the array: ");		//Print the unsorted array
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	sort(arr, n);
    
	printf("The contents of the sorted array: "); //Print the sorted array
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	if (arr != 0)		// Free DA mem
	{
		free(arr);
		arr = 0;
	}
    
    return 0;
}
