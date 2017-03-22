/*
 * common.h
 *
 *  Created on: Mar 17, 2017
 *      Author: quang
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef enum {TASK_INSERT, TASK_SEARCH, TASK_DELETE, TASK_PRINT, NUMBER_OF_OPERATIONS} task_op;
typedef enum {false, true} bool;

typedef struct {
	int task_id;
	task_op operation;
	int data;
} task;

char* get_task_name(task_op name);
void print_task(task a_task);
void print_result(int thread_id, char *message, task new_task);

#endif /* COMMON_H_ */
