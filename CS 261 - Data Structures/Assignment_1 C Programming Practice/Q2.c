/* CS261- Assignment 1 - Q.2*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: This program defines several integers and initializes them
 * Then passes them to a function which alters them. The result is then printed in main
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*********************************************************************
 ** Function: foo
 ** Description: This function takes a and b by address and c by value. Alters
 ** the value at the address of a and b and assigns that to c. Then c is returned
 ** Parameters: a an int address, b an int address, and c an int value
 ** Pre-Conditions: and and b are an int address, c is an int value
 ** Post-Conditions: the values at the address of a and b are altered and c is returned
 *********************************************************************/
int foo(int* a, int* b, int c){
	(*a) = 2 * (*a);
	(*b) = (*b) / 2;
	c = *a + *b;
	return c;
}

int main(){
	int x = 5, y = 6, z = 7;
	printf("x = %d y = %d z = %d\n", x, y, z);
	printf("returned value: %d\n", foo(&x, &y, z));
	printf("x = %d y = %d z = %d\n", x, y, z);
 
	//The return value is different because the address of z was not sent to foo
	//the value of z was sent by value. A local variable was created in foo and assigned
	//the value of z then it was destroyed when it went out of scope.
    return 0;
}
    
    
