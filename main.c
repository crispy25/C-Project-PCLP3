/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "macros.h"
#include "error.h"
#include "hashtable.h"
#include "table.h"
#include "item.h"
#include "load.h"
#include "db.h"

int read_and_parse(cmd_t *input)
{
	int cnt = 0;
	char buffer[MAX_COMMAND_LENGTH];
	fgets(buffer, MAX_COMMAND_LENGTH, stdin);
	buffer[strlen(buffer) - 1] = 0;

	strcpy(input->args[0], "");
	strcpy(input->args[1], "");

	char *p = strtok(buffer, " ");
	while (p) {
		if (!cnt)
			strcpy(input->command, p);
		else if (cnt == 1)
			strcpy(input->type, p);
		else if (cnt == 3 && (strcmp(input->command, "ADD") || strcmp(input->command, "UPDATE") || strcmp(input->command, "FIND")) && strcmp(input->type, "ITEM")) {
			return 0;
		} else if (cnt > 3) {
			return 0;
		} else
			strcpy(input->args[cnt - 2], p);
		
		cnt++;	
		p = strtok(NULL, " ");
	}
	if (--cnt < 2 && strcmp(input->command, "EXIT"))
		return 0;
	return 1;
}

int run_command(db_t *db)
{
	cmd_t input;
	if (!read_and_parse(&input)) {
		print_error(INVALID_COMMAND);
		return 1;
	}

	if (!strcmp(input.command, "EXIT"))
		return 0;

	if (!strcmp(input.type, "TABLE")) {
		if (!strcmp(input.command, "CREATE"))
			create_table(db, input.args[0]);
		else if (!strcmp(input.command, "UPDATE"))
			update_table(db, input.args[0]);
		else if (!strcmp(input.command, "DELETE"))
			delete_table(db, input.args[0]);
		else if (!strcmp(input.command, "DROP"))
			drop_table(db, input.args[0]);
		else if (!strcmp(input.command, "SELECT"))
			select_table(db, input.args[0]);
		else if (!strcmp(input.command, "FIND"))
			find_table(db, input.args[0]);
		else
			print_error(INVALID_COMMAND);
	} else if (!strcmp(input.type, "ITEM")) {
		char *key, *value;
		key = input.args[0];
		value = input.args[1];

		if (!strcmp(input.command, "FIND")) {
			if (strlen(value))
				search_item(db, key, value, NULL);
			else
				search_item(db, key, NULL);
			return 1;
		}
		if (!db->table_selected) {
			print_error(NO_TABLE_SELECTED);
			return 1;
		}
		if (!strcmp(input.command, "ADD"))
			add_item(db->table_selected, key, value);
		else if (!strcmp(input.command, "DELETE"))
			delete_item(db->table_selected, key);
		else if (!strcmp(input.command, "UPDATE"))
			update_item(db->table_selected, key, value);
		else if (!strcmp(input.command, "GET"))
			get_item(db->table_selected, key);
		else
			print_error(INVALID_COMMAND);
	}
	else
		print_error(INVALID_COMMAND);

	return 1;
}

int main(int argc, char *argv[])
{	
	db_t *db = init_database();

	preload(db);

	#ifdef LOAD

	for (int i = 1; i < argc; i++)
		load_tables(db, argv[i]);

	#endif

	while (run_command(db));

	free_db_mem(db);

	return 0;
}
