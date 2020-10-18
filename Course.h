#ifndef COURSE_GRAPH_COURSE_H
#define COURSE_GRAPH_COURSE_H

#include "LinkedList.h"

typedef struct Course_struct {
    char title[TITLE_LEN];
    char name[COURSE_NAME_LEN];
    LinkedList *prereqs;
} Course;


#endif //COURSE_GRAPH_COURSE_H
