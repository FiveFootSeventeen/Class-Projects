/****************************************************
 *Author: Jacob Leno
 *Date: 07/27/18
 *Program: chatclient.c
 *Description: Make a connection with the server at a given
 * address and port number. once a connection is established 
 * the client and server will begin sending messages to one 
 * another until the command \quit is recieved
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include <errno.h>

ssize_t sendMessage(int fd, const void *buffer, size_t n);
ssize_t recieveMessage(int fd, void *buffer, size_t n);
void initiateContact(int *socketFD, int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if(argc < 3) //Check to make sure at least two arguments were given when the program was started
	{
		fprintf(stderr, "First argument must be a hostname and the second a port to connect on\n");
		exit(1);
	}
	int socketFD, continueService = 1, charsEntered, handlesize = 0;
	size_t buffSize = 1024;
	char handle[13];
	char *msgBuf = malloc(sizeof(char) * buffSize);
	memset(msgBuf, '\0', buffSize);

	do //Get the name from the user
	{
		printf("Please enter up to a 10 character name: ");
		handlesize = getline(&msgBuf, &buffSize, stdin); //Getline returns the number of characters entered

	} while (handlesize > 11); //Continue to ask for a name if the user does not input something under 10 characters

	msgBuf[handlesize - 1] = '>'; //Add the line ending to the end of the handle
	msgBuf[handlesize] = ' ';
	handlesize += 2;
	strcpy(handle, msgBuf);

	char *message = malloc((sizeof(char) * buffSize) + handlesize); //Make sure message has enough room for the handle and msgBuf
	memset(message, '\0', buffSize + handlesize);
	
	initiateContact(&socketFD, argc, argv); //Set up the connection with the server
	
	while(continueService)
	{
		memset(msgBuf, '\0', buffSize);
		printf(handle);
		charsEntered = getline(&msgBuf, &buffSize, stdin);
		msgBuf[charsEntered - 1] = '\0'; //Remove the newline from the end of the input text
		
		if(strstr(msgBuf, "\\quit")) continueService = 0;  //If the user entered \quit the stop communication
;	

		strcpy(message, handle); //Attach the handle and the message to the buffer
		strncat(message, msgBuf, charsEntered);

		if(continueService)
		{
			continueService = sendMessage(socketFD, message, charsEntered + handlesize); //If we recieve back 0 bytes we know the server ended the connection
			if (!continueService) printf("Server ended connection\n");
		}

		memset(msgBuf, '\0', buffSize);
		if(continueService)
		{
			continueService = recieveMessage(socketFD, msgBuf, buffSize); //If we recieve back 0 bytes we know the server ended the connection
			if (!continueService) printf("Server ended connection\n");
		}

		printf("%s\n", msgBuf);
		memset(message, '\0', buffSize + handlesize);
	}

	free(message);
	free(msgBuf);
	close(socketFD); // Close the socket
	return 0;
}

//This code was adapted from the "boilerplate" code client.c given in CS344

/*****************************************************
 *Function: initiateContact
 *
 *Description: Takes a socket file descriptor as its first parameter, 
 * and int describing the number of strings in its third parameter, 
 * and an array of strings as its third parameter.
 * This function sets up contact with a remote host at a given host name
 * (argv[1]) and a given port number argv[2]
 ****************************************************/
void initiateContact(int *socketFD, int argc, char *argv[])
{
	int portNumber;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(argv[1]); // Convert the machine name into a special form of address
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
}

/**************************************************
 *Function: writen
 *
 *Description: This function was taken from an example
 * in the book "The Linux Programming Interface" on pg 1255
 * It takes a file descriptor to write to as its first argument,
 * a buffer to write from as its second argument, and how many
 * characters of the buffer to write as its third
 * This function uses a loop to restart the write system call
 * if not all the bytes in the buffer were written.
 *************************************************/
ssize_t sendMessage(int fd, const void *buffer, size_t n)
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

/*****************************************************
 *Function: recieveMessage
 *
 *Description: This function takes a socket file descriptor
 * as its first arguement, followed by a buffer to store the 
 * recieved message as its second and the size of the buffer
 * as its third. The size of the bytes recieved is returned as
 * ssize_t.
 * **************************************************/
ssize_t recieveMessage(int socketFD, void *msgBuf, size_t n)
{
	return read(socketFD, msgBuf, n);
}
