#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "utils.h"
#include "macros.h"
#include "db.h"
#include "load.h"

void load_tables(db_t *db, char *dir)
{
    DIR *folder = opendir(dir);
	DIE(!folder, "Failed to open directory\n");

	struct dirent *file;

	while ((file = readdir(folder))) {
		char *fname = file->d_name;
		char name[MAX_STRING_SIZE];
		char *ext = strrchr(fname, '.');
		if (!ext)
			continue;
		size_t i;
		for (i = 0; i < strlen(fname) - strlen(ext); i++) {
			name[i] = fname[i];
		}
		name[i] = 0;
		if (!strcmp(ext, EXT)) {
			// if table already exist, don't add it
            if (ht_has_key(db->tables, name))
                return;
			char path[MAX_STRING_SIZE] = "";
			strcpy(path, dir);
			strcat(path, "/");
			strcat(path, fname);
			hashtable_t *items = load_table_data(path);
			ht_put(db->tables, name, strlen(name) + 1, items, sizeof(*items));
			#ifndef SILENT
			printf("DB> Loaded table %s\n", name);
			#endif
			SAFE_FREE(items);
		}
	}

	closedir(folder);
}
