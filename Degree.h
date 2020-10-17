#ifndef COURSE_GRAPH_DEGREE_H
#define COURSE_GRAPH_DEGREE_H
#include "Department.h"

typedef struct Degree_struct {
    char name[TITLE_LEN];
    LinkedList *reqs;
} Degree;

void Degree_init(Degree *degree, char *name);

void Degree_parseLine(Degree *degree, char *line);

int Degree_compareDegreeString(void *one, void*two);

void Degree_toString(const void *degree, char *str);

void Degree_courseListFree(void *list);

void Degree_free(void *data);

#endif //COURSE_GRAPH_DEGREE_H
