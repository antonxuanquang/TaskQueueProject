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

#endif /* COMMON_H_ */
