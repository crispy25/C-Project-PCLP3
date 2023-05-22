/* Copyright 2023 <Popescu Cristian-Emanuel 312CA> */
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include "list.h"

#define MAX_STRING_SIZE	256
#define HMAX 100

typedef struct info {
	void *key;
	void *value;
} info;

typedef struct hashtable_t hashtable_t;

struct hashtable_t {
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax;
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
	void (*key_val_free_function)(void*);
};

unsigned int compare_function_ints(void *a, void *b);

int compare_function_strings(void *a, void *b);

unsigned int hash_function_key(void *a);

void key_val_free_function(void *data);

hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*),
		void (*key_val_free_function)(void*));

int ht_has_key(hashtable_t *ht, void *key);

void *ht_get(hashtable_t *ht, void *key);

void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size);

void ht_remove_entry(hashtable_t *ht, void *key);

void ht_free(hashtable_t *ht);

unsigned int ht_get_size(hashtable_t *ht);

unsigned int ht_get_hmax(hashtable_t *ht);

void print_data(void *data, FILE *f);

void ht_print(hashtable_t *ht, FILE *f);

#endif /* _HASHTABLE_H_ */
