/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _MACROS_H_
#define _MACROS_H_

#define MAX_COMMAND_LENGTH 1024
#define MAX_STRING_SIZE	256
#define MAX_ARGS 2
#define DIR_PATH "./tables/"
#define EXT ".tbl"

enum commands {
	CREATE_TABLE,
	DELETE_TABLE,
	DROP_TABLE,
	SELECT_TABLE,
	UPDATE_TABLE,
	FIND_TABLE,
	ADD_ITEM,
	UPDATE_ITEM,
	DELETE_ITEM,
	GET_ITEM,
	FIND_ITEM,
	EXIT
};

typedef struct cmd_t cmd_t;
struct cmd_t
{
	char command[MAX_STRING_SIZE];
	char type[MAX_STRING_SIZE];
	char args[MAX_ARGS][MAX_STRING_SIZE];
};

#endif /* _MACROS_H_ */
