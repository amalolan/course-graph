#include "Department.h"

void Course_init(Course *course, char *name, char *title) {
    strcpy(course->name, name);
    strcpy(course->title, title);
    course->prereqs = malloc(sizeof(LinkedList));
    LinkedList_init(course->prereqs);
}

// Initialized list and line without \n
void Course_parseLine(LinkedList *list, char *line) {
    if (list == NULL) return;
    if (strlen(line) <= 2) return;
    if (line[0] == 'O' && line[1] == 'R') {
        char *str;
        line += 2;
        str = strtok(line, ",");
        while (str != NULL) {
            str++;
            char *courseName = malloc(TITLE_LEN);
            strcpy(courseName, str);
            LinkedList_push(list, courseName);
            str = strtok(NULL, ",");
        }
    } else {
        char *courseName = malloc(TITLE_LEN);
        strcpy(courseName, line);
        LinkedList_push(list, courseName);
    }
}

void Course_prereqsToString(Course *course, char *str) {
    sprintf(str, "");
    Node *curr = course->prereqs->head;
    if (course->prereqs->size > 1) {
        strcat(str, "OR ");
    }
    while (curr != NULL) {
        strcat(str, curr->data);
        strcat(str, ", ");
        curr = curr->next;
    }
    if (course->prereqs->size > 0) {
        str[strlen(str) - 2] = 0; // Remove extra , and space
    }
    strcat(str, "\n");
}

void Course_toString(Course *course, char *str) {
    sprintf(str, "%s\n", course->name);
    strcat(str, course->title);
    strcat(str, "\n");
    char prereqsString[MAX_LINE_LENGTH];
    Course_prereqsToString(course, prereqsString);
    strcat(str, prereqsString);
}

int Course_compareString(const void *one, const void*two) {
    Course *course = (Course *) one;
    char *courseName = (char *) two;
    return strcmp(course->name, courseName);
}

int Course_compare(const void*one, const void*two) {
    Course *courseOne = (Course *) one;
    Course *courseTwo = (Course *) two;
    return strcmp(courseOne->name, courseTwo->name);
}


//int Course_comparePrereq(const void*one, const void*two) {
//    Course *course = (Course *) one;
//    Course *prereq = (Course *) two;
//    Course *foundPrereq = LinkedList_find(course->prereqs, prereq->name, string_compare);
//    if (foundPrereq != NULL) return 0;
//    return -1;
//}

void Course_free(void *data) {
    Course *course = (Course *) data;
    LinkedList_free(course->prereqs, data_free);
    free(course->prereqs);
    course->prereqs = NULL;
}

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
    char courseStr[MAX_LINE_LENGTH * 2];
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
