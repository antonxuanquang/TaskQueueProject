/*
 * common.c
 *
 *  Created on: Mar 17, 2017
 *      Author: quang
 */

#include "common.h"

char* get_task_name(task_op name) {
	if (name == TASK_INSERT) {
		return "TASK_INSERT";
	} else if (name == TASK_SEARCH) {
		return "TASK_SEARCH";
	} else if (name == TASK_DELETE) {
		return "TASK_DELETE";
	} else if (name == TASK_PRINT) {
		return "TASK_PRINT";
	} else {
		return "";
	}
}

void print_task(task a_task) {
	printf("task id: %d \n"
			"operation: %s \n"
			"data: %d \n", a_task.task_id, get_task_name(a_task.operation), a_task.data);
}

void print_result(int thread_id, char *message, task new_task) {
	printf("Thread %d: Task %d: %s %d: %s\n", thread_id,
		new_task.task_id, get_task_name(new_task.operation), new_task.data, message);
}