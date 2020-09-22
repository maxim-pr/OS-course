#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// First Come First Served scheduling algorithm


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// sorts the two-dimensional array with 3 columns relative to the 1st column 
void sort(int n, int** array)
{
	for (int i = 0; i < n; i++) {
		int curr_min = INT_MAX;
		int curr_min_index = -1;
		
		for (int j = i; j < n; j++) {
			if (array[j][1] < curr_min) {
				curr_min = array[j][1];
				curr_min_index = j;
			}
		}

		swap(array[i], array[curr_min_index]);
		swap(array[i] + 1, array[curr_min_index] + 1);
		swap(array[i] + 2, array[curr_min_index] + 2);
	}
}



int main()
{
	int n; // number of processes
	int** processes; // two-dimensional array of n triples: 
					 // [process_index, arrival_time, burst_time]

	printf("Enter number of processes: ");
	scanf("%d", &n);
	printf("\n");

	// allocate memory for the array
	processes = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		processes[i] = (int*)malloc(3 * sizeof(int));
	}

	// initialaize the array
	for (int i = 0; i < n; i++) {
		processes[i][0] = i;

		printf("Enter the arrival time of P%d: ", i);
		scanf("%d", processes[i] + 1);

		printf("Enter the burst time of P%d: ", i);
		scanf("%d", processes[i] + 2);
		printf("\n");
	}


	// sort the array relative to arrival time
	sort(n, processes);


	int** result; // two-dimensional array to store CT, TAT, WT for each process
	
	// allocate memory for result
	result = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		result[i] = (int*)malloc(3 * sizeof(int));
	}

	// simulate the execution (FCFS)
	int current_time = 0;
	for (int i = 0; i < n; i++) {
		if (current_time <= processes[i][1]) {
			current_time = processes[i][1];
		}

		current_time += processes[i][2]; // completion time of i-th process (in array)

		int proccess_index = processes[i][0];
		int ct = current_time;
		int tat = ct - processes[i][1];
		int wt = tat - processes[i][2];

		result[proccess_index][0] = ct;
		result[proccess_index][1] = tat;
		result[proccess_index][2] = wt;
	}


	// print the result array (CT, TAT, WT for each process)
	printf("\tCT\tTAT\tWT\n");
	for (int i = 0; i < n; i++) {
		printf("P%d:\t%d\t%d\t%d\n", i, result[i][0], result[i][1], result[i][2]);
	}

	double avg_tat = 0; // average Turn Around Time
	double avg_wt = 0;  // average Waiting Time

	for (int i = 0; i < n; i++) {
		avg_tat += result[i][1];
		avg_wt += result[i][2];
	}

	avg_tat /= n;
	avg_wt /= n;

	printf("Average TAT: %f\n", avg_tat);
	printf("Average WT: %f\n", avg_wt);

	// free memory
	for (int i = 0; i < n; i++) {
		free(processes[i]);
	}
	free(processes);

	for (int i = 0; i < n; i++) {
		free(result[i]);
	}
	free(result);

	return 0;
}