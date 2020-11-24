#ifndef COURSE_GRAPH_REQUIREMENTS_H
#define COURSE_GRAPH_REQUIREMENTS_H

#include "Util.h"
#include "LinkedList.h"
#include "BinaryTree.h"

typedef struct Requirements_struct {
    LinkedList *ands; // 2D Linked List of ANDs, inner are ORs
} Requirements;


void Requirements_init(Requirements *);
void Requirements_parseLine(Requirements *reqs, char *line, bool or);
void Requirements_removeCourse(Requirements *reqs, char *courseName);
void Requirements_findDifference(Requirements *reqs, BinaryTree *courseStrings, Requirements *remaining);
//void Requirements_isSatisfied(Requirements *reqs, )
void Requirements_toString(Requirements *reqs, char *str, char *delim);
void Requirements_innerListFree(void *);
void Requirements_free(Requirements *reqs, void (*data_free)(void *));

#endif //COURSE_GRAPH_REQUIREMENTS_H
