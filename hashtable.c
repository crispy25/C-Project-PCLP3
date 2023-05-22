/* Copyright 2023 <Popescu Cristian-Emanuel 312CA> */
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utils.h"
#include "hashtable.h"

unsigned int compare_function_ints(void *a, void *b)
{
	return *(unsigned int *)a - *(unsigned int *)b;
}

int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int hash_function_key(void *a) {
	unsigned char *puchar_a = (unsigned char *)a;
	unsigned int hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c;

	return hash;
}

void key_val_free_function(void *data) {
	info *p = (info *)data;
	free(p->key);
	free(p->value);
}

hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*),
		void (*key_val_free_function)(void*))
{
	hashtable_t *ht = malloc(sizeof(*ht));
	DIE(!ht, "Error allocating memory\n");
	ht->buckets = malloc(hmax * sizeof(*ht->buckets));
	DIE(!ht->buckets, "Error allocating memory\n");
	for (unsigned int i = 0; i < hmax; i++) {
		ht->buckets[i] = ll_create(sizeof(info));
		DIE(!ht->buckets[i], "Error allocating memory\n");
	}
	ht->compare_function = compare_function;
	ht->hash_function = hash_function;
	ht->key_val_free_function = key_val_free_function;
	ht->hmax = hmax;
	ht->size = 0;
	return ht;
}

int ht_has_key(hashtable_t *ht, void *key)
{
	if (!ht || !ht->size)
		return 0;
	unsigned int index = ht->hash_function(key) % ht->hmax;
	ll_node_t *node = ht->buckets[index]->head;
	while (node) {
		if (!ht->compare_function(((info *)node->data)->key, key))
			return 1;
		node = node->next;
	}
	return 0;
}

void *ht_get(hashtable_t *ht, void *key)
{
	if (!ht || !ht->size)
		return NULL;
	unsigned int index = ht->hash_function(key) % ht->hmax;
	ll_node_t *node = ht->buckets[index]->head;
	while (node) {
		if (!ht->compare_function(((info *)node->data)->key, key))
			return ((info*)node->data)->value;
		node = node->next;
	}
	return NULL;
}

void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	if (!ht)
		return;
	unsigned int index = ht->hash_function(key) % ht->hmax;
	ll_node_t *node = ht->buckets[index]->head;
	ht->size++;
	while (node) {
		if (!ht->compare_function(((info *)node->data)->key, key)) {
			memcpy(((info *)node->data)->value, value, value_size);
			return;
		}
		node = node->next;
	}
	info i;
	i.key = malloc(key_size);
	DIE(!i.key, "Error alocating memory\n");
	i.value = malloc(value_size);
	DIE(!i.value, "Error alocating memory\n");
	memcpy(i.key, key, key_size);
	memcpy(i.value, value, value_size);
	ll_add_nth_node(ht->buckets[index], ht->buckets[index]->size, &i);
}

void ht_remove_entry(hashtable_t *ht, void *key)
{
	if (!ht || !ht->size)
		return;
	unsigned int index = ht->hash_function(key) % ht->hmax, pos = 0;
	ll_node_t *node = ht->buckets[index]->head;
	if (!node)
		return;
	while (node) {
		if (!ht->compare_function(((info *)node->data)->key, key)) {
			break;
		}
		node = node->next;
		pos++;
	}
	node = ll_remove_nth_node(ht->buckets[index], pos);
	key_val_free_function(node->data);
	free(node->data);
	free(node);
	ht->size--;
}

void ht_free(hashtable_t *ht)
{
	if (!ht)
		return;
	for (unsigned int i = 0; i < ht->hmax; i++) {
		ll_node_t *node = ht->buckets[i]->head, *prev;
		while (node) {
			prev = node;
			node = node->next;
			key_val_free_function(prev->data);
		}
		ll_free(&ht->buckets[i]);
	}
	if (ht->buckets)
		free(ht->buckets);
	free(ht);
	ht = NULL;
}

unsigned int ht_get_size(hashtable_t *ht)
{
	return ht == NULL ? 0 : ht->size;
}

unsigned int ht_get_hmax(hashtable_t *ht)
{
	return ht == NULL ? 0 : ht->hmax;
}

void print_data(void *data, FILE *f)
{
	info *p = (info *)data;
	fprintf(f, "%s %s\n", (char *)p->key, (char *)p->value);
}

void ht_print(hashtable_t *ht, FILE *f)
{
	if (!ht)
		return;
	for (unsigned int i = 0; i < ht->hmax; i++) {
		ll_node_t *node = ht->buckets[i]->head;
		while (node) {
			print_data(node->data, f);
			node = node->next;
		}
	}
}