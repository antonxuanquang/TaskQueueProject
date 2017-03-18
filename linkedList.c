/*
 * linkedList.c
 *
 *  Created on: Mar 17, 2017
 *      Author: quang
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "linkedList.h"


bool list_destroy(struct LNode* head) {
	struct LNode* current;
	while (head != NULL) {
		current = head;
		head = head->next;
		free(current);
	}
	return true;
}

bool list_insert(struct LNode **list, int val) {
	struct LNode *current = (*list);
	struct LNode *new_node = (struct LNode *) malloc(sizeof(struct LNode));
	if (new_node == NULL) return false;
	new_node->val = val;
	new_node->next = NULL;
	if (current == NULL) {
		(*list) = new_node;
		return true;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = new_node;
	return true;
}

bool list_delete(struct LNode **head, int val) {
	struct LNode *current = (*head);
	struct LNode *prev = NULL;
	while (current != NULL) {
		if (current->val == val) {
			if (current == (*head)) {
				*head = (*head)->next;
			} else {
				prev->next = current->next;
			}
			free(current);
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}

bool list_isEmpty(struct LNode* list) {
	return (list != NULL);
}

bool list_isMember(struct LNode* list, int val) {
	struct LNode* current = list;
	while (current != NULL) {
		if (current->val == val) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void list_print(struct LNode *list) {
	struct LNode *current = list;
	while (current != NULL) {
		printf("%d->", current->val);
		current = current->next;
	}
	printf("NULL\n");
}


