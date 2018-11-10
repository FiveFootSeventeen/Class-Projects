/****************************************************
 *Author: Jacob Leno
 *Date: 06/09/18
 *Program: otp_enc
 *Description: otp_enc is given a plaintext file as its first argument
 * and a key file as it second argument. Its third argument is
 * the port at which to connect to otp_enc_d. otp_enc will
 * send these two files to otp_enc_d and wait to receive back
 * the encrypted file when it does it will send it to stdout
 ***************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include <errno.h>

ssize_t writen(int fd, const void *buffer, size_t n);
ssize_t readn(int fd, void *buffer, size_t n);
int checkBadChar(char *buffer, size_t length);

int main(int argc, char *argv[])
{	
	const int DA_BUFFER_SIZE = 1;
	int socketFD, portNumber, charsRead, charsWritten = -5;
	int continueRead = 1, bufferLen, msgLen, processType;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[50], *ptBuffer, *keyBuffer, *encBuffer;

	ptBuffer = malloc(DA_BUFFER_SIZE * sizeof(char)); //Alloc at least one byte so that strlen doesnt segfault
    	keyBuffer = malloc(DA_BUFFER_SIZE * sizeof(char));
	memset(ptBuffer, '\0', DA_BUFFER_SIZE); //Set the byte to the null terminator
	memset(keyBuffer, '\0', DA_BUFFER_SIZE);

	if (argc < 4) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(1); } // Check usage & args
	FILE *ptFile = fopen(argv[1], "r"); //Open up the plaintext file for reading
		if(ptFile == NULL) { fprintf(stderr, "failed to open file in argv[1]\n"); exit(1); }
	FILE *keyFile = fopen(argv[2], "r"); //Open up the key file for reading
		if(keyFile == NULL) { fprintf(stderr, "failed to open file in argv[2]\n"); exit(1); }

	while(continueRead){
		memset(buffer, '\0', sizeof(buffer));
		if( fgets(buffer, sizeof(buffer), ptFile) != NULL) bufferLen = strlen(buffer); //Get info in the plaintext file and read it into the buffer
		if(buffer[sizeof(buffer) - 2] == '\0') { //If we see a null terminator at the second to last character then there are no more characters to read
			continueRead = 0; 
		} else { 
			continueRead = 1;
		}
		ptBuffer = realloc(ptBuffer, strlen(ptBuffer) + bufferLen + 1); //Reallocate memory for the buffer
		strcat(ptBuffer, buffer); //Concatenate the buffer onto the end of keyBuffer
	}
	ptBuffer[strlen(ptBuffer) - 1] = '\0'; //Remove the newline

	continueRead = 1;
	while(continueRead){
		memset(buffer, '\0', sizeof(buffer));
		if( fgets(buffer, sizeof(buffer), keyFile) != NULL) bufferLen = strlen(buffer); //Get info in the key file and read it into the buffer
		if(buffer[sizeof(buffer) - 2] == '\0') { //If we see a null terminator at the second to last character then there are no more characters to read
			continueRead = 0; 
		} else { 
			continueRead = 1;
		}
		keyBuffer = realloc(keyBuffer, strlen(keyBuffer) + bufferLen + 1); //Reallocate memory for the buffer
		strcat(keyBuffer, buffer); //Concatenate the buffer onto the end of keyBuffer
	}
	keyBuffer[strlen(keyBuffer) - 1] = '\0'; //Remove the newline

	if(strlen(ptBuffer) > strlen(keyBuffer)) { fprintf(stderr, "Key file cannot be shorter than plaintext file!\n"); exit(1); }
	if(checkBadChar(ptBuffer, (size_t)strlen(ptBuffer))) { fprintf(stderr, "Plaintext file contains charcters other than A-Z or space!\n"); exit(1); }
	if(checkBadChar(keyBuffer, (size_t)strlen(keyBuffer))) { fprintf(stderr, "Key file contains charcters other than A-Z or space!\n"); exit(1); }

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(1); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) { perror("CLIENT: ERROR opening socket"); exit(1); }
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){ // Connect socket to address
		perror("CLIENT: ERROR connecting");
		exit(1);
	}
	
	processType = 0;
	if(read(socketFD, &processType, sizeof(processType)) < 0 ){ //Read the length of the incoming message from the client
		fprintf(stderr, "Could not read length of incoming message\n");  //Make sure read() read more than 0 bytes
		exit(1);
	}
	if(ntohl(processType) != -20){ //Check to see if we have the correct process trying to connect
		fprintf(stderr, "Cannot use otp_dec_d unless connecting from otp_dec!\n");
		exit(2);
	}


	msgLen = htonl(strlen(ptBuffer));
	write(socketFD, &msgLen, sizeof(msgLen)); //Send the length of the upcoming message before transfering the message
	
	if(writen(socketFD, ptBuffer, strlen(ptBuffer)) != strlen(ptBuffer)){
		perror("CLIENT: ERROR writing to socket");
		exit(1);
	}

	msgLen = htonl(strlen(keyBuffer));
	write(socketFD, &msgLen, sizeof(msgLen)); //Send the length of the upcoming message before transfering the message
	
	if(writen(socketFD, keyBuffer, strlen(keyBuffer)) != strlen(keyBuffer)){
		perror("CLIENT: ERROR writing to socket");
		exit(1);
	}

	encBuffer = malloc(strlen(ptBuffer) * sizeof(char)); //Create space to store the encrypted message
	memset(encBuffer, '\0', strlen(ptBuffer)); 
	readn(socketFD, encBuffer, strlen(ptBuffer)); //Read the encrypted message into the buffer

	printf("%s\n", encBuffer); //Output the buffer to stdout with a newline
	
	free(encBuffer);
	free(keyBuffer);
	free(ptBuffer);
	close(socketFD); // Close the socket
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
 *Function: checkBadChar
 *
 *Description: This function will check through all the 
 * characters in a buffer and return 1 if it finds a
 * character that is not A-Z or space. If it does not
 * find any of these bad characters it will return 0
 *************************************************/

int checkBadChar(char *buffer, size_t length){
	int i;

	for(i = 0; i < length; i++){
		if((buffer[i] >  90 || buffer[i] < 65) && buffer[i] != 32){ //If a bad character is found return 1
			return 1;
		}
	}
	return 0;
}
