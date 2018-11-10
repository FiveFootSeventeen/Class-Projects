/************************************************
 * Author: Jacob Leno
 * Date: 05/28/18
 * Program: smallsh
 * Description: A small shell program 
 **********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

void processInput();
int exitShell(pid_t *);
void changeDirectory(char *);
void statusOut();
void executeCommand(char *);
pid_t executeBackCommand(char **, int);
void catchSIGTSTP(int);
void reportChildTerminated(int, int);
void catchSIGCHLD(int);

int exitStatus = -5, signalTerm = 0, signalNum, sigtstpSignal = 0;

int main(int argc, char * argv[]){
	struct sigaction SIGTSTP_action = {0}, ignore_action = {0}, SIGCHLD_action;

	SIGTSTP_action.sa_handler = catchSIGTSTP;
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = SA_RESTART;
	
	SIGCHLD_action.sa_handler = catchSIGCHLD;
	sigemptyset(&SIGCHLD_action.sa_mask);
	SIGCHLD_action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	
	ignore_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ignore_action, NULL); 
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);
	sigaction(SIGCHLD, &SIGCHLD_action, NULL);

	processInput();	

	return 0;
}
/*************************************************
 *function: catchSIGCHLD
 *description: handler of the SIGCHILD signal
 *************************************************/

void catchSIGCHLD(int signo){
	int childExitMethod, signalNo;
	int childPID = waitpid(-1, &childExitMethod, WNOHANG); //get the pid of the terminated child
	if(WIFEXITED(childExitMethod) != 0) return;
	else {
		signalNo = WTERMSIG(childExitMethod); //Get the signal number that terminated the child
		if(childPID > -1) reportChildTerminated(childPID, signalNo);
	}
}
/*************************************************
 *function: reportChildTerminated
 *description: outputs information about a child terminated by a signal
 *************************************************/

void reportChildTerminated(int chldPid, int signalNo){
	printf("background pid %d is done: terminated by signal %d\n", chldPid, signalNo);
	fflush(stdout);
}
/*************************************************
 *function: catchSIGTSTP
 *description: handler of the SIGTSTP signal
 *************************************************/

void catchSIGTSTP(int signo){
	if(sigtstpSignal == 0){ //If the foreground-only mode hasn't been engaged then engage it
		char *message = "\nEntering foreground-only mode (& is now ignored)\n: ";
		write(STDOUT_FILENO, message, 52); 
		sigtstpSignal = 1 - sigtstpSignal;
	} else { //If foreground-only mode has already been engaged then disengage it
		char *exitmessage = "\nExiting foreground-only mode\n: ";
		write(STDOUT_FILENO, exitmessage, 32);
		sigtstpSignal = 1 - sigtstpSignal;		
	}
}
/*************************************************
 *function: processInput
 *description: processes user input and calls appropriate functions
 *************************************************/

void processInput(){
	char *tokStr, *token, *directory, *lineEntered = NULL;
	static char *backArr[100][512];
	int numCharsEntered, childExitMethod, moreInput = 1, backCmdNum = 0;
	pid_t backCmdPids[100];
	pid_t childPID, exitStatusBack;
	size_t bufferSize = 0;
	//Counters
	int i, j, k;
	//Booleans
	int  backgroundCommand = 0;

	for(i = 0; i < 100; i++){
		backCmdPids[i] = -5;
	}

	while(moreInput){
		j = 0;
		//Check to see if background child processes have completed
		for(i = 0; i < 100; i++){
			if(backCmdPids[i] > 0){ // Check only valid pids
				childPID = waitpid(backCmdPids[i], &childExitMethod, WNOHANG); //Check to see if a specific background has exited, dont wait if its hasn't
				if(childPID > 0){
					if(WIFEXITED(childExitMethod)){ //Check if the process terminated normally
						exitStatusBack = WEXITSTATUS(childExitMethod); //Get the process's exit status
						exitStatus = exitStatusBack; //Set the global exit status to the last background child process
						printf("background pid %d is done: exit value %d\n", childPID, exitStatusBack);
						fflush(stdout);
						backCmdPids[i] = -5; //Set the value of backCmdPids[i] back to a negative so it isnt checked
						k = 0;
						while(backArr[i][k] != NULL){ //Free DA memory allocated to the background processes
							free(backArr[i][k]);
							k++;	
						}
					}
				}
			}
		}
		printf(": "); //Output the prompt and flush stdout
		fflush(stdout);
		numCharsEntered = getline(&lineEntered, &bufferSize, stdin); //Get input from the user
		lineEntered[numCharsEntered - 1] = '\0'; //Remove the newline
		if(numCharsEntered > 1) { //Only process input if the user did not enter a blank line
			if(strstr(lineEntered, "&") != NULL && ((strstr(lineEntered, "&") - lineEntered + 2) ==  numCharsEntered)) {
				backgroundCommand = 1;
			}
			tokStr = lineEntered; //Assign the tokStr pointer to the user input so lineEntered can be deallocated later
			token = strtok(tokStr, " "); //Get the first space seperated input

			if(token[0] ==  '#') {printf("\n"); fflush(stdout);} //The user entered a comment skip the line
			else if(strcmp(token, "exit") == 0) {
				for(i = 0; i < 100; i++){	
					while(backArr[i][k] != NULL){ //Free DA memory allocated to the background processes
						free(backArr[i][k]);
						k++;	
					}
				}
				exitShell(backCmdPids); //If the user has entered the exit command call the exit function
			} else if(strcmp(token, "status") == 0) statusOut(exitStatus, signalTerm, signalNum);
			else if(strcmp(token, "cd") == 0){
				directory = strtok(NULL, " ");
				changeDirectory(directory);
			} else if (backgroundCommand && !sigtstpSignal){
				i = 0;
				while(token != NULL){
					backArr[backCmdNum][i] = malloc(50 * sizeof(char));
					strcpy(backArr[backCmdNum][i], token);
					token = strtok(NULL, " ");
					i++;
				}
				backArr[backCmdNum][i] = NULL;
				backCmdPids[backCmdNum] = executeBackCommand(backArr[backCmdNum], backCmdNum); //Execute the backCommand function and store its return child pid in the backCmdPids array
				backCmdNum++;
				backgroundCommand = 0;
				if(backCmdNum >= 100) backCmdNum = 0;
			} else { executeCommand(token); }
		}
		free(lineEntered);
		lineEntered = NULL;
		bufferSize = 0;
	}
}
/**********************************
 *function: executeCommand
 *description: Executes the commands contained in firstStr
 **********************************/
void executeCommand(char *firstStr){
	char *argsArr[512], *redirectSymbol = NULL, *destination = NULL, readBuffer[50];
	char parentID[20];
	pid_t spawnPid = -5;
	int execRet, i, j, shellOpFound, openFD;
	int saved_stdout = dup(1), childExitMethod, childPID, foundOne;
	sprintf(parentID, "%d", getpid());

	do{
		i = 0;
		shellOpFound = 0;

		while(firstStr != NULL && i < 512 && !shellOpFound){
			argsArr[i] = firstStr;
			if(strcmp(argsArr[i], "$$") == 0) argsArr[i] = parentID; //If $$ is found in the string convert it to the parent process's id number
			firstStr = strtok(NULL, " ");
			if(strcmp(argsArr[i], "&") == 0 && firstStr == NULL) argsArr[i] = NULL; //If & is found in the string make it NULL
			if(firstStr != NULL){	
				if(strcmp(firstStr, ">") == 0 || strcmp(firstStr, "<") == 0){ //If a shell operator is found make a note of it set appropriate variables
					shellOpFound = 1;
					foundOne = 1;
					redirectSymbol = firstStr;
					destination = strtok(NULL, " ");
					firstStr = destination;
				}
			}
			i++;
		}
		argsArr[i] = NULL;

		if(foundOne && !shellOpFound){
			firstStr = NULL;
		} else { 
			spawnPid = fork();	
			switch(spawnPid){
				case -1:{ perror("fork failed!\n"); exit(1); break; }
				case 0:{
					signal(SIGINT, SIG_DFL); //Set the action of the SIGINT signal in the child process to the default action
					signal(SIGTSTP, SIG_IGN); //Set the action of the SIGTSTS signal to be ignored in the child process
					execRet = 0;
					if(shellOpFound){
						if(strcmp(redirectSymbol, ">") == 0){ //Need to read out here, stdout open a different file for writing to
							openFD = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
							if(openFD == -1) {
								printf("cannot open %s for output\n", destination); exitStatus = 1;
								fflush(stdout);
								signalTerm = 0;
								exit(1);
							}
							dup2(openFD, 1);
							execRet = execvp(*argsArr, argsArr);
						}  else if (strcmp(redirectSymbol, "<") == 0){ //Need to read in here
							openFD = open(destination, O_RDONLY);	
							if(openFD == -1) { 
								printf("cannot open %s for input\n", destination); 
								fflush(stdout);
								exitStatus = 1;
								signalTerm = 0;
								exit(1);
							}
							dup2(openFD, 0);	
							execRet = execvp(*argsArr, argsArr);
						}
					} else {
						execRet = execvp(*argsArr, argsArr); //No redirect call execvp on the argument string
					}
					if(execRet == -1) { 
						exitStatus = 1; 
						signalTerm = 0; 
						printf("%s: no such file or directory\n", argsArr[0]);
						fflush(stdout);
						exit(1); 
					}
					exit(0);
					break;
				}
				default:{
					shellOpFound = 0; 
					break;
				}
			}
		}

		
	} while(firstStr != NULL);


	waitpid(spawnPid, &childExitMethod, 0);
	if(WIFEXITED(childExitMethod)){
		exitStatus = WEXITSTATUS(childExitMethod);
		signalTerm = 0;
	} else {
		signalNum = WTERMSIG(childExitMethod);
		printf("terminated by signal %d\n", signalNum);
		signalTerm = 1;
	}
	

}
/*************************************************
 *function: executeBackCommand
 *description: Executes a command in the background and allows the shell to continue
 * taking commands
 *************************************************/
pid_t executeBackCommand(char **userArr, int cmdNum){
	char *argsArr[512], *firstStr, redirectSymbol[5], *destination, readBuffer[50];
	pid_t spawnPid = -5;
	int execRet, childExitMethod, i, j, shellOpFound, openFD;
	int saved_stdout = dup(1), childProcesses = 0, childPID, foundOne, devNullOut, devNullIn;
	j = 0;	
	do{
		shellOpFound = 0;
		i = 0;
		while(userArr[j] != NULL && i < 512 && !shellOpFound){
			argsArr[i] = userArr[j];
			if(userArr[j] != NULL){	
				if(strcmp(userArr[j], ">") == 0 || strcmp(userArr[j], "<") == 0 || strcmp(userArr[j], "&") == 0){ //If a shell operator is found make a note of it set appropriate variables
					if(strcmp(userArr[j], "&") == 0){ //If a "&" was found ignore it
						argsArr[i] = NULL;
					} else {
						shellOpFound = 1;
						foundOne = 1;
						strcpy(redirectSymbol, userArr[j]);
						j++;
						destination = userArr[j];
					}
				}
			}
			j++;
			i++;
		}
		argsArr[i] = NULL;


		if(foundOne && !shellOpFound){
			firstStr = NULL;
		} else { 
			childProcesses++;
			spawnPid = fork();	

			switch(spawnPid){
				case -1:{ perror("fork failed!\n"); exit(1); break; }
				case 0:{
					execRet = 0;
					signal(SIGTSTP, SIG_IGN); //Set the action of the SIGTSTS signal to be ignored in the child process
					if(shellOpFound){
						if(strcmp(redirectSymbol, ">") == 0){ //Need to read out here, stdout open a different file for writing to
							openFD = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
							if(openFD ==  -1) {
								printf("cannot open %s for output\n", destination); 
								fflush(stdout);
								exit(1);
							}
							dup2(openFD, 1);
							execRet = execvp(*argsArr, argsArr);
						}  else if (strcmp(redirectSymbol, "<") == 0){ //Need to read in here
							openFD = open(destination, O_RDONLY);	
							if(openFD == -1) { 
								printf("cannot open %s for input\n", destination); 
								fflush(stdout);
								exit(1);
							}
							dup2(openFD, 0);	
							execRet = execvp(*argsArr, argsArr);
						}
					} else {
						devNullIn = open("/dev/null", O_RDONLY); //Redirect all input to /dev/null
						dup2(devNullIn, 0);
						devNullOut = open("/dev/null", O_RDWR); //Redirect all output to /dev/null
						dup2(devNullOut, 1);
						execRet = execvp(*argsArr, argsArr);
					}
					if(execRet == -1) { 
						printf("%s: no such file or directory\n", argsArr[0]);
						fflush(stdout);
						exit(1); 
					}
					exit(0);
					break;
				}
				default:{
					shellOpFound = 0; 
					break;
				}
			}
		}

	} while(firstStr != NULL);

	printf("background pid is %d\n", spawnPid);	
	fflush(stdout);
	return spawnPid;
}
/*************************************************
 *function: exitShell
 *description: Exits the shell and kills off all processes
 *************************************************/
int exitShell(pid_t backPidArray[]){
	int i;
	for(i = 0; i < 100; i++){
		if(backPidArray[i] > 0) kill(backPidArray[i], SIGKILL); //Kill off all currently running background processes
	}
	exit(0);
}
/*************************************************
 *function: changeDirectory
 *description: Changes the current working directory to the user specified directory
 *************************************************/

void changeDirectory(char *directory){
	char *lastChar, *currentDir, *newDir;
	int returnVal = 0;

	if(directory == NULL){ // user has requested the home directory
		returnVal = chdir(getenv("HOME"));	
	} else { 
		currentDir = getcwd(NULL, 0);

		if(strstr("/", directory) == NULL){ //User has entered a relative path 
			if(strcmp(directory, "..") == 0){ //The user desired to move up one level
				lastChar = strrchr(currentDir, '/'); //Get the last occurance of the / character in the directory
				*lastChar = '\0'; //Set that character to eof character
				returnVal = chdir(currentDir); //Set the directory to a new value that is one level higher than it was previously
			} else {
				newDir = malloc(strlen(currentDir) + strlen(directory) + 2); //Allocate enough memory to hold the name of the path, the directory desired, the / character and the null terminator
				strcpy(newDir, currentDir);
				strcat(newDir, "/");
				strcat(newDir, directory);
				returnVal = chdir(newDir);
				free(newDir);
				newDir = NULL;
			}			
		} else { //User has entered an absolute path
				returnVal = chdir(directory);	
		}
	}
	if(returnVal == 0){	
		exitStatus = 0;
		signalTerm = 0;
	} else {
		exitStatus = 1;
		signalTerm = 0;
	}
}
/*************************************************
 *function: statusOut
 *description: outputs the exit status of the last process
 *************************************************/

void statusOut(){
	if(exitStatus >= 0 && signalTerm == 0){
		printf("exit value %d\n", exitStatus);
		fflush(stdout);
	} else if (signalTerm) {
		printf("terminated by signal %d\n", signalNum);
		fflush(stdout);
	}
}
