/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _LIST_H_
#define _LIST_H_

typedef struct ll_node_t ll_node_t;
typedef struct linked_list_t linked_list_t;

typedef struct ll_node_t
{
	void* data;
	struct ll_node_t* next;
} ll_node_t;

typedef struct linked_list_t
{
	ll_node_t* head;
	unsigned int data_size;
	unsigned int size;
} linked_list_t;

linked_list_t *ll_create(unsigned int data_size);

void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data);

ll_node_t *ll_remove_nth_node(linked_list_t* list, unsigned int n);

unsigned int ll_get_size(linked_list_t* list);

void ll_free(linked_list_t** pp_list);

void ll_print_string(linked_list_t* list);

#endif /* _LIST_H_ */
