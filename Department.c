#include "Department.h"

void Department_init(Department *department, char *name) {
    strcpy(department->name, name);
    department->courses = malloc(sizeof(BinaryTree));
    BinaryTree_init(department->courses, Course_compareString);
}

void Department_addCourse(Department *department, Course *course) {
    BinaryTree_insert(department->courses, course, Course_compareCourse);
}

void Department_toString(const void *data, char *str) {
    Department *department = (Department *) data;
    sprintf(str, "department: %s\n", department->name);
    char courseStr[MAX_LINE_LENGTH * 2]; // Times 2 to account for Title and Name
    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    BinaryTree_serialize(department->courses, list);
    for (size_t i = 0; i < department->courses->size; i++) {
        Course *course = ArrayList_get(list, i);
        Course_toString(course, courseStr);
        strcat(str, courseStr);
    }
    ArrayList_free(list, dont_free);
    free(list);
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
    BinaryTree_free(department->courses, Department_courseFree);
    free(department->courses);
    department->courses = NULL;
}
