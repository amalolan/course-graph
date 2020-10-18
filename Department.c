#include "Department.h"

void Department_init(Department *department, char *name) {
    strcpy(department->name, name);
    department->courses = malloc(sizeof(ArrayList));
    ArrayList_init(department->courses);
}

void Department_addCourse(Department *department, Course *course) {
    ArrayList_push(department->courses, course);
}

void Department_toString(const void *data, char *str) {
    Department *department = (Department *) data;
    sprintf(str, "department: %s\n", department->name);
    char courseStr[MAX_LINE_LENGTH * 2]; // Times 2 to account for Title and Name
    for (size_t i = 0; i < department->courses->size; i++) {
        Course *course = ArrayList_get(department->courses, i);
        Course_toString(course, courseStr);
        strcat(str, courseStr);
    }
}

int Department_compareString(const void *one, const void *two) {
    Department *department = (Department *)one;
    char * departmentName = (char *) two;
    return strcmp(department->name, departmentName);
}



void Department_courseFree(void *data) {
    Course *course = (Course *) data;
    Course_free(data);
    free(course);
}

void Department_free(void *data) {
    Department *department = (Department *) data;
    ArrayList_free(department->courses, Department_courseFree);
    free(department->courses);
}
