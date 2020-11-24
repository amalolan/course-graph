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
    Course_parsePrereqsLine(courseLine, line);
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

void Degree_removeCourse(Degree *degree, char *courseName) {
    Node *currLine = degree->reqs->head;
    while (currLine != NULL) {
        LinkedList *courseList = (LinkedList *) currLine->data;
        if (LinkedList_remove(courseList, courseName, string_compare, data_free)) {
            if (courseList->size == 0) {
                LinkedList_remove(degree->reqs, courseList, direct_compare, data_free);
            }
            return;
        }
        currLine = currLine->next;
    }
}


void Degree_findReqsDifference(Degree *degree, ArrayList *courseStrings, LinkedList *reqs) {
    Node *currLine = degree->reqs->head;
    /**
     * each currLine is a LinkedList. The loop then looks again at each element.
     */
    while (currLine != NULL) {
        LinkedList *courseList = (LinkedList *) currLine->data;
        Node *currCourse = courseList->head;
        bool found = false;
        while (currCourse != NULL) {
            // TODO: Change to Binary Tree
            if (ArrayList_find(courseStrings, currCourse->data, string_compare)) {
                found = true;
                break;
            }
            currCourse = currCourse->next;
        }
        if (!found) {
            LinkedList_push(reqs, courseList);
        }
        currLine = currLine->next;
    }
}

void Degree_reqsToString(LinkedList *reqs, char *str) {
    strcpy(str, "");
    Node *currLine = reqs->head;
    /**
     * each currLine is a LinkedList. The loop then looks again at each elemen.
     */
    while (currLine != NULL) {
        LinkedList *courseList = (LinkedList *) currLine->data;
        Node *currCourse = courseList->head;
        if (courseList->size > 1) {
            strcat(str, "OR ");
        }
        while (currCourse != NULL) {
            strcat(str, currCourse->data);
            strcat(str, ", ");
            currCourse = currCourse->next;
        }
        if (courseList->size > 0) {
            str[strlen(str) - 2] = 0; // Remove extra , and space
        }
        strcat(str, "\n");
        currLine = currLine->next;
    }
}

void Degree_toString(const void *data, char *str) {
    Degree *degree = (Degree *) data;
    Degree_reqsToString(degree->reqs, str);
}

void Degree_courseListFree(void *list) {
    LinkedList_free(list, data_free);
    free(list);
}

void Degree_free(void *data) {
    Degree *degree = (Degree *)data;
    LinkedList_free(degree->reqs, Degree_courseListFree);
    free(degree->reqs);
    degree->reqs = NULL;
}