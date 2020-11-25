#ifndef COURSE_GRAPH_COURSE_H
#define COURSE_GRAPH_COURSE_H

#include "LinkedList.h"
#include "Requirements.h"

/**
 * Stores a course along with a string of prereqs as a Requirements struct.
 * Prereqs are stores as 2d linked lists of strings.
 * Part of Department.
 */
typedef struct Course_struct {
    char title[TITLE_LEN];
    char name[COURSE_NAME_LEN];
    Requirements *prereqs;
} Course;

/**
 * Initializes the course. Assumes memory has been allocated.
 * Allocates memory for the Requirements.
 * @param course The course being initialized. Mem must be allocated.
 * @param title The title of the course (ex 'Software Engineering').
 * @param name The course name (ex. 'CS 205')
 */
void Course_init(Course *course, char *title, char *name);

/**
 * Reads a line containing pre-reqs and appends to the requirements by calling
 * the requirement's parseLine function.
 * @param course Initialized list
 * @param line Line of prereqs starting without whitespace and without \n at the end
 */
void Course_parsePrereqsLine(Course *course, char *line);

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
 * Comparator for comparing two Course oobjects
 * @param one Course * course objectt
 * @param two Course * second course objectt
 * @return 0 if one->name == two->name, else -1 or 1.
 */
int Course_compareCourse(const void *one, const void*two);


/**
 * Destructs the course object. Frees linked list and associated data.
 * @param data
 */
void Course_free(void *data);


#endif //COURSE_GRAPH_COURSE_H
