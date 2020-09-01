#include <stdio.h>
#include <stdlib.h>


void printArray(int* array, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void swap(int* a, int* b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}



void bubbleSort(int* array, int n)
{
	int sorted = 0;

	while (sorted == 0) {
		sorted = 1;
		for (int i = 1; i < n; i++) {
			if (array[i - 1] > array[i]) {
				swap(array + i - 1, array + i);
				sorted = 0;
			}
		}
	}
}


int main()
{	int n;
	printf("Enter number of elements in the array:\n");
	scanf("%d", &n);

	if (n < 1) {
		printf("Wrong input\n");
		return -1;
	}

	int* array = (int*)malloc(sizeof(int) * n); // allocate memory for the array

	printf("Enter the array:\n");
	for (int i = 0; i < n; i++)  {
		scanf("%d", array + i);
	}

	bubbleSort(array, n);

	printf("Sorted array:\n");
	printArray(array, n);

	free(array);
	return 0;
}


