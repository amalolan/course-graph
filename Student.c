#include "Student.h"

void Student_init(Student *student, char *name, char *degree) {
    strcpy(student->name, name);
    strcpy(student->degree, degree);
    student->courses = malloc(sizeof(ArrayList));
    ArrayList_init(student->courses);
}

//  no \n character
void Student_addCourse(Student *student, char *line) {
    char *courseName = malloc(COURSE_NAME_LEN);
    strcpy(courseName, line);
    ArrayList_push(student->courses, courseName);
}

int Student_compareString(const void *one, const void *two) {
    Student *student = (Student *)one;
    char * studentName = (char *) two;
    return strcmp(student->name, studentName);
}

void Student_toString(const void *data, char *str) {
    Student *student = (Student *) data;
    sprintf(str, "degree: %s\n", student->degree);
    if (((ArrayList *) student->courses)->size > 0) {
        strcat(str, "completed: ");
        for (size_t i = 0; i < student->courses->size; i++) {
            char *courseStr = ArrayList_get(student->courses, i);
            strcat(str, courseStr);
            strcat(str, ", ");
        }
        str[strlen(str) - 2] = 0; // Remove extra , and space
        strcat(str, "\n");
    }
    else {
        strcat(str, "completed: NONE\n");
    }
}

void Student_free(void *data) {
    Student *student = (Student *)data;
    ArrayList_free(student->courses, data_free);
    free(student->courses);
    student->courses = NULL;
}