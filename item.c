/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "hashtable.h"
#include "macros.h"
#include "error.h"
#include "item.h"
#include "table.h"
#include "db.h"

void add_item(hashtable_t *table, char *key, char *value)
{
	if (!value || !strlen(value)) {
		printf("Invalid value\n");
		return;
	}
	if (ht_has_key(table, key)) {
		print_error(EXISTING_ITEM);
		return;
	}
	ht_put(table, key, strlen(key) + 1, value, strlen(value) + 1);
}

void update_item(hashtable_t *table, char *key, char *value)
{
	if (!value || !strlen(value)) {
		printf("Invalid value\n");
		return;
	}
	ht_put(table, key, strlen(key) + 1, value, strlen(value) + 1);
}

void delete_item(hashtable_t *table, char *key)
{
	if (ht_has_key(table, key))
		ht_remove_entry(table, key);
	else
		print_error(KEY_NOT_PRESENT);
}

void get_item(hashtable_t *table, char *key)
{
	char *value = (char *)ht_get(table, key);
	if (value) {
		#ifdef PLAIN
		printf("%s %s\n", key, value);
		#elif defined EQU
		printf("%s = %s\n", key, value);
		#else
		printf("Key: %s - Value: %s\n", key, value);
		#endif
		return;
	}
	
	print_error(KEY_NOT_PRESENT);
}

void find_item(hashtable_t *table, char *key)
{
	if (!table) {
		print_error(NO_TABLE_SELECTED);
		return;
	}

	if (ht_has_key(table, key))
		printf("Item with key <%s> is present\n", key);
	else
		print_error(KEY_NOT_PRESENT);
}

void search_item(db_t *db, ...)
{
	if (!db)
        return;
	
    va_list list;
    va_start(list, db);
	int argc = 0;

	char *args[MAX_ARGS];

    void *arg = va_arg(list, char *);
    while (arg) {
		if (argc < MAX_ARGS)
			args[argc++] = arg;
        arg = va_arg(list, char *);
    }
	
	/**
	 * If we only have one argument, the key, search it in the table selected
	 * Otherwise, search it in all tables in the database
	*/
	if (argc == 1)
		find_item(db->table_selected, args[0]);
	else
	if (argc == 2 && !strcmp(args[1], "-GLOBAL")) {
		int key_present = 0;
		// traverse all tables and check for the key
		for (unsigned int i = 0; i < db->tables->hmax; i++) {
			ll_node_t *node = db->tables->buckets[i]->head;
			if (node) {
				hashtable_t *items = (hashtable_t *)(((info *)node->data)->value);
				if (items)
					if (ht_has_key(items , args[0])) {
						printf("Item with key <%s> is present in table <%s>\n", args[0], (char *)(((info *)node->data)->key));
						key_present = 1;
					}
			}
		}
		// if key is nor present
		if (!key_present)
			print_error(KEY_NOT_PRESENT);
	} else
		print_error(INVALID_COMMAND);
    
    va_end(list);
}