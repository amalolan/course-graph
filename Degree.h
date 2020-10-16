#ifndef COURSE_GRAPH_DEGREE_H
#define COURSE_GRAPH_DEGREE_H
#include "Department.h"
#include "Parser.h"

typedef struct Degree_struct {
    char name[DEGREE_NAME_LEN];
    LinkedList *reqs;
} Degree;

void Degree_init(Degree *degree, char *name);

void Degree_parseLine(Degree *degree, char *line);

void Degree_toString(Degree *degree, char *str);

void Degree_courseListFree(void *list);

void Degree_free(Degree *degree);

#endif //COURSE_GRAPH_DEGREE_H
