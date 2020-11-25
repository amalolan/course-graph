#ifndef COURSE_GRAPH_DEGREE_H
#define COURSE_GRAPH_DEGREE_H
#include "Department.h"
#include "BinaryTree.h"
#include "Requirements.h"

/**
 * Represents a Degree. Reqs are stored as 2D Linkedlists of strings.
 */
typedef struct Degree_struct {
    char name[TITLE_LEN];
    Requirements *reqs;
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
 * Removes a course from the degree.
 * @param degree The degree to remove from
 * @param courseName The name of the course to remove (ex. CS 150)
 */
void Degree_removeCourse(Degree *degree, char *courseName);
/**
 * String representation of degree
 * @param degree intialized degree
 * @param str place to store the string rep. Needs memory to be allocated.
 */
void Degree_toString(const void *degree, char *str);


/**
 * Destructor for degree
 * @param data Initialized data to destroy
 */
void Degree_free(void *data);

#endif //COURSE_GRAPH_DEGREE_H
