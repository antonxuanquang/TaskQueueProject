/*
 * linkedList.h
 *
 *  Created on: Mar 17, 2017
 *      Author: quang
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct node{
	int val;
	struct node* next;
} node;

bool list_destroy(struct node* list);
bool list_insert(struct node **list, int val);
bool list_delete(struct node **list, int val);
bool list_isEmpty(struct node* list);
bool list_isMember(struct node* list, int val);
void list_print(struct node *list);


#endif /* LINKEDLIST_H_ */
