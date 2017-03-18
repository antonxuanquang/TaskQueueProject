/*
 * queue.h
 *
 *  Created on: Mar 18, 2017
 *      Author: quang
 */
#include "common.h"

#ifndef QUEUE_H_
#define QUEUE_H_

struct QNode {
	task operation;
	struct QNode* next;
};

struct Queue {
	struct QNode *head, *tail;
};

struct Queue* queue_create();
struct QNode* node_create(task new_task);
bool queue_destroy();
bool queue_enqueue(struct Queue* queue, task new_task);
struct QNode* queue_dequeue();
bool queue_isEmpty();


#endif /* QUEUE_H_ */
