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
    if (line[0] == 'O' && line[1] == 'R') {
        char *str;
        line += 2;
        str = strtok(line, ",");
        while (str != NULL) {
            str++;
            char *courseName = malloc(COURSE_NAME_LEN);
            strcpy(courseName, str);
            LinkedList_push(courseLine, courseName);
            str = strtok(NULL, ",");
        }
    } else {
        char *courseName = malloc(COURSE_NAME_LEN);
        strcpy(courseName, line);
        LinkedList_push(courseLine, courseName);
    }
    LinkedList_push(degree->reqs, courseLine);
}

void Degree_toString(Degree *degree, char *str) {
    sprintf(str, "degree: %s\n", degree->name);
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
        str[strlen(str) - 2] = 0; // Remove extra , and space
        strcat(str, "\n");
        currLine = currLine->next;
    }
}

void CourseList_free(void *list) {
    LinkedList_free(list, data_free);
    free(list);
}

void Degree_free(Degree *degree) {
    LinkedList_free(degree->reqs, CourseList_free);
    free(degree->reqs);
}