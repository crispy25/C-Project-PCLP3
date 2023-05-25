/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _ITEM_H_
#define _ITEM_H_

#include "error.h"
#include "db.h"

typedef struct  item_t item_t;
struct item_t {
    char *key;
    char *value;
};

// Add item to the table given
void add_item(hashtable_t *table, char *key, char *value);

// Update item with new value
void update_item(hashtable_t *table, char *key, char *value);

// Delete item from table
void delete_item(hashtable_t *table, char *key);

// Print item
void get_item(hashtable_t *table, char *key);

// Helper function for search()
void find_item(hashtable_t *table, char *key);

/**
 * Search for item in the selected table if the key is the only argument
 * Otherwise, search in all tables for the key, if second argument is "-GLOBAL"
*/
void search_item(db_t *db, ...);

#endif // _ITEM_H_
