/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _LOAD_H_
#define _LOAD_H_

#include <stdarg.h>
#include "db.h"

// load all tables in memory from given folder
void load_tables(db_t *db, char *dir);

#endif // _LOAD_H_
