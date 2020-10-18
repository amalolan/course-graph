#ifndef COURSE_GRAPH_UTIL_H
#define COURSE_GRAPH_UTIL_H
#define MAX_LINE_LENGTH 128
#define LIST_LENGTH 8192
#define TITLE_LEN 64
#define COURSE_NAME_LEN 16

#include <stdio.h>
#include "string.h"
#include <stdlib.h>

void removeNewline(char *str);

int string_compare(const void *one, const void *two);

void data_free(void *data);


#endif //COURSE_GRAPH_UTIL_H
