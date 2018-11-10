/****************************************************
 *Author: Jacob Leno
 *Date: 06/09/18
 *Program: otp_enc_d
 *Description: This program acts as a daemon and connect up to
 * 5 otp_enc proccesses at once. When otp_enc_d connects to a process
 * it will receive data from otp_enc and encrypt it sending
 * the endrypted message back to otp_enc
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

ssize_t readn(int fd, void *buffer, size_t n);
ssize_t writen(int fd, const void *buffer, size_t n);
char getChar(int num);
int getInt(char charIn);

int main(int argc, char *argv[])
{
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead, childProcesses, childExitMethod;
	int spawnPid, i, msgLen, ptLength, keyInt, ptInt, otp_encID = -20;
	pid_t childPid;
	socklen_t sizeOfClientInfo;
	char *ptBuffer, *keyBuffer, *encBuffer;
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	childProcesses = 0;
	while(1){
		if(childProcesses >= 5){
			childPid = wait(&childExitMethod);
			if(childPid < 0) { fprintf(stderr, "Wait failed\n"); exit(1); break; }
			--childProcesses;
		} else {
			spawnPid = fork();
			switch(spawnPid){
				case -1: { fprintf(stderr, "Fork failed, couldn't spawn child process\n"); exit(1); break; }
				case 0: { 
					// Accept a connection, blocking if one is not available until one connects
					sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
					establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
					if (establishedConnectionFD < 0) error("ERROR on accept");

					otp_encID = htonl(otp_encID);
					write(establishedConnectionFD, &otp_encID, sizeof(otp_encID)); //Send the id of the otp_enc program over first

					msgLen = 0;
					if(read(establishedConnectionFD, &msgLen, sizeof(msgLen)) < 0 ){ //Read the length of the incoming message from the client
						fprintf(stderr, "Could not read length of incoming message\n");  //Make sure read() read more than 0 bytes
						exit(1);
					}
					ptLength = msgLen = ntohl(msgLen); //Return the value in msgLen back to host byte order
					
					ptBuffer = malloc((msgLen * sizeof(char)) + 1); //Create enough memory to hold the entire message
					memset(ptBuffer, '\0', msgLen + 1);
					if(readn(establishedConnectionFD, ptBuffer, msgLen) != msgLen){
							fprintf(stderr, "CLIENT: ERROR reading from socket\n");
							exit(1);	
					}
						
					msgLen = 0;
					if(read(establishedConnectionFD, &msgLen, sizeof(msgLen)) < 0 ){ //Read the length of the incoming message from the client
						fprintf(stderr, "Could not read length of incoming message\n");  //Make sure read() read more than 0 bytes
						exit(1);
					}
					msgLen = ntohl(msgLen); //Return the value in msgLen back to host byte order

					keyBuffer = malloc((msgLen * sizeof(char)) + 1);
					memset(keyBuffer, '\0', msgLen + 1);
					if(readn(establishedConnectionFD, keyBuffer, msgLen) != msgLen){
							fprintf(stderr, "CLIENT: ERROR reading from socket\n");
							exit(1);	
					}
					
					encBuffer = malloc((ptLength * sizeof(char)) + 1); //Allocate enough space in the encBuffer to hold the encrypted message
					memset(encBuffer, '\0', ptLength + 1); 
					for(i = 0; i < ptLength; i++){
						ptInt = getInt(ptBuffer[i]); //Get the int associated with the current char in the ptBuffer
						keyInt = getInt(keyBuffer[i]); //Get the int associated with the current char in the keyBuffer
						encBuffer[i] = getChar((keyInt + ptInt) % 27); //Get the encrypted char and store it in the encBuffer
					}
					
					writen(establishedConnectionFD, encBuffer, ptLength);

					free(encBuffer);
					free(ptBuffer);	
					free(keyBuffer);
					exit(0);
					break;
				}
				default:{
					childProcesses++;
				}
			}
		}
	}
			

	close(listenSocketFD); // Close the listening socket
	return 0; 
}

/**************************************************
 *Function: writen
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

/*************************************************
 *Function: getChar
 *
 *Description: returns the corresponding character of a
 * given number, if the number is 26 it returns a space
 ************************************************/
char getChar(int num){
	if(num == 26) return ' ';
	else return 65 + num;
}

/*************************************************
 *Function: getInt
 *
 *Description: returns the corresponding integer of a
 * given character, if the character is a space it returns 26
 ************************************************/
int getInt(char charIn){
	if(charIn == ' ') return 26;
	return (int)charIn - 65;
}
