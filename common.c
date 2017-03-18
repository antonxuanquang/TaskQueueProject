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
