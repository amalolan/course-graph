#ifndef COURSE_GRAPH_UTIL_H
#define COURSE_GRAPH_UTIL_H
#define MAX_LINE_LENGTH 128
#define LIST_LENGTH 8192
#define TITLE_LEN 64
#define COURSE_NAME_LEN 16

#include <stdio.h>
#include "string.h"
#include <stdlib.h>
/**
 * Removes trailing \n for a string
 * @param str string with \n at the end
 */
void removeNewline(char *str);

/**
 * Calls strcmp() wrapper for void* data.
 * @param one  char* one
 * @param two char *two
 * @return strcmp(one,two)
 */
int string_compare(const void *one, const void *two);

/**
 * Wrapper for a call to free(data)
 * @param data allocated data to free.
 */
void data_free(void *data);


#endif //COURSE_GRAPH_UTIL_H
