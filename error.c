/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#include <stdio.h>
#include "error.h"

void print_error(int err)
{
	switch (err)
	{
	case INVALID_COMMAND:
		printf("Invalid command\n");
		break;
	case NO_TABLE_FOUND:
		printf("No table found\n");
		break;
	case NO_TABLE_SELECTED:
		printf("No table selected\n");
		break;
    case KEY_NOT_PRESENT:
        printf("Key is not present\n");
        break;
    case FILE_ERROR:
        printf("Error opening file\n");
		break;
	case EXISTING_TABLE:
        printf("Table already exists\n");
        break;
	case EXISTING_ITEM:
        printf("Item already exists\n");
        break;
	case INVALID_VALUE:
        printf("Value is not valid\n");
        break;
	default:
	 	printf("Error?\n");
		break;
	}
}
