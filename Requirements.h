#ifndef COURSE_GRAPH_REQUIREMENTS_H
#define COURSE_GRAPH_REQUIREMENTS_H

#include "Util.h"
#include "LinkedList.h"
#include "BinaryTree.h"

/**
 * Contains LinkedList<LinkedList<void*>> in CNF form where
 * outer linked lists are conjuncts and inner are disjuncts.
 * Used in courses for prereqs and degree for course requirements.
 */
typedef struct Requirements_struct {
    LinkedList *ands; // 2D Linked List of ANDs, inner are ORs (CNF)
} Requirements;

/**
 * Initializes the object
 * @param reqs an allocated Requirements object
 */
void Requirements_init(Requirements *reqs);

/**
 * parses a line of course requirements, OR or AND specified by the or parameter.
 * if or, all go in one list. Else, each course goes in a separate list.
 * @param reqs the Requirements object
 * @param line the line of course strings split by ','
 * @param or OR if true, AND if false
 */
void Requirements_parseLine(Requirements *reqs, char *line, bool or);

/**
 * Removes a course from the requirements
 * @param reqs the Requirements object
 * @param courseName the course to remove
 */
void Requirements_removeCourse(Requirements *reqs, char *courseName);

/**
 * Finds all courses in reqs but not in courseStrings.
 * That is, performs set difference reqs - courseStrings.
 * Result is in remaining as another Requirements object.
 * @param reqs the Requirements object.
 * @param courseStrings the Tree of courses that have been taken and hence should not be in remaining
 * @param remaining another Requirements object already allocated and initialized
 */
void Requirements_findDifference(Requirements *reqs, BinaryTree *courseStrings, Requirements *remaining);

/**
 * Convert reqs to string representation. ORs will always be separated by ', '
 * ANDs will be separated by the specified delimiter
 * @param reqs the Requirements object
 * @param str an allocated string to store the representation in. Will be overwrittten.
 * @param delim The delimiter to split all courses by.
 */
void Requirements_toString(Requirements *reqs, char *str, char *delim);

/**
 * Comparator used to check if two is in one. One is LinkedList* and two is char*
 * one is the inner level linked list
 * @param one  LinkedList* the linked list to find two in
 * @param two char* the string to look for in the linked list
 * @return 0 if found, -1 otherwise
 */
int Requirements_innerListFindComparator(const void *one, const void *two);

/**
 * Destructor for the inner level of the 2D list. Sometimes not called if the
 * second levels were copied over.
 */
void Requirements_innerListFree(void *);

/**
 * Destructor for Requirements
 * @param reqs the Requirements object
 * @param data_free the destructor for the data type
 */
void Requirements_free(Requirements *reqs, void (*data_free)(void *));

#endif //COURSE_GRAPH_REQUIREMENTS_H
