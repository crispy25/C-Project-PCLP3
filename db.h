/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _DB_H_
#define _DB_H_

#include "hashtable.h"

typedef struct db_t db_t;
struct db_t
{
	int nTables;
	hashtable_t *table_selected;
	hashtable_t *tables;
};

// Return new database
db_t *init_database();

// Load all existing tables from current directory
void preload(db_t *db);

// Load all table data in memory
hashtable_t *load_table_data(char *file);

void free_db_mem(db_t *db);


#endif // _DB_H_
