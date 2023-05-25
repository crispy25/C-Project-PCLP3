/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdio.h>
#include <string.h>
#include "macros.h"
#include "utils.h"
#include "error.h"
#include "table.h"
#include "db.h"

void create_table(db_t *db, char *name)
{
	// check if table with key <name> already exist in database
	if (ht_has_key(db->tables, name)) {
		print_error(EXISTING_TABLE);
		return;
	}
	// create new hashtable for data contained by table
	hashtable_t *items = ht_create(HMAX, hash_function_key, compare_function_strings, key_val_free_function);
	// add new table to the database
	ht_put(db->tables, name, strlen(name) + 1, items, sizeof(*items));
	free(items);

	// create file for table with extension ".table"
	strcat(name, EXT);
	FILE *f = fopen(name, "w");
	DIE(!f, "Failed creating file for table");
	fclose(f);

	db->nTables++;
}

void delete_table(db_t *db, char *name)
{
	// check if there is no table with key <name> in database
	if (!ht_has_key(db->tables, name)) {
		print_error(NO_TABLE_FOUND);
		return;
	}

	// delete all data in table
	ht_remove_entry(db->tables, name);

	// add same table, but w/o any data
	create_table(db, name);
}

void drop_table(db_t *db, char *name)
{
	// check if there is no table with key <name> in database
	if (!ht_has_key(db->tables, name)) {
		print_error(NO_TABLE_FOUND);
		return;
	}

	// remove table from database
	ht_remove_entry(db->tables, name);

	// remove table file 
	strcat(name, EXT);
	remove(name);

	db->nTables--;
}

void select_table(db_t *db, char *name)
{
	// check if there is no table with key <name> in database
	if (!ht_has_key(db->tables, name)) {
		print_error(NO_TABLE_FOUND);
		return;
	}
	// select table
	db->table_selected = (hashtable_t *)ht_get(db->tables, name);
	printf("Selected <%s> table\n", name);
}

void update_table(db_t *db, char *name)
{
	// check if there is no table with key <name> in database
	if (!ht_has_key(db->tables, name)) {
		print_error(NO_TABLE_FOUND);
		return;
	}
	// check if there is no table selected
	if (!db->table_selected) {
		print_error(NO_TABLE_SELECTED);
		return;
	}
	// update table
	hashtable_t *table = db->table_selected;
	printf("Updated <%s> table\n", name);

	// update file on disk
	strcat(name, EXT);
	FILE *f = fopen(name, "w");
	DIE(!f, "Error opening file\n");
	print_table(table, f);

	fclose(f);
}

void find_table(db_t *db, char *name)
{
	if (ht_has_key(db->tables, name))
		printf("Table <%s> is present\n", name);
	else
		printf("Table <%s> is not present\n", name);
}

static void print_data(void *data, FILE *f)
{
	info *p = (info *)data;
	fprintf(f, "%s %s\n", (char *)p->key, (char *)p->value);
}

void print_table(hashtable_t *items, FILE *f)
{
	if (!items)
		return;
	
	for (unsigned int i = 0; i < items->hmax; i++) {
		ll_node_t *node = items->buckets[i]->head;
		while (node) {
			print_data(node->data, f);
			node = node->next;
		}
	}
}

void free_table(void *data)
{
	info *table = (info *)data;
	free(table->key);
	ht_free((hashtable_t *)table->value);
}
