/****************************************************
 *Author: Jacob Leno
 *Date: 08/11/2018
 *Program: ftserver.c
 *Description: This program listens for a request from a client
 * at a port number specified as its first argument.
 ***************************************************/

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

enum Errors { SENDINGFILE = 0, SENDINGDIR, BADCOMMAND, BADFILE };

ssize_t readn(int fd, void *buffer, size_t n);
ssize_t writen(int fd, const void *buffer, size_t n);
int validatePort(char * portNum);
void sendResponse(int fd, int errNo, char* hostIP, char *msgPart[]);
char* getClientIP(int fd);
void listenSocketSetup(int *listenSocketFD, int portNumber);
int processMessage(char *msgPart[]);
void establishConnection(int *socketFD, char* hostIP, int hostPort);
void sendDir(int fd);
void sendFile(int fd, char *filename);


//This code was adapted from the "boilerplate" code server.c given in CS344

int main(int argc, char *argv[])
{
	int listenSocketFD, connectionP, portNumber;
	int i;
	unsigned short msgLen;
	socklen_t sizeOfClientInfo;
	struct sockaddr_in clientAddress;
	char *clientIP, *message, *msgPart[5];
	char *token, *originPtr;

	if (argc < 2) { printf("Port number must be given as second argument\n"); exit(1); } // Check args
	portNumber = validatePort(argv[1]);	//Make sure user entered a valid port number
	if(portNumber == -1) { printf("Please enter a valid port number between 0 and 65635\n"); exit(1); }

	listenSocketSetup(&listenSocketFD, portNumber);	
			
	// Accept a connection, blocking if one is not available until one connects
	sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect

	while(1)
	{
		connectionP = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
		if (connectionP < 0) error("ERROR on accept");

		clientIP = getClientIP(connectionP);
		
		msgLen = 0;
		if(read(connectionP, (void *)(&msgLen), sizeof(msgLen)) < 0 ){ //Read the length of the incoming message from the client
			fprintf(stderr, "Could not get incoming message\n");  //Make sure read() read more than 0 bytes
			exit(1);
		}
		msgLen = htons(msgLen);
		
		message = malloc(sizeof(char) * msgLen);
		originPtr = message; 	//Keep track of the original pointer so it can be deleted later
		readn(connectionP, message, msgLen);
		
		token = strtok(message, " ");
		i = 0;
		while(token != NULL && i < 5)
		{
			if (token != NULL)
			{
				msgPart[i] = (char*) malloc(strlen(token) * sizeof(char));
				strcpy(msgPart[i], token);
				i++;
			}
			token = strtok(NULL, " ");
		}
		printf("Connection from %s\n", msgPart[0]);

		sendResponse(connectionP, processMessage(msgPart), clientIP, msgPart);

		for(i = 0; i < 5; i++) free(msgPart[i]);
		free(originPtr);
	}

	close(connectionP);

	return 0; 
}


//This code was adapted from the "boilerplate" code client.c given in CS344
/*****************************************************
 *Function: establishconnection 
 *
 *Description: Takes a socket file descriptor as its first parameter, 
 * a c-string containing the host ip as its 2nd parameter, and an int
 * that represents the host's port number as its 3rd parameter.
 * This function sets up contact with a remote host at a given host name
 * and a given port number
 ****************************************************/
void establishConnection(int *socketFD, char* hostIP, int hostPort)
{
	int portNumber;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = hostPort; // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(hostIP); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(1); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	*socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (*socketFD < 0) { perror("CLIENT: ERROR opening socket"); exit(1); }
	// Connect to server
	if (connect(*socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){ // Connect socket to address
		perror("CLIENT: ERROR connecting");
		exit(1);
	}
	return;
}

/************************************************
 *Function: processMessage
 *
 *Description: 1st Argument is message from the client that
 * has been partitioned into seperate character arrays based
 * on how the message was spaced. This function looks at the
 * array and returns a number indicating whether or not the
 * client issued a good or bad command. 
 ************************************************/
int processMessage(char *msgPart[])
{
	struct stat fileStats;

	if(strcmp(msgPart[2], "-l") != 0 && strcmp(msgPart[2], "-g") != 0) return BADCOMMAND; //Second argument isnt either -l or -g, command is bad
	else if(strcmp(msgPart[2], "-l") == 0) //Second argument is -l
	{
		if (validatePort(msgPart[3]) == -1) return BADCOMMAND; //Third argument was not a valid port number
		else return SENDINGDIR;
	}
	else if(strcmp(msgPart[2], "-g") == 0) //Second argumetn is -g
	{
		if (stat(msgPart[3], &fileStats) != 0) return BADFILE; //File in third argument does not exist
		else return SENDINGFILE;
	}

	return BADCOMMAND;
}

/**********************************************
 *Function: sendResponse
 *
 *Description: Given a valid error number an a file
 * descriptor this funciton sends a response back 
 * to the client.
 *********************************************/

void sendResponse(int fd, int errNo, char *hostIP, char *msgPart[])
{
	char *badCmd = "INVALID COMMAND";
	char *badFile = "FILE NOT FOUND";
	char *clientIP = getClientIP(fd);
	unsigned short number = htons(errNo), clientResponse;
	int connectionQ; 
	write(fd, &number, 2);

	switch(errNo)
	{
		case BADCOMMAND:
				printf("Bad command recieved on port %s\n", msgPart[3]); 		//Client issued a bad command send an error message
				printf("Sending error message to %s:%s\n", clientIP, msgPart[3]);
				number = strlen(badCmd);
				number = htons(number);
				write(fd, &number, 2);
				writen(fd, badCmd, strlen(badCmd));
			break;
		case BADFILE:
				printf("File \"%s\" requested on port %s\n", msgPart[3], msgPart[4]);	//Client requested a bad file send an error message
				printf("File not found. Sending error message to %s:%s\n", clientIP, msgPart[4]);
				number = strlen(badCmd);
				number = htons(number);
				write(fd, &number, 2);
				writen(fd, badFile, strlen(badFile));
			break;
		case SENDINGDIR:
				printf("List directory requested on port %s\n", msgPart[3]);
				read(fd, (void *)(&clientResponse), sizeof(clientResponse)); //Get the response from the client indicating that it is ready to recieve a connection
				clientResponse = ntohs(clientResponse);
				if(clientResponse == 200)
				{
					establishConnection(&connectionQ, hostIP, atoi(msgPart[3]));
					printf("Sending directory contents to %s:%s\n", clientIP, msgPart[3]);
					sendDir(connectionQ);
				}
				close(connectionQ);
			break;	
		case SENDINGFILE:
				printf("File \"%s\" requested on port %s\n", msgPart[3], msgPart[4]);
				read(fd, (void *)(&clientResponse), sizeof(clientResponse)); //Get the response from the client indicating that it is ready to recieve a connection
				clientResponse = ntohs(clientResponse); 
				if(clientResponse == 200)
				{
					establishConnection(&connectionQ, hostIP, atoi(msgPart[4]));
					printf("Sending \"%s\" to %s:%s\n", msgPart[3], clientIP, msgPart[4]);
					sendFile(connectionQ, msgPart[3]);
				}
				close(connectionQ);
			break;
	}
	
}
/****************************************************
 *Function: sendFile
 *
 *Description: First argument is the file descriptor or an
 * open socket to send the file to. The second argument is the
 * name of the file to be sent. This function sends a 
 * text file to a given socket, each time a chunk of up to
 * 1000 bytes is sent and the size of the chunk precedes
 * the data. At the end of the transmission the number 0
 * is sent to indicate the end of the file.
 ***************************************************/
void sendFile(int fd, char *filename)
{
	FILE *openFile = fopen(filename, "r");
	if(openFile == NULL) { printf("Could not open file!\n"); return; }
	unsigned short chunkSize;
	int read;
	char buffer[1001];

	do
	{
		read = fread(buffer, 1, 1000, openFile); //Read from the file in 1000 byte chunks
		if(read > 0)
		{
			chunkSize = htons(read);
			write(fd, &chunkSize, 2);
			writen(fd, buffer, read);
		}
	} while(read == 1000);
	fclose(openFile);

	chunkSize = htons(0);  //End of the directory transmission
	write(fd, &chunkSize, 2);
}

//Code for this function adapted from https://www.sanfoundry.com/c-program-list-files-directory
/***********************************************
 *Function: sendDir
 *
 *Description: Takes a file descriptor to send the directory
 * structure to as its only argument. This function
 * gets the directory structure of the current working
 * directory and sends it to the socket indicated by fd.
 * Only the names of regular files in the directory
 * are sent
 **********************************************/
void sendDir(int fd)
{
	DIR *dirStream; //DIR is a data type that represents a directory stream
	struct dirent *directory; //The dirent structure represents the next directory entry in the directory stream
	unsigned short number;

	
	dirStream = opendir("."); //Open the current working directory
	if(dirStream)
	{		//For each item in the directory send it to the client
		while((directory = readdir(dirStream)) != NULL)
		{
			if(directory->d_type == DT_REG)
			{
				number = htons(strlen(directory->d_name));  //First get the size of the data to send
				write(fd, &number, 2);
				writen(fd, directory->d_name, strlen(directory->d_name)); //Write the data to the socket
			}
		}
		number = htons(0);  //End of the directory transmission
		write(fd, &number, 2);
	}
}

//The code for this function is from a class piazza post:
//https://piazza.com/class/jic8p6felt05rx?cid=676
/**********************************************
 * Function: getClientIP
 *
 * Description: This function gets a client's ip
 * from a file descriptor given as its only argument
 * and returns that IP as type char*
 *********************************************/

char* getClientIP(int fd)
{
	struct sockaddr_in addr; //Struct to hold IPv4 AF_INET sockets
	socklen_t addr_size = sizeof(struct sockaddr_in);
	int res = getpeername(fd, (struct sockaddr *)&addr, &addr_size);	//Returns the address of the peer connected to the socket fd
										//In the buffer pointed to by addr, addr_size indicates the 
										//amount of space pointed to by addr
	char *clientip = malloc(20);
	strcpy(clientip, inet_ntoa(addr.sin_addr)); //Converts the internet host address in the in_addr struct member of addr, sin_addr, to
						    //to a string in IPv4 dotted-decimal notation. It must be copied to a DA buffer because
						    //inet_ntoa returns a statically allocated string
	return clientip;
}


/************************************************
 * Function: validatePort
 *
 * Description: Validate that the given port number
 * is valid. The function takes a char* as it only 
 * argument and returns -1 if the port number is invalid.
 * If it is valid the function returns the port number
 * ********************************************/

int validatePort(char * portNum)
{
	int i, intNum;
	size_t length = strlen(portNum);
	
	if(length > 5) return -1;
	
	for(i = 0; i < length; i++)
	{
		if(portNum[i] < 48 || portNum[i] > 57) return -1;
	}

	intNum = atoi(portNum);
	if(intNum < 65536 && intNum >= 0) return intNum;
	else return -1;
}

//This code was adapted from the "boilerplate" code server.c given in CS344
/************************************************
 * Function: listenSocketSetup
 *
 * Description: Set up a socket to listen on a given port number
 ***********************************************/
void listenSocketSetup(int *listenSocketFD, int portNumber)
{
	struct sockaddr_in serverAddress;
	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	*listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (*listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(*listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(*listenSocketFD, 1); // Flip the socket on - it can now receive up to 1 connection

	printf("Server open on %d\n", portNumber);
}


/**************************************************
 *Function: readn
 *
 *Description: *This function was taken from an example
 * in the book "The Linux Programming Interface" on pg 1255
 * It takes a file descriptor to write to as its first argument,
 * a buffer to write from as its second argument, and how many
 * characters of the buffer to write as its third
 * This function will use a loop to restart the read system
 * call if it did not read the requested number of bytes
 *************************************************/

ssize_t readn(int fd, void *buffer, size_t n){
    ssize_t numRead;                    // # of bytes fetched by last read() 
    size_t totRead;                     // Total # of bytes read so far 
    char *buf;
    buf = buffer;                       // No pointer arithmetic on "void *" 
    for (totRead = 0; totRead < n; ) {
        numRead = read(fd, buf, n - totRead);
        if (numRead == 0)               // EOF 
            return totRead;             // May be 0 if this is first read() 
        if (numRead == -1) {
            if (errno == EINTR)
                continue;               // Interrupted --> restart read() 
            else
                return -1;              // Some other error 
        }
        totRead += numRead;
        buf += numRead; 		// Advance the buffer pointer to point to the last character read
    }
    return totRead;                     // Must be 'n' bytes if we get here 
}

/**************************************************
 *Function: writen
 *
 *Description: *This function was taken from an example
 * in the book "The Linux Programming Interface" on pg 1255
 * It takes a file descriptor to write to as its first argument,
 * a buffer to write from as its second argument, and how many
 * characters of the buffer to write as its third
 * This function uses a loop to restart the write system call
 * if not all the bytes in the buffer were written.
 * ***********************************************/
ssize_t writen(int fd, const void *buffer, size_t n)
{
    ssize_t numWritten;                 // # of bytes written by last write()
    size_t totWritten;                  // Total # of bytes written so far
    const char *buf;

    buf = buffer;                       // No pointer arithmetic on "void *" 
    for (totWritten = 0; totWritten < n; ) {
        numWritten = write(fd, buf, n - totWritten);

        if (numWritten <= 0) {
            if (numWritten == -1 && errno == EINTR)
                continue;               // Interrupted --> restart write() 
            else
                return -1;              // Some other error 
        }
        totWritten += numWritten;
        buf += numWritten;
    }
    return totWritten;                  // Must be 'n' bytes if we get here 
}

