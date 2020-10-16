#ifndef COURSE_GRAPH_TYPES_H
#define COURSE_GRAPH_TYPES_H
#define DEGREE_NAME_LEN 30
#define COURSE_LINE_LEN 100
#define COURSE_TITLE_LEN 10
#define COURSE_NAME_LEN 40

#include <stdio.h>
#include "string.h"
#include <stdlib.h>


void dont_free(void *);

int double_compare(const void *one, const void *two);

void double_toString(const void *data, char *str);

void data_free(void *data);

void string_toString(const void *, char *str);



#endif //COURSE_GRAPH_TYPES_H
