/******************************************************************
 *Author: Jacob Leno
 *Date: 05/05/18
 *Assignment: Program 2 - Adventure
 *Description: Adventure buildroom file. This program builds a file for use
 * in the adventure program.
 *****************************************************************/

#include <time.h>
#include <stdio.h>
#include <string.h>

#define TOTALROOMS 7
#define TRUE 1
#define FALSE 0

struct Room {
	char roomName[9];
	int connections[6];
	int numConnections;
	int roomType;
	int roomNumber;
};

//Function Headers
struct Room GetRandomRoom(struct Room roomsArray[]);
void AddRandomConnection(struct Room originArray[]);
int IsGraphFull(struct Room tempRoomsArray[]);
int CanAddConnectionFrom(struct Room testRoom); 
int ConnectionAlreadyExists(struct Room roomOne, struct Room roomTwo);
void ConnectRoom(struct Room roomOne, struct Room roomTwo, struct Room originArray[]);
int IsSameRoom(struct Room roomOne, struct Room roomTwo);
void writeData(struct Room roomsArray[], char *directoryName);

int main(int argc, char *argv[]){


	int i, j, randNum;
	srand(time(NULL));
	char directoryName[30] = "lenoja.rooms.";
	char pid[10];
	struct Room roomsArray[TOTALROOMS];
	char namesArray[10][9] = {{"Hall"}, {"Study"}, {"Lounge"}, {"Kitchen"}, {"Attic"}, {"Basement"}, {"Library"}, {"Studio"}, {"Dungeon"}, {"Gym"}}; //All the rooms to be chosen at random for the file
	sprintf(pid, "%d", getpid());
	strncat(directoryName, pid, 10);
	mkdir(directoryName, 0755);

	randNum = rand() % 10; //Get a random number to start with
	for(i = 0; i < 7; i++){ //For 7 names add a new name to the struct
		strcpy(roomsArray[i].roomName, namesArray[randNum]); //Starting at a random name in the namesArray begin to fill roomsArray with room names
		roomsArray[i].roomNumber = i;
		roomsArray[i].numConnections = 0;
		if(i == 0) roomsArray[i].roomType = 0;
		else if (i == 6) roomsArray[i].roomType = 2;
		else roomsArray[i].roomType = 1;
		randNum++; //Increment randNum, and start again at 0 if it is 10 or greater
		if(randNum >= 10) randNum = 0;
	}
	
	//Create all connections in graph
	while (IsGraphFull(roomsArray) == FALSE)
	{
	  AddRandomConnection(roomsArray); 
	}
 
	writeData(roomsArray, directoryName);

	return 0;
}

/*****************************************
 *function: writeData
 *description: Writes data from roomsArray into seperate files, one for each room, contained
 * in the directory name given
 *parameters: 1st argument is an array of Room structures, 2nd Argument is a c-string containing the directory name
 *pre-conditions:  1st argument is populated with values corresponding to rooms for the game, 2nd argument
 * contains the name of a valid directory
 *post-conditions: None
 ****************************************/
void writeData(struct Room roomsArray[], char *directoryName){
   int i, j;
   FILE *outFile;
   char *room = ".room";
   char directory[30] = "./";
   char fileName[40];
   memset(fileName, '\0', 40);
   strncat(directory, directoryName, 20); //Build up the directory location so a file name can be added to it
   strncat(directory, "/", 2);
   
   for(i = 0; i < TOTALROOMS; i++){
      strcpy(fileName, directory); //Add the name of the room file we want to create
      strncat(fileName, roomsArray[i].roomName, 10);
      strncat(fileName, room, 6);
      outFile = fopen(fileName, "w");
      fprintf(outFile, "ROOM NAME: %s\n", roomsArray[i].roomName); 
      for(j = 0; j < roomsArray[i].numConnections; j++){ // Add the names of each room connection in the struct
	fprintf(outFile, "CONNECTION %d: %s\n", (j+1), roomsArray[roomsArray[i].connections[j]].roomName);
      }
      if(roomsArray[i].roomType == 0){ //Get the room type and add it to the file
	fprintf(outFile, "ROOM TYPE: START_ROOM\n"); 
      } else if (roomsArray[i].roomType == 2){
	fprintf(outFile, "ROOM TYPE: END_ROOM\n");
      } else if (roomsArray[i].roomType == 1){ 
	fprintf(outFile, "ROOM TYPE: MID_ROOM\n"); 
      }

      memset(fileName, '\0', 40); // Set the filename back to all null terminators
      fclose(outFile);
   } 
}

/*****************************************
 *function: GetRandomRoom
 *description: Returns a random Room, does NOT validate if connection can be added
 *parameters: An array of struct Room
 *pre-conditions: The array is filled Rooms
 *post-conditions: Returns a random element from the array 
 ****************************************/
struct Room GetRandomRoom(struct Room roomsArray[])
{
   int randNum;
   randNum = rand() % TOTALROOMS;
   return roomsArray[randNum];
}

/*****************************************
 *function: AddRandomConnection
 *description: Adds a random, valid outbound connection from a Room to another Room
 *parameters: An array of struct Room
 *pre-conditions: The array is filled with Rooms initialized with proper values
 *post-conditions: A random connection is made between two of the rooms in the array
 ****************************************/
void AddRandomConnection(struct Room originArray[])  
{
  struct Room A;  
  struct Room B;
  int done, i;
  done = FALSE;
	
  do {	
    do {
	 A = GetRandomRoom(originArray);
    } while (CanAddConnectionFrom(A) == FALSE); //Keep getting a rancom room for A until a connection can be made to it
	 i = 0;
	 do {
	    B = GetRandomRoom(originArray);
	    if (CanAddConnectionFrom(B) == FALSE || IsSameRoom(A, B) == TRUE || ConnectionAlreadyExists(A, B) == TRUE) {
	      i++;
	    } else {
	      done = TRUE;
	    }
	  } while (i < 10 && done == FALSE); //Only check if a connection can be made to A up to 10 times, otherwise
  } while (done == FALSE);  		     //get a different value for A

  ConnectRoom(A, B, originArray); //Make connections to both rooms 
  ConnectRoom(B, A, originArray);  
}



/*****************************************
 *function: IsGraphFull
 *description: Returns true if all rooms have 3 to 6 outbound connections, false otherwise
 *parameters: An array of struct Room
 *pre-conditions: The array is initialized with proper values
 *post-conditions: An int representing the condition of the array. If there are still rooms with
 * less than 3 connections 0 representing false is returned otherwise 1 representing true is returned.
 ****************************************/
int IsGraphFull(struct Room tempRoomsArray[])  
{
  int i;
  for(i = 0; i < TOTALROOMS; i++){
	if(tempRoomsArray[i].numConnections < 3)
		return FALSE;	
  }
  return TRUE;
}


/*****************************************
 *function: CanAddConnectionFrom
 *description: Returns true if a connection can be added from Room x (< 6 outbound connections), false otherwise
 *parameters: A struct Room
 *pre-conditions: Struct room is initialized with proper values
 *post-conditions: If the struct room given has 6 or more values 0 representing false is returned. If it has
 * less than 6 values 1 representing true is returned.
 ****************************************/
int CanAddConnectionFrom(struct Room testRoom) 
{
  if(testRoom.numConnections <= 6)
	return TRUE;
  else
	return FALSE;
}


/*****************************************
 *function: ConnectionAlreadyExists
 *description: Returns true if a connection from roomOne to roomTwo already exists, false otherwise
 *parameters: 1st Parameter: A struct Room, 2nd Parameter: A struct Room
 *pre-conditions: Both parameters are initialized with proper struct Room values.
 *post-conditions: If a connection between the two rooms already exists 1 is returns, otherwise 0.
 ****************************************/
int ConnectionAlreadyExists(struct Room roomOne, struct Room roomTwo)
{
  int i;
  for(i = 0; i < roomOne.numConnections; i++){
	if(roomOne.connections[i] == roomTwo.roomNumber)
		return TRUE;	
  }
  return FALSE;
}

/*****************************************
 *function: ConnectRoom
 *description: Connects roomOne and roomTwo together, does not check if this connection is valid
 *parameters: 1st Parameter: A struct Room, 2nd Parameter: A struct Room, 3rd Parameter: A struct Room array
 *pre-conditions: All three parameters are initialized with proper values
 *post-conditions: 1st and 2nd struct Room parameters have one another on their list of connections
 ****************************************/
void ConnectRoom(struct Room roomOne, struct Room roomTwo, struct Room originArray[]) 
{
  originArray[roomOne.roomNumber].connections[roomOne.numConnections] = roomTwo.roomNumber;
  originArray[roomOne.roomNumber].numConnections++;
}

/*****************************************
 *function: IsSameRoom
 *description: Returns true if roomOne and roomTwo  are the same Room, false otherwise
 *parameters: 1st Parameter: A struct Room, 2nd Parameter: A struct Room
 *pre-conditions: Both parameters are initialized with proper values
 *post-conditions: If both parameters are the same room 1 is returned, otherwise 0 is returned
 ****************************************/
int IsSameRoom(struct Room roomOne, struct Room roomTwo)
{
  if(roomOne.roomNumber == roomTwo.roomNumber) return TRUE; 
  else return FALSE;
}
