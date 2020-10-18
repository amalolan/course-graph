#ifndef COURSE_GRAPH_DEGREE_H
#define COURSE_GRAPH_DEGREE_H
#include "Department.h"

/**
 * Represents a Degree. Contains LinkedList<LinkedList<String>> where  the 2D LinkedLists were disjuncts, 1D are the
 * conjuncts.
 */
typedef struct Degree_struct {
    char name[TITLE_LEN];
    LinkedList *reqs;
} Degree;

/**
 * Initializes the struct. Needs pre-allocated data.
 * @param degree pre-allocated pointer to initialize
 * @param name The name of the degree. Will be copied.
 */
void Degree_init(Degree *degree, char *name);

/**
 * Reads a line of course requirements for the degree, and adds courses to the LinkedList.
 * @param degree The initialized degree
 * @param line the line to read without \n
 */
void Degree_parseLine(Degree *degree, char *line);

/**
 * Comparator used to compare a Degree * with char * of degree name
 * @param one Degree * pointer to degree object
 * @param two char * poiner containing name of the degree
 * @return 0 if one->name == degreeName, -1 or 1 otherwise.
 */
int Degree_compareString(const void *one, const void *two);

/**
 * Comparator used to check if two is in one. One is LinkedList* and two is char*
 * @param one  LinkedList* the linked list to find two in
 * @param two char* the string to look for in the linked list
 * @return 0 if found, -1 otherwise
 */
int Degree_compareCourseLineString(const void *one, const void *two);

/**
 * String representation of degree
 * @param degree  intialized degree
 * @param str place to store the string rep. Needs memory to be allocated.
 */
void Degree_toString(const void *degree, char *str);

/**
 * Helper Destructor which destroys degree->reqs
 * @param list The initialized LinkedList to free
 */
void Degree_courseListFree(void *list);

/**
 * Main destructor for Degree
 * @param data Initialized data to destroy
 */
void Degree_free(void *data);

#endif //COURSE_GRAPH_DEGREE_H
