#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

int main()
{
	struct rusage usage;

	void** arr = malloc(sizeof(void*) * 10);

	for (int i = 0; i < 10; i++) {

		arr[i] = malloc(10 * 1024 * 1024);
		memset(arr[i], '0', 10 * 1024 * 1024);

		getrusage(RUSAGE_SELF, &usage);
		printf("%f Mb\n", usage.ru_maxrss / 1024.0);
		sleep(1);
	}

	
	for (int i = 0; i < 10; i++)
		free(arr[i]);
	free(arr);
	return 0;
}