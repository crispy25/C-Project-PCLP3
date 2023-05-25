/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _ERROR_H_
#define _ERROR_H_

enum errors {
	INVALID_COMMAND = -1,
	NO_TABLE_FOUND,
	NO_TABLE_SELECTED,
	KEY_NOT_PRESENT,
	FILE_ERROR,
	EXISTING_TABLE,
	EXISTING_ITEM,
	INVALID_VALUE
};


void print_error(int err);

#endif // _ERROR_H_
