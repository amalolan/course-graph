#include "Degree.h"


void Degree_init(Degree *degree, char *name) {
    strcpy(degree->name, name);
    degree->reqs = malloc(sizeof(LinkedList));
    LinkedList_init(degree->reqs);
}

// line at least size 2, no \n character
void Degree_parseLine(Degree *degree, char *line) {
    LinkedList *courseLine = malloc(sizeof(LinkedList));
    LinkedList_init(courseLine);
    Course_parseLine(courseLine, line);
    LinkedList_push(degree->reqs, courseLine);
}

int Degree_compareString(const void *one, const void *two) {
    Degree *degree = (Degree *)one;
    char *degreeName = (char *)two;
    return strcmp(degree->name, degreeName);
}

int Degree_compareCourseLineString(const void *one, const void *two) {
    LinkedList *courseLine = (LinkedList*)one;
    char *courseName = (char*) two;
    char *findData = LinkedList_find(courseLine, courseName, string_compare);
    if (findData != NULL) return 0;
    return -1;
}

void Degree_toString(const void *data, char *str) {
    Degree *degree = (Degree *) data;
    strcpy(str, "");
//    sprintf(str, "degree: %s\n", degree->name);
    Node *currLine = degree->reqs->head;
    while (currLine != NULL) {
        Node *currCourse = ((LinkedList *) currLine->data)->head;
        if (((LinkedList *) currLine->data)->size > 1) {
            strcat(str, "OR ");
        }
        while (currCourse != NULL) {
            strcat(str, currCourse->data);
            strcat(str, ", ");
            currCourse = currCourse->next;
        }
        if (((LinkedList *) currLine->data)->size > 0) {
            str[strlen(str) - 2] = 0; // Remove extra , and space
        }
        strcat(str, "\n");
        currLine = currLine->next;
    }
}

void Degree_courseListFree(void *list) {
    LinkedList_free(list, data_free);
    free(list);
}

void Degree_free(void *data) {
    Degree *degree = (Degree *)data;
    LinkedList_free(degree->reqs, Degree_courseListFree);
    free(degree->reqs);
}