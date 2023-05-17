/* Copyright 2023 Popescu Cristian-Emanuel 312CA */
#ifndef _UTILS_H_
#define _UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#endif /* _UTILS_H_ */
