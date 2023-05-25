/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _TABLE_H_
#define _TABLE_H_

#include "macros.h"
#include "hashtable.h"
#include "db.h"

typedef struct table_t table_t;
struct table_t
{
	char name[MAX_STRING_SIZE];
	hashtable_t *items;
};

// Add new table to the database
void create_table(db_t *db, char *name);

// Clear all data from the table
void delete_table(db_t *db, char *name);

// Remove the table from the database
void drop_table(db_t *db, char *name);

// Select the table as current table
void select_table(db_t *db, char *name);

// Save the changes on the disk
void update_table(db_t *db, char *name);

// Search for the table in the database
void find_table(db_t *db, char *name);

// Write all data in the table to file
void print_table(hashtable_t *items, FILE *f);

// Free memory used by table
void free_table(void *data);

#endif // _TABLE_H_
