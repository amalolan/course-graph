#ifndef COURSE_GRAPH_COURSE_H
#define COURSE_GRAPH_COURSE_H
#define COURSE_TITLE_LEN 10
#define COURSE_NAME_LEN 40
#include "LinkedList.h"

typedef struct Course_struct {
    char title[COURSE_TITLE_LEN];
    char name[COURSE_NAME_LEN];
    LinkedList *prereqs;
} Course;

void Course_init(Course *c, char* title, char *name, LinkedList *prereqs);


#endif //COURSE_GRAPH_COURSE_H
