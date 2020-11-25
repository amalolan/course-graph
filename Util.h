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
 * Used to directly compare two pointers' addresses
 * @param one pointer one
 * @param two pointer two
 * @return 0 if one == two, -1 otherwise
 */
int direct_compare(const  void *one, const void *two);

/**
 * Wrapper for a call to free(data)
 * @param data allocated data to free.
 */
void free_data(void *data);

/**
 * Destructor to not free any data. Used when copies are made or objects are
 * initialized on the heap.
 * @param data data to not free
 */
void dont_free(void *data);

/**
 * wrapper to pretty much copy the string from data to str. Used to follow
 * coding convention of conversion to strings for data structures.
 * @param data the char * string
 * @param str the place to copy it to. Must be initialized and allocated.
 */
void string_toString(const void *data, char *str);

#endif //COURSE_GRAPH_UTIL_H
