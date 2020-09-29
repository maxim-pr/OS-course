#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}


// as I don't know how to find exact number of bytes that was allocated
// with the given pointer, this function has the 'current_size' as an argument 
int* realloc_int(int* ptr, size_t current_size, size_t new_size)
{

	if (new_size == 0) {
		free(ptr);
		return NULL;
	}

	int* new_ptr = (int*)malloc(new_size);

	if (ptr != NULL) {

		int nelements_to_copy = min(current_size, new_size) / sizeof(int);

		for (int i = 0; i < nelements_to_copy; i++) {
			new_ptr[i] = ptr[i];
		}

	}

	return new_ptr;
}


int main()
{
	srand(time(NULL)); 

	int n1;
	printf("Enter N1 - numer of elements in the array: ");
	scanf("%d", &n1);

	int* p = (int*)malloc(sizeof(int) * n1);

	printf("Randomly generated matrix of N1 integers:\n");
	for (int i = 0; i < n1; i++) {
		p[i] = rand() % 100;
		printf("%d ", p[i]);
	}
	printf("\n");


	int n2;
	printf("Enter N2 - new size to reallocate this array: ");
	scanf("%d", &n2);


	p = realloc_int(p, sizeof(int) * n1, sizeof(int) * n2);
	
	printf("Reallocated array:\n");
	for (int i = 0; i < n2; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");

	free(p);
	return 0;
}