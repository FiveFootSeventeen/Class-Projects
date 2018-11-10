/* CS261- Assignment 1 - Q.5*/
/* Name: Jacob Leno
 * Date: 01/19/18
 * Solution description: This program takes a single word and converts
 * it into stick caps. The word is then displayed to the console.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*********************************************************************
** Function: sticky
** Description: Takes a single word and converts it to sticky caps
** Parameters: A c-string of a single word
** Pre-Conditions: word is a c-string that consists of a single word
** Post-Conditions: word is a c-string in stick caps
*********************************************************************/
void sticky(char* word){
	int i = 0;
	int switchIt = 1;
	while (word[i] != '\0') {
		if (word[i] >= 'A' && word[i] <= 'Z' && switchIt == 0) {	//If the letter is uppercase and should be lowercase convert it
			word[i] = toLowerCase(word[i]);
		}
		if (word[i] >= 'a' && word[i] <= 'z' && switchIt == 1) {	//If the letter is lowercase and should be uppercase convert it
			word[i] = toUpperCase(word[i]);
		}
		i++;
		switchIt = 1 - switchIt;
	 }
}

int main(){
	char stickyStr[70];
	printf("Enter a string to be converted to sticky caps\n");
	scanf("%s", stickyStr);				//Get a word from the user
    
	sticky(stickyStr);
    
	printf("\nHere is the word in sticky caps: %s", stickyStr);
	printf("\n");
    
    return 0;
}
