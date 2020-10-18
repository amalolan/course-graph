#ifndef COURSE_GRAPH_COURSE_H
#define COURSE_GRAPH_COURSE_H

#include "LinkedList.h"

/**
 * Stores a course along with a string of prereqs as LinkedList.
 * Part of Department.
 */
typedef struct Course_struct {
    char title[TITLE_LEN];
    char name[COURSE_NAME_LEN];
    LinkedList *prereqs;
} Course;

/**
 * Initializes the course. Assumes memory has been allocated.
 * Allocates memory for the LinkedList.
 * @param course The course being initialized. Mem must be allocated.
 * @param title The title of the course (ex 'Software Engineering').
 * @param name The course name (ex. 'CS 205')
 */
void Course_init(Course *course, char *title, char *name);

/**
 * Reads a line containing pre-reqs and appends to linked list
 * @param list Initialized list
 * @param line Line of prereqs starting without whitespace and without \n at the end
 */
void Course_parseLine(LinkedList *list, char *line);

/**
 * Provides string representation of Course
 * @param course Initialized course
 * @param str The string to store it in. Needs to be allocated already.
 */
void Course_toString(Course *course, char *str);

/**
 * Comparator for comparing a Course object and a courseName char *
 * @param one Course * course object
 * @param two char * course name
 * @return 0 if one->name == two, else -1 or 1.
 */
int Course_compareString(const void *one, const void *two);

/**
 * Converts prereqs LinkedList to a single line of strings
 * @param course The initialized course
 * @param str "\n" if no prereqs, else list of prereqs as str.
 */
void Course_prereqsToString(Course *course, char *str);

/**
 * Destructs the course object. Frees linked list and associated data.
 * @param data
 */
void Course_free(void *data);


#endif //COURSE_GRAPH_COURSE_H
