/* CSCI 401: Lab #4: Intro to Function Pointers
 * Programmer (Student ID): Ben Corriette (@02956064)
 * Last modified date: 11/18/2021
 * 
 * Summary: A program that reads from an input file and sorts its contents
 * according to its priority and arrival time field values and then
 * displays those values.
 * 
 * Reference: Quick Sort and Function Pointers Lab Handout
 */ 

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 0			//change this to 1 to enable verbose output

// Signature definition for funtion pointer
typedef int (*Comparer) (const void *a, const void *b);

// Compares two processes by priority and arrival time
int my_comparer(const void *this, const void *that)
{
	Process *process_1;
	Process *process_2;
	int process_1_arrival_time;
	int process_2_arrival_time;
	int process_1_priority;
	int process_2_priority;
	
	process_1 = (Process*) this;
	process_2 = (Process*) that;
	
	process_1_arrival_time = process_1->arrival_time;
	process_2_arrival_time = process_2->arrival_time;
	process_1_priority = process_1->priority;
	process_2_priority = process_2->priority;
	
	/* If two priorities are equal, arrival time should be
	 * considered as the second condition
	 */ 
	if (process_1_priority == process_2_priority) {
		return process_1_arrival_time - process_2_arrival_time;
	}
	return process_2_priority - process_1_priority;
}

int main(int argc, char *argv[])
{

	if (argc < 2) {
		   fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
		   fflush(stdout);
		   return 1;
	}

	/*******************/
	/* Parse the input */
	/*******************/
	FILE *input_file = fopen(argv[1], "r");
	if (!input_file) {
		   fprintf(stderr, "Error: Invalid filepath\n");
		   fflush(stdout);
		   return 1;
	}

	Process *processes = parse_file(input_file);

	/*******************/
	/* sort the input  */
	/*******************/
	Comparer process_comparer = &my_comparer;

#if DEBUG
	for (int i = 0; i < P_SIZE; i++) {
		    printf("%d (%d, %d) ",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	printf("\n");
#endif

	qsort(processes, P_SIZE, sizeof(Process), process_comparer);

	/**************************/
	/* print the sorted data  */
	/**************************/

	for (int i = 0; i < P_SIZE; i++) {
		    printf("%d (%d, %d)\n",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	fflush(stdout);
	fflush(stderr);

	/************/
	/* clean up */
	/************/
	free(processes);
	fclose(input_file);
	return 0;
}
