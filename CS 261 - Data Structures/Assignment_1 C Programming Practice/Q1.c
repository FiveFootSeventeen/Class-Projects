/* CS261- Assignment 1 - Q.1*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: A short program that allocates memory to a struct pointer.
 * It then assigns random values to the id and score data members, prints out their
 * values, and prints out min, max, and average.
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
** Function: allocate
** Description: Allocates memory to a struct student pointer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a pointer to an array of 10 students structs
*********************************************************************/
struct student* allocate(){
	return malloc(sizeof(struct student) * 10);
}

/*********************************************************************
** Function: generate
** Description: Generates an id (1-10) and a random score (1-100) for each student
** Parameters: A pointer to an array of 10 student structs
** Pre-Conditions: students is not null
** Post-Conditions: none
*********************************************************************/
void generate(struct student* students){
	int i;
	for (i = 0; i < 10; i++) {
		students[i].id = i + 1;
		students[i].score = rand() % 100 + 1;
	}
}

/*********************************************************************
** Function: output
** Description: Outputs the id and score of each student
** Parameters: A pointer to an array of 10 initialized student structs
** Pre-Conditions: students is not null
** Post-Conditions: none
*********************************************************************/
void output(struct student* students){
	int i;
	for (i = 0; i < 10; i++) {
		printf("Student ID: %d score: %d%%\n", students[i].id, students[i].score);
	}
}

/*********************************************************************
** Function: summary
** Description: Outputs the min, max, and average score of 10 students
** Parameters: A pointer to an array of 10 initialized student structs
** Pre-Conditions: students is not null
** Post-Conditions: none
*********************************************************************/
void summary(struct student* students){
	int i, min = students[0].score;
	int max = students[0].score;
	float average = 0;

	for (i = 0; i < 10; i++) {
		if (students[i].score < min)
			min = students[i].score;
		if (students[i].score > max)
			max = students[i].score;
		average += students[i].score;
	}
	average = average / 10;
	printf("\n");
	printf("The minimum score: %d%%\n", min);
	printf("The maximum score: %d%%\n", max);
	printf("The average score: %.2f%%\n", average);
}

/*********************************************************************
** Function: deallocate
** Description: Deallocates data allocated to a student struct pointer
** Parameters: a pointer to DA student struct data.
** Pre-Conditions: none
** Post-Conditions: pointer sent as an argument will have its data deleted and 
** be set to null
*********************************************************************/
void deallocate(struct student* stud){
	if (stud != 0) {
		free(stud);
		stud = 0;
	}
}

int main(){
    struct student* stud = NULL;
	unsigned seed = (int)time(0);
	srand(seed);
    
	stud = allocate(); 
	generate(stud);
	output(stud);
	summary(stud);
	deallocate(stud);

    return 0;
}
