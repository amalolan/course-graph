#include "Department.h"

void Course_init(Course *course, char *name, char *title) {
    strcpy(course->name, name);
    strcpy(course->title, title);
    course->prereqs = malloc(sizeof(LinkedList));
    LinkedList_init(course->prereqs);
}

void Course_parseLine(Course *course, char* line) {
    parseCoursesLine(course->prereqs, line);
}

void Course_toString(Course *course, char* str) {
    sprintf(str, "%s\n", course->title);
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

void Course_free(Course *course)  {
    LinkedList_free(course->prereqs, data_free);
    free(course->prereqs);
}