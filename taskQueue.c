/*
 * taskQueue.c
 *
 *  Created on: Mar 17, 2017
 *      Author: Quang
 */

#include <stdio.h>
#define __USE_GNU
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "common.h"
#include "linkedList.h"
#include "queue.h"


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


void perform_operations(int thread_id, struct LNode **list, task new_task);
void *handle_operation_loop(void* data);
void generate_tasks(int num_tasks);

//*********************************************************
//
// Global variables
//
//*********************************************************
struct LNode *ll_head = NULL;
struct Queue *queue = NULL;
const MAX_RANDOM_VALUE = 100;
int waiting_thread = 0;
pthread_mutex_t queue_mutex;
pthread_mutex_t list_mutex;
pthread_mutex_t cond_mutex;
pthread_cond_t  cond_task;
bool done = false;

//*********************************************************
//
// Main Function
//
//*********************************************************

void perform_operations(int thread_id, struct LNode **list, task new_task) {
	task_op operation = new_task.operation;
	if (operation == TASK_INSERT) {
		if (list_isMember((*list), new_task.data)) {
			print_result(thread_id, "Can't insert value in linked list", new_task);
			return;
		}
		pthread_mutex_lock(&list_mutex);
		bool successful = list_insert(list, new_task.data);
		pthread_mutex_unlock(&list_mutex);
		if (successful) {
			print_result(thread_id, "Insert successfully", new_task);
		} else {
			print_result(thread_id, "Can't insert value in linked list", new_task);
		}
	} else if (operation == TASK_SEARCH) {
		bool foundData = list_isMember((*list), new_task.data);
		if (foundData) {
			print_result(thread_id, "Found it!", new_task);
		} else {
			print_result(thread_id, "Value not found!", new_task);
		}
	} else if (operation == TASK_DELETE) {
		pthread_mutex_lock(&list_mutex);
		bool successful = list_delete(list, new_task.data);
		pthread_mutex_unlock(&list_mutex);
		if (successful) {
			print_result(thread_id, "Delete successfully!", new_task);
		} else {
			print_result(thread_id, "Value not found!", new_task);
		}
	} else if (operation == TASK_PRINT) {
		printf("Thread %d: Task %d: %s: ", thread_id, new_task.task_id, get_task_name(new_task.operation));
		list_print((*list));
	}
}





void generate_tasks(int num_tasks) {
	int index;
	bool isEmpty = false;

	srand(time(NULL));
	for (index = 1; index <= num_tasks; index++) {
		task new_task = {index, rand() % NUMBER_OF_OPERATIONS, rand() % MAX_RANDOM_VALUE};
		printf("Main: Generate task %d: %s %d\n", index, get_task_name(new_task.operation), new_task.data);
		
		pthread_mutex_lock(&queue_mutex);
		queue_enqueue(queue, new_task);
		pthread_mutex_unlock(&queue_mutex);

		pthread_cond_signal(&cond_task);
	}
	while (!isEmpty) {
		pthread_mutex_lock(&queue_mutex);
		isEmpty = queue_isEmpty(queue);
		pthread_mutex_unlock(&queue_mutex);

		pthread_cond_signal(&cond_task);
	}
	done = true;
	// while (waiting_thread > 0) {
	// 	pthread_cond_broadcast(&cond_task);
	// }
	
}

void *handle_operation_loop(void* data) {
	int thread_id = *((int*)data);
	task new_task;

	/* lock the mutex, to assure exclusive access to the list */

	while (true) {
		if (done) return;
		waiting_thread++;
		pthread_cond_wait(&cond_task, &cond_mutex);
		waiting_thread--;
		if (queue_isEmpty(queue)) {
			return;
		} else {
			pthread_mutex_lock(&queue_mutex);
			new_task = queue_dequeue(queue)->operation;
			pthread_mutex_unlock(&queue_mutex);
			
			perform_operations(thread_id, &ll_head, new_task);
			
		}
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	int index;

	if (argc != 3 && atoi(argv[1]) <= 0 && atoi(argv[2]) <= 0) {
		printf("usage: %s <number of threads > 0> <number of tasks > 0> \n", argv[0]);
		return EXIT_FAILURE;
	}

	pthread_mutex_init(&queue_mutex, NULL);
	pthread_mutex_init(&list_mutex, NULL);
	pthread_mutex_init(&cond_mutex, NULL);
	pthread_cond_init(&cond_task, NULL);
	
	queue = queue_create();

	int num_threads = atoi(argv[1]);
	int thr_id[num_threads];
	int num_tasks = atoi(argv[2]);

	pthread_t  threads[num_threads];   /* thread's structures   */
	for (index = 0; index < num_threads; index++) {
		thr_id[index] = index;
		pthread_create(&threads[index], NULL, handle_operation_loop, (void*)&thr_id[index]);
	}

	generate_tasks(num_tasks);

	for (index = 0; index < num_threads; index++) {
		pthread_join(threads[index], NULL);
	}

	list_destroy(ll_head);
	queue_destroy(queue);

	pthread_mutex_destroy(&queue_mutex);
	pthread_mutex_destroy(&list_mutex);
	pthread_mutex_destroy(&cond_mutex);
	pthread_cond_destroy(&cond_task);

	return EXIT_SUCCESS;
}

































