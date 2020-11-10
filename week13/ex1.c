#include <stdio.h>
#include <stdlib.h>


void input_array(FILE* file, int* array, int len)
{
	for (int i = 0; i < len; i++) {
		fscanf(file, "%d", array + i);
	}
}

void input_matrix(FILE* file, int** matrix, int row, int col)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(file, "%d", matrix[i] + j);
		}
	}

}

int less(int* array1, int* array2, int len)
{
	for (int i = 0; i < len; i++) {
		if (array1[i] > array2[i]) 
			return 0;
	}

	return 1;
}

void add_array(int* array1, int* array2, int len) 
{
	for (int i = 0; i < len; i++) {
		array1[i] += array2[i];
	}
}

void subtract_array(int* array1, int* array2, int len) 
{
	for (int i = 0; i < len; i++) {
		array1[i] -= array2[i];
	}
}

int* bankers_algorithm(int m, int n, int* E, int* A, int** C, int** R)
{
	int* finished = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		finished[i] = 0;
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if ((finished[i] == 0) && (less(R[i], A, m) == 1)) {
				add_array(A, C[i], m);
				subtract_array(A, R[i], m);
				finished[i] = 1;
			}

		}
	}

	return finished;
}

int main()
{
	FILE* input = fopen("ex1.txt", "r");

	int m; // number of resource classes
	int n; // number of processes

	fscanf(input, "%d", &m);
	fscanf(input, "%d", &n);

	int* E = (int*)malloc(sizeof(int) * m); // total number of resources of each class
	int* A = (int*)malloc(sizeof(int) * m); // number of resources of each class available now

	// input E vector
	input_array(input, E, m);

	// input A vector
	input_array(input, A, m);

	int** C = (int**)malloc(sizeof(int*) * n); // allocation matrix
	int** R = (int**)malloc(sizeof(int*) * n); // request matrix

	for (int i = 0; i < n; i++) {
		C[i] = (int*)malloc(sizeof(int) * m);
		R[i] = (int*)malloc(sizeof(int) * m);
	}

	// input C
	input_matrix(input, C, n, m);

	// input R
	input_matrix(input, R, n, m);


	int* finished = bankers_algorithm(m, n, E, A, C, R);

	FILE* output = fopen("output.txt", "w");
	
	int all_finished = 1;
	for (int i = 0; i < n; i++) {
		if (finished[i] == 0) {
			all_finished = 0;
			fprintf(output, "%d-th process deadlocked\n", i);
			break;
		}
	}

	if (all_finished == 1) {
		fprintf(output, "No deadlock is detected\n");
	}


	free(E);
	free(A);

	for (int i = 0; i < n; i++) {
		free(C[i]);
		free(R[i]);
	}

	free(C);
	free(R);

	fclose(input);

	return 0;
}