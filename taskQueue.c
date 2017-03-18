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
#include "queue.h"

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

void print_task(task a_task);
void perform_operations(struct node **head_ref, task new_task);
void print_result(char *message, task new_task);

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
	struct Queue *queue = queue_create();
	srand(time(NULL));
	for (index = 1; index <= num_tasks; index++) {
		task new_task = {index, rand() % NUMBER_OF_OPERATIONS, rand() % 100};
		queue_enqueue(queue, new_task);
	}

	while (!queue_isEmpty(queue)) {
		task new_task = queue_dequeue(queue)->operation;
		perform_operations(&head, new_task);
	}

	list_destroy(head);
	queue_destroy(queue);
}

void perform_operations(struct node **list, task new_task) {
	task_op operation = new_task.operation;
	if (operation == TASK_INSERT) {
		bool successful = list_insert(list, new_task.data);
		if (successful) {
			print_result("Insert successfully", new_task);
		} else {
			print_result("Can't insert value %d in linked list \n", new_task);
		}
	} else if (operation == TASK_SEARCH) {
		bool foundData = list_isMember((*list), new_task.data);
		if (foundData) {
			print_result("Found it!", new_task);
		} else {
			print_result("Value not found!", new_task);
		}
	} else if (operation == TASK_DELETE) {
		bool successful = list_delete(list, new_task.data);
		if (successful) {
			print_result("Delete successfully!", new_task);
		} else {
			print_result("Value not found!", new_task);
		}
	} else if (operation == TASK_PRINT) {
		printf("Task %d: %s: ", new_task.task_id, get_task_name(new_task.operation));
		list_print((*list));
	}
}

void print_task(task a_task) {
	printf("task id: %d \n"
			"operation: %s \n"
			"data: %d \n", a_task.task_id, get_task_name(a_task.operation), a_task.data);
}

void print_result(char *message, task new_task) {
	printf("Task %d: %s %d: %s\n", new_task.task_id, get_task_name(new_task.operation),
			new_task.data, message);
}




































