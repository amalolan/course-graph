#ifndef COURSE_GRAPH_DEPARTMENT_H
#define COURSE_GRAPH_DEPARTMENT_H

#include "LinkedList.h"
#include "BinaryTree.h"
#include "Course.h"

/**
 * Departments are stored in this. Contains BinaryTree of Course objects
 * compared by their names.
 */
typedef struct Department_struct {
    char name[TITLE_LEN];
    BinaryTree *courses;
} Department;

/**
 * Initialized the department. Needs memory to be allocated.
 * @param department the instantiated Department object
 * @param name the department object's name
 */
void Department_init(Department *department, char *name);

/**
 * Adds a course to this department
 * @param department intialized Department object
 * @param course the course object to add
 */
void Department_addCourse(Department *department, Course *course);

/**
 * Converts it to a string representation.
 * str will be overwritten, and needs enough space to be allocated.
 * @param data the Department object
 * @param str the string to write to
 */
void Department_toString(const void *data, char *str);

/**
 * Comparator for a Department object and a name string.
 * Returns 0 if the names match, -1 or 1 otherwise.
 * @param one the Department* object
 * @param two the char* name
 * @return 0 if object->name == name, -1 or 1 otherwise
 */
int Department_compareString(const void *one, const void *two);

/**
 * Destructor wrapper for courses in the department
 * @param data The course to free
 */
void Department_courseFree(void *data);

/**
 * Main destructor for the department.
 * @param data The Department object to destruct.
 */
void Department_free(void *data);

#endif //COURSE_GRAPH_DEPARTMENT_H
