/*
 * queue.c
 *
 *  Created on: Mar 18, 2017
 *      Author: quang
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue* queue_create() {
	struct Queue* queue = malloc(sizeof(struct Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

bool queue_destroy(struct Queue* queue) {
	struct QNode* current;
	while (queue->head != NULL) {
		current = queue->head;
		queue->head = queue->head->next;
		free(current);
	}
	queue->tail = NULL;
	return true;
}

struct QNode* node_create(task new_task) {
	struct QNode* new_node = malloc(sizeof(struct QNode));
	new_node->operation = new_task;
	new_node->next = NULL;
	return new_node;
}

bool queue_isEmpty(struct Queue* queue) {
	return queue->head == NULL;
}

bool queue_enqueue(struct Queue* queue, task new_task) {
	struct QNode* new_node = node_create(new_task);

	if (queue->tail == NULL) {
		queue->head = queue->tail = new_node;
		return true;
	}

	queue->tail->next = new_node;
	queue->tail = new_node;
	return true;
}

struct QNode* queue_dequeue(struct Queue* queue) {
	if (queue_isEmpty(queue)) {
		return NULL;
	}

	struct QNode* result = queue->head;
	queue->head = queue->head->next;

	if (queue->head == NULL) {
		queue->tail = NULL;
	}

	return result;
}








