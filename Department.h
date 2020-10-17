#ifndef COURSE_GRAPH_DEPARTMENT_H
#define COURSE_GRAPH_DEPARTMENT_H
#include "LinkedList.h"
#include "ArrayList.h"

typedef struct Course_struct {
    char title[TITLE_LEN];
    char name[COURSE_NAME_LEN];
    LinkedList *prereqs;
} Course;

void Course_init(Course *course, char* title, char *name);

void Course_parseLine(LinkedList *list, char* line);

void Course_toString(Course *course, char* str);

int Course_compareString(const void *one, const void *two);


void Course_free(void *data);

typedef struct Department_struct {
    char name[TITLE_LEN];
    ArrayList *courses;
} Department;

void Department_init(Department *department, char* name);

void Department_addCourse(Department *department, Course *course);

Course *Department_findCourse(Department *department, char *courseName);

void Course_prereqsToString(Course *course, char *str);

void Department_toString(const void *data, char* str);

void Department_courseFree(void *data);

void Department_free(void *data);
#endif //COURSE_GRAPH_DEPARTMENT_H
