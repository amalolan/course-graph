#ifndef COURSE_GRAPH_STUDENT_H
#define COURSE_GRAPH_STUDENT_H

#include "LinkedList.h"
#include "BinaryTree.h"
#include "Course.h"

/**
 * Student object with name degree and a tree of courses that have been completed.
 * Tree contains strings only.
 */
typedef struct Student_struct {
    char name[TITLE_LEN];
    char degree[TITLE_LEN];
    BinaryTree *courses;
} Student;

/**
 * Initializes student
 * @param student the student object with allocated memory
 * @param name the name of the student
 * @param degree the degree of the student
 */
void Student_init(Student *student, char *name, char *degree);

/**
 * Converts to a string representation.
 * @param student the student to convert
 * @param str the string to store it in. Needs to be allocated and will be overwritten.
 */
void Student_toString(const void *student, char *str);

/**
 * Adds a course to the student's tree.
 * @param student the student to add to
 * @param courseName the course's name to add
 */
void Student_addCourse(Student *student, char *courseName);

/**
 * Comparator for Student * and char *
 * @param one Student * object
 * @param two char * name
 * @return 0 if object->name == name, -1 or 1 otherwise
 */
int Student_compareString(const void *one, const void *two);

/**
 * Destructor for student
 * @param data the student object to free
 */
void Student_free(void *data);

#endif //COURSE_GRAPH_STUDENT_H
