#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Round-Robin scheduling Algorithm


int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// sorts the two-dimensional array with 3 columns by the 1st column 
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
	int quantum;

	// input n
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

	printf("Enter quantum: ");
	scanf("%d", &quantum);
	printf("\n");


	// sort the array relative to arrival time
	sort(n, processes);



	int** result; // two-dimensional array to store CT, TAT, WT for each process
	
	// allocate memory for result
	result = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		result[i] = (int*)malloc(3 * sizeof(int));
	}



	


	// array for storing time left untill the end of the execution
	int* remain_time;
	remain_time = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		remain_time[processes[i][0]] = processes[i][2];
	}


	// array for storing boolean indicators whether the process is executed completely
	int* finished;
	finished = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		finished[i] = 0;
	}


	// simulate the execution (Round-robin)
	int current_time = processes[0][1];
	int total_time = processes[0][1];  // time instance when all processes are executed
	for (int i = 0; i < n; i++) {
		total_time += processes[i][2];
	}

	// while current variable is less than final time instance - iterate
	while(current_time < total_time){
				

		for (int i = 0; i < n; i++) {

			int process_index = processes[i][0];

			if (remain_time[process_index] > 0) {
				int t = min(quantum, remain_time[process_index]);

				current_time += t;
				remain_time[process_index] -= t;
			}
			
			if (remain_time[process_index] == 0 && finished[process_index] == 0){		
				result[process_index][0] = current_time;
				finished[process_index] = 1;
			}
		}

	}
	

	
	// in previous loop only CT was computed
	// having AT and CT other components TAT and WT are computed:
	for (int i = 0; i < n; i++) {
		int process_index = processes[i][0];
		int at = processes[i][1];
		int ct = result[process_index][0];
		int bt = processes[i][2];
		int tat = ct - at;
		int wt = tat - bt;

		result[process_index][1] = tat;
		result[process_index][2] = wt;

	}

	//print the result array (CT, TAT, WT for each process)
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