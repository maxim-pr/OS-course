#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	printf("Enter N - number of elements in the array ");
	scanf("%d", &n);

	if (n < 1) {
		printf("Wrong input\n");
		return -1;
	}

	int* arr = (int*)malloc(sizeof(int) * n);  // array declaration

	// array initialization
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	// print the array
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	// free memory
	free(arr);

	return 0;
}