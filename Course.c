#include "Course.h"


void Course_init(Course *course, char *name, char *title) {
    strcpy(course->name, name);
    strcpy(course->title, title);
    course->prereqs = malloc(sizeof(LinkedList));
    LinkedList_init(course->prereqs);
}

// Initialized list and line without \n
void Course_parsePrereqsLine(LinkedList *list, char *line) {
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
    char prereqsString[MAX_LINE_LENGTH]; // By definition, max line length is the CSV of prereqs
    Course_prereqsToString(course, prereqsString);
    strcat(str, prereqsString);
}

int Course_compareString(const void *one, const void*two) {
    Course *course = (Course *) one;
    char *courseName = (char *) two;
    return strcmp(course->name, courseName);
}

int Course_compareCourse(const void *one, const void*two) {
    Course *courseOne = (Course *) one;
    Course *courseTwo = (Course *) two;
    return strcmp(courseOne->name, courseTwo->name);
}

void Course_free(void *data) {
    Course *course = (Course *) data;
    LinkedList_free(course->prereqs, free_data);
    free(course->prereqs);
    course->prereqs = NULL;
}
