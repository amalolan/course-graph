#ifndef COURSE_GRAPH_DEPARTMENT_H
#define COURSE_GRAPH_DEPARTMENT_H
#include "LinkedList.h"
#include "Parser.h"

typedef struct Course_struct {
    char title[COURSE_TITLE_LEN];
    char name[COURSE_NAME_LEN];
    LinkedList *prereqs;
} Course;

void Course_init(Course *course, char* title, char *name);

void Course_parseLine(Course *c, char* str);

void Course_toString(Course *c, char* str);

void Course_free(Course *course);

#endif //COURSE_GRAPH_DEPARTMENT_H
