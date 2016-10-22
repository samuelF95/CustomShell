
#include <stdio.h>
#include <stdlib.h>                                                                           
#include <unistd.h>                                                                         
#include <string.h>                                                                         
#include <sys/types.h>                                                                     
#include <signal.h>                                                                            
#include <sys/wait.h>                                                                       
#include <fcntl.h>                                                                         
#include <termios.h> 
#include <time.h> 
#include <limits.h> 
#include <grp.h>    
              

// ****** Data Structures & File Descriptors ******                                
#define TRUE 1
#define STDIN 1
#define BUFFER_MAX_LENGTH 50            // The max chatacters for the buffer length
static char* currentDirectory;          // The buffer for the working directory
static char userInput = '\0';
static char buffer[BUFFER_MAX_LENGTH];  // The buffer for user input
static int bufferChars = 0;
static char *commandArgv[5];            // Holds the array of strings for given command
static int cmdArgCount = 0;             // word count for the given commands


// ****** User Input Functions ******
// gets line from the user
void getText();

// populates the getline into teh array of string (commadnArgv) 
void popCommand();

// clears the buffer and commandArgv
void clearCommand();

// ****** Error checks and Prompt ******
// Display the welcome screen
void welcomeScreen();

// Display the custom shell
void custShellPrompt();

// ****** Custom Shell Functions ******
// Determines if the command is built in or not 
void handleUserCommand();

// Checks if command is builtin 
int checkBuiltInCommands();
                                                                                                                        
// executes a command 
void executeCommand(char *command[], char *file, int newDescriptor);

// Create the child process
void launchJob(char *command[], char *file, int newDescriptor);

// Retrieve the date (internal command) 
void Date();

// Retrieve the user details (internal command)
void userDets();

// pwd command (external commmand)
void pwd();

// ifconfig (external command)
void ifconfig();

// help (internal command)
void help();

//clear the screen
void clearScreen();


// ****** User Input Functions ******

//Read a line of text from the user
void getText(){
        clearCommand();                                                                       
        while ((userInput != '\n') && (bufferChars < BUFFER_MAX_LENGTH)) {
                buffer[bufferChars++] = userInput;
                userInput = getchar();
        }
        buffer[bufferChars] = 0x00;                                                            
        popCommand();
}

// space is utilised as a seperator and it populates the array commandArgv
void popCommand(){
        char* bufferPointer;                                // variable pointing to the buffer
        bufferPointer = strtok(buffer, " ");
        while (bufferPointer != NULL) { 
                commandArgv[cmdArgCount] = bufferPointer;   // populate commandArgv array
                bufferPointer = strtok(NULL, " ");
                cmdArgCount++;
        }
}

//	clears the arrays of chars, allowing the user to input the next command
void clearCommand(){
        while (cmdArgCount != 0) {
                commandArgv[cmdArgCount] = NULL;
                cmdArgCount--;                              // decrement the number of words in the command line
        }
        bufferChars = 0;                                    // erase the chars in the buffer
}


//****** Error Checks and Prompts ******
// display the welcome screen

void welcomeScreen(){
		printf("\n");
        printf("\tWelcome to the Custom Shell,  %s\n", getenv("LOGNAME"));
//        printf("\tThe process ID is |  %d", (int) customshell_PID);
        printf("\n\n");
}

// Display the prompt for shell
void custShellPrompt(){
        printf("[CustomShell]");
}

// Checking to execute the built-in commands

void handleUserCommand(){
        if ((checkBuiltInCommands(commandArgv[0])) == 0) {
                printf("Error: Unknown command!\n\n");
        }
}

/**
 * List of the built-in commands: exit, cd, dt, ud, pw, ifc, help, h
 * the program will return 1 if the built-in is executed,
 * or else it will return 0
 */
int checkBuiltInCommands(){
        if (strcmp("exit", commandArgv[0]) == 0) {
		printf("You have now exited the Custom Shell\n\n");
                exit(EXIT_SUCCESS);
        }
	if (strcmp("dt", commandArgv[0]) == 0) {
	        Date();
	        return 1;
	}
	if (strcmp("ud", commandArgv[0]) == 0) {
		userDets();
		return 1;
	}
	if (strcmp("pw", commandArgv[0]) == 0) {
		pwd();
		return 1;
	}
	if (strcmp("ifc", commandArgv[0]) == 0) {
		ifconfig();
		return 1;
	}
	if (strcmp("help", commandArgv[0]) == 0) {
		help();
		return 1;
	}
	if (strcmp("clrscrn", commandArgv[0]) == 0) {
		clearScreen();
		return 1;
	}
        return 0;
}


 
// Displaying the internal date command
void Date() {
		printf("\n");
		
		time_t t;
		struct tm *tmp;
		char buf[64];
		time(&t);
		tmp = localtime(&t);
		strftime(buf, 64, "Time and Date:  %Y%m%d%H%M%S", tmp);
		printf("%s\n", buf);
		
		printf("\n");
}

//Printing out the user details in set order
void userDets(){
		printf("\n");
		
		struct group *gr;
		int ngroups, i;
		gid_t groups[NGROUPS_MAX];

		ngroups = NGROUPS_MAX;
		if ( getgrouplist( getlogin(), getegid(), groups, &ngroups) == -1) {
			printf ("Cannot contain anymore within the groups array: %d\n", ngroups);
		}
		
		printf("%d, %s," , geteuid(), getenv("LOGNAME"));
		for (i=0; i < ngroups; i++) {
			 gr = getgrgid(groups[i]);
			printf(" %s," ,  gr->gr_name);
		}
		printf(" %s", getcwd(getenv("HOME"), 1024));
		printf("\n");
		printf("\n");
}

// Print the working directory
void pwd() {
		printf("\n");
		system("pwd");
		printf("\n");
}

//Clear the screen
void clearScreen(){
		printf("\n");
		system("clear");
		printf("\n");
}

// Display hlep
void help() {
		
		if (commandArgv[1] != NULL ) {
			if(strcmp(commandArgv[1], "ifc") == 0){
				printf("\n");
				printf("ifc: used to configure a network interface, such as ethernet, wireless and modem etc. The setting for the first interface will be displayed.\n");
				printf("\n");
			}
			else if (strcmp(commandArgv[1], "pw" ) == 0){
				printf("\n");
				printf("pw | prints out the current working directory.\n");
				printf("\n");
			}
			else if (strcmp(commandArgv[1], "dt" ) == 0){
				printf("\n");
				printf("dt | date will be displayed in the format i.e. 20130926215222.\n");
				printf("\n");
			}
			else if (strcmp(commandArgv[1], "ud" ) == 0){
				printf("\n");
				printf("ud | user details will be displayed in the format | userID, groupID, username, groupname, iNode of users home directory.\n");
				printf("\n");
			}
			else if (strcmp(commandArgv[1], "exit" ) == 0){
				printf("\n");
				printf("exit | exit customshell.\n");
				printf("\n");
			}
			else {
				printf("\n");
				printf("%s | has no help implemented.\n", commandArgv[1]);
				printf("\n");

			}
		}
		else {
				if (commandArgv[1] == NULL) {
					printf("\n");
					printf("ud | prints out the userid, groupid, username and groupname.\n");
					printf("dt | prints out the current date i.e. 20130926215222.\n");
					printf("pw | prints out the current working directory.\n");
					printf("ifc | prints out the ifconfig of the eth0 by default. Own interface can be specified by user.\n");
					printf("exit | exit customshell.\n");
					printf("\n");
				}
			}
}

// Displays the  ifconfig

void ifconfig() {
	char command[100];
	if (commandArgv[1] == NULL) {
		printf("\n");
		system("ifconfig eth0");
		printf("\n");
	} else {
	    if (commandArgv[1] != NULL) {                                  
	       	printf("\n");
			sprintf(command, "ifconfig %s", commandArgv[1]);
			system(command);
			printf("\n");
	    }
	}
}




int main(int argc, char **argv, char **envp){
        welcomeScreen();
        custShellPrompt();                                                                            
        while (TRUE) {
                userInput = getchar();
                switch (userInput) {
                case '\n':                                                                               
                        custShellPrompt();                                                            
                        break;
                default:
                        getText();              // store user input in buffer
                        handleUserCommand();        // executes the command
                        custShellPrompt();                                                              
                        break;
                }
        }
        printf("\n");
        return 0;
}
