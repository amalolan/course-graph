#ifndef COURSE_GRAPH_DEGREE_H
#define COURSE_GRAPH_DEGREE_H
#define DEGREE_NAME_LEN 30
#define COURSE_LINE_LEN 100
#include "Course.h"

typedef struct Degree_struct {
    char name[DEGREE_NAME_LEN];
    LinkedList *reqs;
} Degree;

void Degree_init(Degree *degree, char *name);

void Degree_parseLine(Degree *degree, char *line);

void Degree_toString(Degree *degree, char *str);

void CourseList_free(void *list);

void Degree_free(Degree *degree);

#endif //COURSE_GRAPH_DEGREE_H
