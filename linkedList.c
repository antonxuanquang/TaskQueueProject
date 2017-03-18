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


bool list_destroy(struct node* list) {
	if (list == NULL) return true;
	else {
		struct node* current = list;
		struct node* next;
		do {
			next = current->next;
			free(current);
		} while(next != NULL);
		return true;
	}
}

bool list_insert(struct node **list, int val) {
	struct node *current = (*list);
	struct node *new_node = (struct node *) malloc(sizeof(node));
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

bool list_delete(struct node **head, int val) {
	struct node *current = (*head);
	struct node *prev = NULL;
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

bool list_isEmpty(struct node* list) {
	return (list != NULL);
}

bool list_isMember(struct node* list, int val) {
	struct node* current = list;
	while (current != NULL) {
		if (current->val == val) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void list_print(struct node *list) {
	struct node *current = list;
	while (current != NULL) {
		printf("%d->", current->val);
		current = current->next;
	}
	printf("NULL\n");
}


