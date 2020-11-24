#include "Degree.h"
#include "BinaryTree.h"


void Degree_init(Degree *degree, char *name) {
    strcpy(degree->name, name);
    degree->reqs = malloc(sizeof(Requirements));
    Requirements_init(degree->reqs);
}

// line at least size 2, no \n character
void Degree_parseLine(Degree *degree, char *line) {
    if (strlen(line) > 3) {
        bool or = (line[0] == 'O' && line[1] == 'R' && line[2] == ' ');
        if (or) line += 3;
        Requirements_parseLine(degree->reqs, line, or);
    }
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
    if (findData == NULL) return -1;
    return 0;
}


void Degree_removeCourse(Degree *degree, char *courseName) {
    Requirements_removeCourse(degree->reqs, courseName);
}


void Degree_toString(const void *data, char *str) {
    Degree *degree = (Degree *) data;
    char delim[] = "\n";
    Requirements_toString(degree->reqs, str, delim);
}

void Degree_free(void *data) {
    Degree *degree = (Degree *)data;
    Requirements_free(degree->reqs, Requirements_innerListFree);
    free(degree->reqs);
    degree->reqs = NULL;
}