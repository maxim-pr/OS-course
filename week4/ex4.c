#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Enter bash commands:\n");
	printf("(to stop use command 'exit')\n");
	while(1){
	char* buff; // the string of the command
    	size_t buffSize = 100;
    	size_t length;
    	buff = (char*)malloc(buffSize * sizeof(char));

    	length = getline(&buff, &buffSize, stdin);

	int ncommands = 0;
	for (int i = 0; i < length; i++) {
		if (buff[i] == ' ' || buff[i] == '\n')
			ncommands++;
	}

	// if the command is 'exit' then stop the execution
	if (buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't')
		break;

	// now we need to split this command (a string) into array of strings
    	char** args;
    	args = (char**)malloc((ncommands + 1) * sizeof(char*));

	for (int i = 0; i < ncommands; i++) {
		args[i] = (char*)malloc(length * sizeof(char));
    	}
	args[ncommands] = NULL;

	// fill in the array of pointers to chars 'args'
	int argIndex = 0;
	int charIndex = 0;

	for (int i = 0; i < length; i++) {
		if (buff[i] == ' ' || buff[i] == '\n') {
			args[argIndex][charIndex] = 0;
			argIndex++;
			charIndex = 0;
		}
		else {
			args[argIndex][charIndex] = buff[i];
			charIndex++;
		}
	}

	// create a process, and execute in this child process the bash command
	int id = fork();
	if (id == 0)
	    	execvp(args[0],args);
	}

	return 0;
}
