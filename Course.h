#ifndef COURSE_GRAPH_COURSE_H
#define COURSE_GRAPH_COURSE_H
#define TITLE_LEN 10
#define NAME_LEN 30
#include "LinkedList.h"

typedef struct Course_struct {
    char title[TITLE_LEN];
    char name[NAME_LEN];
    LinkedList *prereqs;
} Course;

void Course_init(Course *c, char* title, char *name, LinkedList *prereqs) {
    strcpy(c->name, name);
    strcpy(c->title, title);
    prereqs = prereqs;
}


#endif //COURSE_GRAPH_COURSE_H
