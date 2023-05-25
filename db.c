/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "utils.h"
#include "macros.h"
#include "hashtable.h"
#include "table.h"
#include "load.h"
#include "db.h"

hashtable_t *load_table_data(char *file)
{	
	FILE *f = fopen(file, "r");
	DIE(!f, "Error opening file\n");
	
	hashtable_t *items = ht_create(HMAX, hash_function_key, compare_function_strings, key_val_free_function);

	char key[MAX_STRING_SIZE], value[MAX_STRING_SIZE];
	while (fscanf(f, "%s %s", key, value) == 2) {
		ht_put(items, key, strlen(key) + 1, value, strlen(value) + 1);
	}

	fclose(f);

	return items;
}

void preload(db_t *db)
{
	load_tables(db, ".");
}

db_t *init_database()
{
	db_t *db = ALLOC(db_t, 1);
	DIE(!db, "Error allocating memory for database\n");

	db->nTables = 0;
	db->table_selected = NULL;
	db->tables = ht_create(HMAX, hash_function_key, compare_function_strings, free_table);

	mkdir(DIR_PATH, 0777);
	chdir(DIR_PATH);

	return db;
}

void free_db_mem(db_t *db)
{
	ht_free(db->tables);

	SAFE_FREE(db);
}
