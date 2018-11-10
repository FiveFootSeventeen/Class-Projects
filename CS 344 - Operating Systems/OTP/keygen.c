/****************************************************
 *Author: Jacob Leno
 *Date: 06/07/18
 *Program: keygen.c
 *Description: Creates a key file of a specified length.
 * the characters generated in the file will any of 
 * 27 characters (A-Z and Space).
 * *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int args, char *argv[]){
	if(args > 2) { perror("Too many arguments"); exit(1); }	 //If the user input too many arguments output to stderr
	srand(time(NULL));
	int i, randNum, numChars = atoi(argv[1]);

	for(i = 0; i < numChars; i++){
		randNum = rand() % 27; //Get a random number between 0 and 26
		if(randNum == 26) randNum = 32;  //If its 26 set it to a space
		else randNum += 65;
		printf("%c", randNum);	//Output to stdout
	}
	printf("\n");

	return 0;
}
