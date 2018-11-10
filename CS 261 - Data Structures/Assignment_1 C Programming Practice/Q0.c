/* CS261- Assignment 1 - Q. 0*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: This is simple demonstration of the use of pointers.
 * It demonstrates passing a variable by reference, printing addresses, variables
 * pointed to by pointers and printing variables themselves.
 */
 
#include <stdio.h>
#include <stdlib.h>


 /*********************************************************************
 ** Function: fooA
 ** Description: Displays the value of an int passed by reference, the address
 ** iptr is pointing to, and the address of iptr itself.
 ** Parameters: iptr is a pointer to an int
 ** Pre-Conditions: iptr is not null
 ** Post-Conditions: none, pointed to by iptr is unchanged
 *********************************************************************/
void fooA(int* iptr){
	printf("iptr value: %d\n", *iptr);
     
	printf("address pointed to by iptr: %p\n", iptr);
     
	printf("address of iptr: %p\n", &iptr);
}

int main(){
    
    int x =10;
	printf("address of x: %p\n", &x);
	fooA(&x);
	printf("value of x: %d\n", x);
    
    return 0;
}
