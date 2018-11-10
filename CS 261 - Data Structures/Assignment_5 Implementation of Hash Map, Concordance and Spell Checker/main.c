/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Jacob Leno
 * Date: 03/06/2018
 */
#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

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
			if (c >= 'A' && c <= 'Z') c += 32;			//Make sure each letter in the word returned is lower case.
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
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
	char *word;
	int i, wordCount = 0;
	int *wordPtr;
    clock_t timer = clock();
    HashMap *map = hashMapNew(10);
	HashLink *tempLink;
	FILE *readFile;
	readFile = fopen(fileName, "r");
	if (readFile == NULL) {
		printf("Could not open file: %s", fileName);
	}
    
	word = nextWord(readFile);
	while (word != NULL){					//For each word in the concordance hash it into the map, count how many times it has appeared
		wordPtr = hashMapGet(map, word);
		if (wordPtr != NULL) wordCount = *wordPtr;
		wordCount++;
		hashMapPut(map, word, wordCount);
		wordCount = 0;
		free(word);
		word = nextWord(readFile);
	};
	fclose(readFile);

	for (i = 0; i < hashMapCapacity(map); i++) {
		tempLink = map->table[i];				//Print out the words in the hash map with times they have appeared
		while (tempLink != NULL) {
			printf("%s: ", tempLink->key);
			printf("%d\n", tempLink->value);
			tempLink = tempLink->next;
		}
	}
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}