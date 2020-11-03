#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char const* argv[])
{
	FILE* input = stdin;

	if (argc == 1) {
		printf("No arguments provided\n");
		return 1;
	}

	int nfiles = 0;
	int append = 0;  // bool variable to indicate whether to append or rewrite files

	// compute number of files provided
	for (int i = 1; i < argc; i++) {
		if (strcmp("-a", argv[i]) == 0)
			append = 1;
		else
			nfiles++;
	}

	if (nfiles == 0) {
		printf("No files provided");
		return 1;
	}


	FILE** files;
	if (append)
		files = (FILE**)malloc(sizeof(FILE*) * (argc - 2));
	else
		files = (FILE**)malloc(sizeof(FILE*) * (argc - 1));

	// open files with given names
	int k = 0;
	if (append) {
		for (int i = 1; i < argc; i++) {
			if (strcmp("-a", argv[i]) != 0) {
				files[k] = fopen(argv[i], "a");
				k++;
			}
		}
	} 
	else {
		for (int i = 1; i < argc; i++) {
			if (strcmp("-a", argv[i]) != 0) {
				files[k] = fopen(argv[i], "w");
				k++;
			}
		}
	}



	char curr = fgetc(input);  // current symbol

	// read input character by character and write to the output files
	while (curr != EOF) {
		for (int i = 0; i < nfiles; i++) {
			fprintf(files[i], "%c", curr);
		}
		curr = fgetc(input);
	}
	

	for (int i = 0; i < nfiles; i++) {
		fclose(files[i]);
	}
	fclose(input);
	return 0;
}