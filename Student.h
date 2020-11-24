#ifndef COURSE_GRAPH_STUDENT_H
#define COURSE_GRAPH_STUDENT_H

#include "LinkedList.h"
#include "ArrayList.h"
#include "Course.h"

typedef struct Student_struct {
    char name[TITLE_LEN];
    char degree[TITLE_LEN];
    ArrayList *courses;
} Student;

void Student_init(Student *student, char *name, char *degree);

void Student_toString(const void *student, char *str);
void Student_addCourse(Student *degree, char *courseName);

int Student_compareString(const void *one, const void *two);

void Student_free(void *data);

#endif //COURSE_GRAPH_STUDENT_H
