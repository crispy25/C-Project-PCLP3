/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utils.h"

linked_list_t *ll_create(unsigned int data_size)
{
	linked_list_t* ll;

	ll = ALLOC(linked_list_t, 1);

	ll->head = NULL;
	ll->data_size = data_size;
	ll->size = 0;

	return ll;
}

void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *prev, *curr;
	ll_node_t* new_node;

	if (!list)
		return;

	if (n > list->size)
		n = list->size;

	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}

	new_node = ALLOC(ll_node_t, 1);
	new_node->data = malloc(list->data_size);
	memcpy(new_node->data, new_data, list->data_size);

	new_node->next = curr;
	if (prev == NULL)
		list->head = new_node;
	else
		prev->next = new_node;

	list->size++;
}

ll_node_t *ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *prev, *curr;

	if (!list || !list->head)
		return NULL;

	if (n > list->size - 1)
		n = list->size - 1;

	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}

	if (prev == NULL)
		list->head = curr->next;
	else
		prev->next = curr->next;

	list->size--;

	return curr;
}

unsigned int ll_get_size(linked_list_t* list)
{
	 if (!list)
		return -1;

	return list->size;
}

void ll_free(linked_list_t** list)
{
	ll_node_t* currNode;

	if (!list || !*list)
		return;

	while (ll_get_size(*list) > 0) {
		currNode = ll_remove_nth_node(*list, 0);
		SAFE_FREE(currNode->data);
		currNode->data = NULL;
		SAFE_FREE(currNode);
		currNode = NULL;
	}

	SAFE_FREE(*list);
	*list = NULL;
}

void ll_print_string(linked_list_t* list)
{
	ll_node_t* curr;

	if (!list)
		return;

	curr = list->head;
	while (curr != NULL) {
		printf("%s ", (char*)curr->data);
		curr = curr->next;
	}

	printf("\n");
}
