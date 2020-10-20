#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main()
{
	DIR* dir = opendir("temp");

	struct dirent* current_file;
	current_file = readdir(dir);

	FILE* outputfile;

	while (current_file != NULL) {
		int current_file_inode_number = current_file->d_ino;


  		char current_file_inode_number_s[100];
  		sprintf(current_file_inode_number_s, "%d", current_file_inode_number);


		char command1[100];
		strcpy(command1, "find ~ -inum ");
		strcat(command1, current_file_inode_number_s); 

		char command2[100];
		strcpy(command2, command1);
			
		strcat(command1, " | wc -l");

		outputfile = popen(command1, "r");

		char result_string[200];
		fscanf(outputfile, "%s", result_string);

		int nlink = *result_string - 48;

		if (nlink >= 2) {
			printf("Current file: %s\n", current_file->d_name);
			printf("Numer of links: %d\n", nlink);
			printf("Links:\n");

			outputfile = popen(command2, "r");


			char c = fgetc(outputfile); 
    		while (c != EOF) 
    		{ 
        		printf ("%c", c); 
        		c = fgetc(outputfile); 
    		} 
  
			printf("\n");

		}


		current_file = readdir(dir);
	}
	
	fclose(outputfile);
	closedir(dir);
	return 0;
}