
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
/* Prototype */
void createChildAndRead (int);

/* -------------------------------------------------------------
Function: main
Arguments: 
	int ac	- number of command arguments
	char **av - array of pointers to command arguments
Description:
	Extract the number of processes to be created from the
	Command line. If an error occurs, the process ends.
	Call createChildAndRead to create a child, and read
	the child's data.
-------------------------------------------------- ----------- */

int main (int ac, char **av)
{
 int processNumber; 

 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &processNumber)== 1)
 {
    createChildAndRead(processNumber);
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments: 
	int prcNum - the process number
Description:
	Create the child, passing prcNum-1 to it. Use prcNum
	as the identifier of this process. Also, read the
	messages from the reading end of the pipe and sends it to 
	the standard output (df 1). Finish when no data can
	be read from the pipe.
-------------------------------------------------- ----------- */

void createChildAndRead(int prcNum) {
	int length;
	char val[256];

	if (prcNum == 1) { // verifying that prcNum is equal to 1 then printing the output
	
		length = sprintf(val, " Process %d begins\n", prcNum);

		write(STDOUT_FILENO, val, length); // used STDOUT_FILENO since we have an integer due to the ineger conversion
		//incompatibility error

		sleep(5); // we make it do the sleep call for 5 seconds and then outputs process terminates
		length = sprintf(val, " Process %d terminates\n", prcNum); //process terminates

		write(STDOUT_FILENO, val, length);
	}
	else {
		length = sprintf(val, "Process %d begins\n", prcNum); // here the else begins where the process begins again

		write(STDOUT_FILENO, val, length); // used STDOUT_FILENO since we have an integer due to the ineger conversion
		//incompatibility error

		int pipe_value[2]; // we create the pipe and set it

		if (pipe(pipe_value) == -1) {
			fprintf(stderr, "Failed to create pipes\n"); // failed to print the message
			exit(EXIT_FAILURE); // this will be the unsuccessful execution
		}

		if (fork() == 0) {   // we set the fork to 0 
			close(pipe_value[0]); // closing the pipe value and setting it to 0 
			dup2(pipe_value[1], STDOUT_FILENO); // this is used to create a copy of existing file
			char numberoofArguments[20];
			sprintf(numberoofArguments, "%d", prcNum - 1);
			char* arg[] = {"cpr", numberoofArguments, NULL};
			// this causes the current program to be aborted by the current process
			//and will start program execution in the file path
			execv("cpr", arg);
		}

		close(pipe_value[1]); // will close the writing in the file
		// this is a contant declared in stdio.h in the beginning of the code
		
		char dash[BUFSIZ];
		int reading; // integer to create the reading

		//the reading is happening here 
		while ((reading = read(pipe_value[0], dash, BUFSIZ)) > 0) {
			// this will print all data
			write(STDOUT_FILENO, dash, reading);
		}

		close(pipe_value[0]);
		// this will make the program sleep for 10 seconds and analyze the zombie behaviour
		// after that, we close the pipe
		sleep(10);

		length = sprintf(val, "Process %d terminates\n", prcNum);
		write(STDOUT_FILENO, val, length);
		
	}

}



