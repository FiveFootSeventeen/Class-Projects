/******************************************************************
 *Author: Jacob Leno
 *Date: 05/05/18
 *Assignment: Program 2 - Adventure
 *Description: Adventure buildroom file. This program will start the 
 * adventure game. It requires the buildroom file to be run first
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define TOTALROOMS 7
#define TRUE 1
#define FALSE 0

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct Room {
	char roomName[9];
	char connections[6][9];
	int numConnections;
	int roomNumber, roomType;
};

//Function Headers
void getMostRecentDirName(char *);
void readFileDataIn(char *, struct Room *);
void startGame(struct Room *);
struct Room getStartRoom(struct Room *);
int changeRoom(struct Room *currentRoom, struct Room roomsArray[], char *);
int checkWin(struct Room);
void *writeTime();
void displayTime();

int main(int argc, char *argv[]){
	struct Room roomsArray[TOTALROOMS];
	char mostRecentDir[30] = "./";	

	memset(mostRecentDir, '\0', sizeof(mostRecentDir));

	getMostRecentDirName(mostRecentDir); //Get the name of the most recently created directory
	readFileDataIn(mostRecentDir, roomsArray); //Get the data from the most recent directory
	startGame(roomsArray); //Start the adventure game

	return 0;
}


/*****************************************
 *Function: startGame
 *Description: Called from main to begin the adventure game
 *Parameters: An initialized struct Room array
 *Pre-Conditions: The struct Room array is initialized with proper values. All rooms connections
 * have a corresponding connection.
 *Post-Conditions: None
 ****************************************/
void startGame(struct Room roomsArray[]){
	struct Room currentRoom;
	int steps = 0, playing, i, nextRoomNum, path[200], numCharsEntered;
	char *userInput = NULL;
	size_t bufferSize = 0;
	pthread_t thread;

	currentRoom = getStartRoom(roomsArray); //Get the starting room to begin the game
	playing = TRUE;
	while (playing){
		pthread_mutex_trylock(&lock); //Lock the mutex if it is not already locked
		pthread_create(&thread, NULL, writeTime, NULL); //Create a second thread that starts in the writeTime function
		printf("\nCURRENT LOCATION: %s\n", currentRoom.roomName); //Begin to print out game prompts
		printf("POSSIBLE CONNECTIONS: ");
		for(i = 0; i < (currentRoom.numConnections - 1); i++){ //Print out all connections in the current room
			printf("%s, ", currentRoom.connections[i]);
		}
		printf("%s.\n", currentRoom.connections[currentRoom.numConnections-1]);
		printf("WHERE TO? >");
		numCharsEntered = getline(&userInput, &bufferSize, stdin); //Get the choice from the user
		userInput[numCharsEntered - 1] = '\0'; //Remove the newline character from the end of the user's entry
		nextRoomNum = changeRoom(&currentRoom, roomsArray, userInput); //Get the value corresponding to the user's choice
		if(nextRoomNum == FALSE){
			printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		} else if (nextRoomNum == -1){ //User chose to see the time unlock the mutex lock on the second thread
			pthread_mutex_unlock(&lock);
			pthread_join(thread, NULL); //Wait for the second thread to finish what its doing
			displayTime(); //Display the time retrieved by the second thread
		} else {
			path[steps] = nextRoomNum;
			steps++;
			if(checkWin(currentRoom) == TRUE) playing = FALSE; //Check if the user is in the winning room
		}
		free(userInput);
		userInput = NULL;
		bufferSize = 0;
	}
	printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	for(i = 0; i < steps; i++){ //Output the path the user took
		printf("%s\n", roomsArray[path[i]-1].roomName); 
	}
	
}

/*****************************************
 *Function: displayTime
 *Description: Get the formatted time in the specified file and display it
 *Parameters: None
 *Pre-Conditions: currentTime.txt containes an updated time
 *Post-Conditions: Time is written to the console
 ****************************************/
void displayTime(){
	FILE* openFile;
	char currentTime[50];

	openFile = fopen("currentTime.txt", "r");
	fgets(currentTime, sizeof(currentTime), openFile);
	printf("\n%s\n", currentTime);
}

/*****************************************
 *Function: writeTime
 *Description: Write the current time to a specified file
 *Parameters: None
 *Pre-Conditions: None
 *Post-Conditions: Current time is formatted in a file called currentTime.txt
 ****************************************/
void *writeTime(){
	pthread_mutex_lock(&lock); //Bar the thread from continuing until the mutex is unlocked

	time_t t;
	char currentTime[50];
	struct tm *tmp;
	char *format = "%l:%M%P, %A, %B %d, %Y"; //Specify a format for the date to use in strftime function
	FILE *openFile;

	t = time(NULL); //Get the current time
	tmp = localtime(&t); //Convert the current time to tm struct type and assign it to the tm struct
	
	strftime(currentTime, sizeof(currentTime), format, tmp); //Convert the value in the struct to the format specified in the format variable
	openFile = fopen("currentTime.txt", "w");
	fputs(currentTime, openFile); //Put the data in the file specified in the file stream
	fclose(openFile);
	pthread_mutex_unlock(&lock); //Unlock the mutex to allow the main thread to pass
}

/*****************************************
 *Function: checkWin
 *Description: Checks to see if the current room is the end room 
 *Parameters: A struct Room
 *Pre-Conditions: The struct room is initialized with the proper values
 *Post-Conditions: If the given room is the end room 1 representing true is returned, otherwise 0 representing false is returned
 ****************************************/
int checkWin(struct Room currentRoom){
	if(currentRoom.roomType == 2) return TRUE;
	else return FALSE;
}

/*****************************************
 *function: changeRoom 
 *description:  Change the current room to what the user has specified
 *parameters: 1st Parameter: A struct Room, A struct Room array, A c-string
 *pre-conditions: 1st parameter is a properly initialized struct Room, 2nd Parameter is a properly
 * initialized struct Room array, 3rd parameter is a c-string representing the user's choice
 *post-conditions: If user has given input correctly corresponding to a room name currentRoom is changed
 * to the specified room and the number of that room is returned. If the user has given input that does not
 * correspond to a room or the time 0 is returned. If the user has asked for the time -1 is returned.
 ****************************************/
int changeRoom(struct Room *currentRoom, struct Room roomsArray[], char *userInput){
	int i, j;	
	if(strcmp(userInput, "time") == 0) return -1; // User has asked for the time return -1
	for(i = 0; i < currentRoom->numConnections; i++){
		if(strcmp(currentRoom->connections[i], userInput) == 0){  //Check user's input against all the room names
			for(j = 0; j < TOTALROOMS; j++){
				if(strcmp(roomsArray[j].roomName, userInput) == 0){
					*currentRoom = roomsArray[j];
					return (j+1);
				}	
			}	
		}  
	}
	return FALSE;
}

/*****************************************
 *function: 
 *description: 
 *parameters:
 *pre-conditions:
 *post-conditions:
 ****************************************/
struct Room getStartRoom(struct Room roomsArray[]){
	int i;

	for(i = 0; i < TOTALROOMS; i++){
		if(roomsArray[i].roomType == 0){
			return roomsArray[i];
		}
	}
}

/*****************************************
 *function: readFileDataIn
 *description: Read file data into a struct Room array
 *parameters: 1st Parameter: a c-string representing the directory to get the data from, 2nd Parameter: an 
 * unitialized struct Room array
 *pre-conditions: 1st parameter contains the name of a valid directory
 *post-conditions: 2nd parameter contains the data from the room files found in the directory
 ****************************************/
void readFileDataIn(char *directory, struct Room roomsArray[]){
	struct dirent* pdir;
	DIR* dir;
	char fileLocation[40], roomName[10], numChar[3];
	FILE *openFile;
	int roomNumber, i, j;
	
	memset(fileLocation, '\0', sizeof(fileLocation));

	dir = opendir(directory);
	i=0;
	while((pdir = readdir(dir)) != NULL){ //Read through each file in the directory
		if(strstr(pdir->d_name, ".room") != NULL){
			strcpy(fileLocation, directory);
			strcat(fileLocation, pdir->d_name);
			openFile = fopen(fileLocation, "r");
			fscanf(openFile, "%*s %*s %s", roomName); //Get the room name
			strcpy(roomsArray[i].roomName, roomName); //Copy the room name into the struct	
			roomsArray[i].roomNumber = i+1;  //Copy the room number into the struct
			fscanf(openFile, "%*s %s %s", numChar, roomName);
			j = 0;
			while (atoi(numChar) != 0){ //While the second parameter contains an int get each connection name and number
				roomNumber = atoi(numChar);
				strcpy(roomsArray[i].connections[j], roomName);
				fscanf(openFile, "%*s %s %s", numChar, roomName);
				j++;
			}
			roomsArray[i].numConnections = j; //Set the number of connections
			 //The room type is in roomName now it can be added to the struct
			if(strcmp(roomName, "START_ROOM") == 0){
				roomsArray[i].roomType = 0;
			} else if (strcmp(roomName, "MID_ROOM") == 0){
				roomsArray[i].roomType = 1;
			} else {
				roomsArray[i].roomType = 2;
			}

			fclose(openFile);
			i++;
		}
	}
}


/*****************************************
 *function: getMostRecentDirName
 *description: Get the name of the most recently created directory
 *parameters: An editable c-string to be set to the name of the most recently created directory
 *pre-conditions: None
 *post-conditions: Given c-string has the name of the most recent directory
 ****************************************/
void getMostRecentDirName(char *dirReturned){
	int newestDirTime = -1; //Modified timestamp of newest subdir examined
	char targetDirPrefix[30] = "lenoja.rooms.";  //Prefix to look for
	char newestDirName[256];  //Holds the name of the newest dir that contains prefix
	memset(newestDirName, '\0', sizeof(newestDirName));

	DIR* dirToCheck;  //Holds the directory we're starting in
	struct dirent *fileInDir;  //Holds the current subdir of the starting directory
	struct stat dirAttributes;  //Holds information gained about subdir

	dirToCheck = opendir("."); //Open up the directory this program was run in

	if(dirToCheck > 0){ //Make sure the current directory could be opened
		while((fileInDir = readdir(dirToCheck)) != NULL){ //Check each entry in dir
			if(strstr(fileInDir->d_name, targetDirPrefix) != NULL){ //If the entry has the prefix
				stat(fileInDir->d_name, &dirAttributes); //Get attributes of the entry
				if ((int)dirAttributes.st_mtime > newestDirTime){ //If this time is bigger
					newestDirTime = (int)dirAttributes.st_mtime;
					memset(newestDirName, '\0', sizeof(newestDirName));
					strcpy(newestDirName, fileInDir->d_name);
				}	
			}
		}
	}
	closedir(dirToCheck); //Close the directory
	strcat(dirReturned, newestDirName);
	strcat(dirReturned, "/");
}

