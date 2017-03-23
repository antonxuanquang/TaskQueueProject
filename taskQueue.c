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
bool get_task_node(struct QNode **task_node);

//*********************************************************
//
// Global variables
//
//*********************************************************
struct LNode *ll_head = NULL;
struct Queue *queue = NULL;
const MAX_RANDOM_VALUE = 100;
int volatile waiting_thread = 0;
pthread_mutex_t queue_mutex;
pthread_mutex_t list_mutex;
pthread_mutex_t thread_wait_mutex;
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
		bool successful = list_insert(list, new_task.data);
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





bool get_task_node(struct QNode **task_node) {

	while (true) {
		pthread_mutex_lock(&cond_mutex);
		waiting_thread++;
		while (pthread_cond_wait(&cond_task, &cond_mutex) != 0);
		waiting_thread--;
		pthread_mutex_unlock(&cond_mutex);

		if (done) return false;
		if (!queue_isEmpty(queue)) {
			pthread_mutex_unlock(&queue_mutex);
			*task_node = queue_dequeue(queue);
			pthread_mutex_unlock(&queue_mutex);
			return (task_node != NULL) ? true : false;
		}
	}
	return true;
}



void *handle_operation_loop(void* data) {
	int thread_id = *((int*)data);
	struct QNode *task_node;
	
	while (get_task_node(&task_node)) {
		pthread_mutex_lock(&list_mutex);
		perform_operations(thread_id, &ll_head, task_node->operation);
		pthread_mutex_unlock(&list_mutex);
		free(task_node);
	}

	pthread_exit(0);
}

void generate_tasks(int num_tasks) {
	int index;
	struct QNode* task_node;

	for (index = 1; index <= num_tasks; index++) {
		task new_task = {index, rand() % NUMBER_OF_OPERATIONS, rand() % MAX_RANDOM_VALUE};
		printf("Main: Generate task %d: %s %d\n", index, get_task_name(new_task.operation), new_task.data);
		
		pthread_mutex_lock(&queue_mutex);
		queue_enqueue(queue, new_task);
		pthread_mutex_unlock(&queue_mutex);

		if (waiting_thread > 0) {
			pthread_cond_signal(&cond_task);
		}
	}

	while (pthread_cond_signal(&cond_task) != 0);
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
	int num_tasks = atoi(argv[2]);
	int thr_id[num_threads];

	pthread_t  threads[num_threads];   /* thread's structures   */
	for (index = 0; index < num_threads; index++) {
		thr_id[index] = index;
		pthread_create(&threads[index], NULL, handle_operation_loop, (void*)&thr_id[index]);
	}

	generate_tasks(num_tasks);

	while (!queue_isEmpty(queue) || waiting_thread < num_threads);
	printf("out\n");
	done = true;
	pthread_cond_broadcast(&cond_task);

	for (index = 0; index < num_threads; index++) {
		pthread_join(&threads[index], NULL);
	}

	printf("Main: Print final list\n");
	list_print(ll_head);

	list_destroy(ll_head);
	queue_destroy(queue);

	pthread_mutex_destroy(&queue_mutex);
	pthread_mutex_destroy(&list_mutex);
	pthread_mutex_destroy(&cond_mutex);
	pthread_cond_destroy(&cond_task);

	return EXIT_SUCCESS;
}

































