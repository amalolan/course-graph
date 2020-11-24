#ifndef COURSE_GRAPH_DEPARTMENT_H
#define COURSE_GRAPH_DEPARTMENT_H

#include "LinkedList.h"
#include "BinaryTree.h"
#include "Course.h"

/**
 * Departments are stored in this. Contains ArrayList of Course objects.
 */
typedef struct Department_struct {
    char name[TITLE_LEN];
    BinaryTree *courses;
} Department;

/**
 * Initialized the department. Needs memory to be allocated.
 * @param department
 * @param name
 */
void Department_init(Department *department, char *name);

void Department_addCourse(Department *department, Course *course);

void Department_toString(const void *data, char *str);

int Department_compareString(const void *one, const void *two);

void Department_courseFree(void *data);

void Department_free(void *data);

#endif //COURSE_GRAPH_DEPARTMENT_H
