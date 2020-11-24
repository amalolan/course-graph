#include "Student.h"

void Student_init(Student *student, char *name, char *degree) {
    strcpy(student->name, name);
    strcpy(student->degree, degree);
    student->courses = malloc(sizeof(BinaryTree));
    BinaryTree_init(student->courses, string_compare);
}

//  no \n character
void Student_addCourse(Student *student, char *line) {
    char *courseName = malloc(COURSE_NAME_LEN);
    strcpy(courseName, line);
    BinaryTree_insert(student->courses, courseName, NULL);
}

int Student_compareString(const void *one, const void *two) {
    Student *student = (Student *)one;
    char * studentName = (char *) two;
    return strcmp(student->name, studentName);
}

void Student_toString(const void *data, char *str) {
    Student *student = (Student *) data;
    sprintf(str, "degree: %s\n", student->degree);
    if (((BinaryTree *) student->courses)->size > 0) {
        ArrayList *list = malloc(sizeof(ArrayList));
        ArrayList_init(list);
        BinaryTree_serialize(student->courses, list);
        strcat(str, "completed: ");
        for (size_t i = 0; i < list->size; i++) {
            char *courseStr = ArrayList_get(list, i);
            strcat(str, courseStr);
            strcat(str, ", ");
        }
        str[strlen(str) - 2] = 0; // Remove extra , and space
        strcat(str, "\n");
        ArrayList_free(list, dont_free);
        free(list);
    }
    else {
        strcat(str, "completed: NONE\n");
    }
}

void Student_free(void *data) {
    Student *student = (Student *)data;
    BinaryTree_free(student->courses, free_data);
    free(student->courses);
    student->courses = NULL;
}