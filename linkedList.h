/*
 * linkedList.h
 *
 *  Created on: Mar 17, 2017
 *      Author: quang
 */

#include "common.h"

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct LNode{
	int val;
	struct LNode* next;
};

bool list_destroy(struct LNode* list);
bool list_insert(struct LNode **list, int val);
bool list_delete(struct LNode **list, int val);
bool list_isEmpty(struct LNode* list);
bool list_isMember(struct LNode* list, int val);
void list_print(struct LNode *list);


#endif /* LINKEDLIST_H_ */
