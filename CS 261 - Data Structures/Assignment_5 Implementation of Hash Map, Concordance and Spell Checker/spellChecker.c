/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Jacob Leno
 * Date: 03/06/2018
 */
#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hashFunction1(const char* key);
int hashFunction2(const char* key);

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
	assert(file != NULL);
	assert(map != NULL);
	char *word;

	word = nextWord(file);
	while (word != NULL) {			//For each word in the dictionary, add it to the hash map
		hashMapPut(map, word, 0);
		free(word);
		word = NULL;
		word = nextWord(file);
	}
}

/**
* Calculates the Levenshtein distance between two given words
* argument.
* @param The base word to be compared
* @param The word the base word is being compared against
* @return an int representing the Levenshtein distance between the two words
*/
int getLevDistance(char *baseWord, char *compareWord) {
	int lengthDiff, lengthBase, lengthCompare, i, levDist;
	lengthBase = (int)strlen(baseWord);
	lengthCompare = (int)strlen(compareWord);
	lengthDiff = lengthBase - lengthCompare;

	levDist = 0;
	if (lengthDiff < 0) {									//The base word was smaller than the compared word so dont add the absolute value of lengthCompare
		for (i = 0; i < lengthBase; i++) {
			if (baseWord[i] != compareWord[i]) levDist++;
		}
		levDist += abs(lengthCompare);
	} else {
		for (i = 0; i <= (lengthBase - 1); i++) {
			if (i <= (lengthCompare - 1)) {
				if (baseWord[i] != compareWord[i]) levDist++;
			}
			else {
				levDist++;
			}
		}
	}
	return levDist;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
	const char* fileName = "dictionary.txt";
	if (argc > 1)
	{
		fileName = argv[1];
	}
	printf("Opening file: %s\n", fileName);

    HashMap* map = hashMapNew(1000);
	HashLink *tempLink;
    FILE* file = fopen(fileName, "r");
    clock_t timer = clock();
	int idx, levDist, printLev, wordsPrinted, i;
	int goodWord = 0;
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        if (strcmp(inputBuffer, "quit") == 0) {
            quit = 1;
		} else {
			idx = HASH_FUNCTION(inputBuffer) % map->capacity;					
			if (idx < 0) idx += map->capacity;
			tempLink = map->table[idx];
			while (tempLink != NULL) {											//Check through each value in the hash bucket to see if it is the given key
				levDist = getLevDistance(inputBuffer, tempLink->key);
				if (strcmp(tempLink->key, inputBuffer) == 0 && levDist == 0) {
					goodWord = 1;
					tempLink = NULL;
				} else {
					tempLink->value = levDist;
					tempLink = tempLink->next;
				}
			}
			if (goodWord != 1) {												//If the given key was not found assign a levenshtein distance to each word in the hash table
				for (i = 0; i < (map->capacity - 1); i++) {
					tempLink = map->table[i];
					while (tempLink != NULL) {
						levDist = getLevDistance(inputBuffer, tempLink->key);
						tempLink->value = levDist;
						tempLink = tempLink->next;
					}
				}
			}
		}
		if (quit != 1) {
			if (goodWord == 1) {
				printf("Word spelled correctly\n");
				goodWord = 0;
			}
			else {
				printf("Did you mean one of these words; \n");
				printLev = 1;
				wordsPrinted = 0;
				while (wordsPrinted < 5) {										//Starting with the lowest levenshtein distance print out the first five
					i = 0;														//closest matching words
					while (i < (map->capacity - 1) && wordsPrinted < 5){
						tempLink = map->table[i];
						while (tempLink != NULL && wordsPrinted < 5) {
							if (tempLink->value == printLev && wordsPrinted < 4) {
								printf("%s, ", tempLink->key);
								wordsPrinted++;
							}
							else if (tempLink->value == printLev && wordsPrinted == 4) {
								printf("or %s?\n", tempLink->key);
								wordsPrinted++;
							}
							tempLink = tempLink->next;
						}
						i++;
					}
					printLev++;
				}

			}
		}
    }
    
    hashMapDelete(map);
    return 0;
}

