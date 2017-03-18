/*
 * taskQueue.c
 *
 *  Created on: Mar 17, 2017
 *      Author: Quang
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "common.h"
#include "linkedList.h"

#define NUM_THREADS 3

//*********************************************************
//
// Type Declarations
//
//*********************************************************


//*********************************************************
//
// Extern Declarations
//
//*********************************************************


//********************************************************
//
// Function Prototypes
//
//*********************************************************
bool queue_create();
bool queue_destroy();
bool queue_enqueue();
bool queue_dequeue();
bool queue_isEmpty();
void print_task(task a_task);
void perform_operations(struct node **head_ref, task new_task);

//*********************************************************
//
// Global variables
//
//*********************************************************

//*********************************************************
//
// Main Function
//
//*********************************************************



int main(int argc, char* argv[]) {
	if (argc != 3 && atoi(argv[1]) <= 0 && atoi(argv[2]) <= 0) {
		printf("usage: %s <number of threads > 0> <number of tasks > 0> \n", argv[0]);
	}
//	int num_threads = atoi(argv[1]);
	int num_tasks = atoi(argv[2]);
	int index;
	struct node *head = NULL;
	srand(time(NULL));
	for (index = 0; index < num_tasks; index++) {
		task new_task = {index, rand() % NUMBER_OF_OPERATIONS, rand() % 100};
		perform_operations(&head, new_task);
	}
}

void perform_operations(struct node **list, task new_task) {
	task_op operation = new_task.operation;
	if (operation == TASK_INSERT) {
		bool successful = list_insert(list, new_task.data);
		if (successful) {
			printf("%s %d: Insert value %d in linked list \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		} else {
			printf("%s %d: Can't insert value %d in linked list \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		}
	} else if (operation == TASK_SEARCH) {
		bool foundData = list_isMember((*list), new_task.data);
		if (foundData) {
			printf("%s %d: Found value %d in linked list \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		} else {
			printf("%s %d: There is no value %d in linked list \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		}
	} else if (operation == TASK_DELETE) {
		bool successful = list_delete(list, new_task.data);
		if (successful) {
			printf("%s %d: Delete value %d in linked list \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		} else {
			printf("%s %d: There is no value %d in linked list to delete \n",
					get_task_name(new_task.operation), new_task.data, new_task.data);
		}
	} else if (operation == TASK_PRINT) {
		printf("%s: ", get_task_name(new_task.operation));
		list_print((*list));
	}
}

void print_task(task a_task) {
	printf("task id: %d \n"
			"operation: %s \n"
			"data: %d \n", a_task.task_id, get_task_name(a_task.operation), a_task.data);
}






































