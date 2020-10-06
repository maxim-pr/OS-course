#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
	void** arr = malloc(sizeof(void*) * 10);

	for (int i = 0; i < 10; i++) {
		arr[i] = malloc(10 * 1024 * 1024);
		memset(arr[i], '0', 10 * 1024 * 1024);
		sleep(1);
	}

	
	for (int i = 0; i < 10; i++)
		free(arr[i]);
	free(arr);
	return 0;
}