#include "Degree.h"
#include "BinaryTree.h"

/**
 * Copy string and initialize Requirements
 */
void Degree_init(Degree *degree, char *name) {
    strcpy(degree->name, name);
    degree->reqs = malloc(sizeof(Requirements));
    Requirements_init(degree->reqs);
}

/**
 * Remove the starting 'OR ', if it exists and calls it with a true or parameter.
 */
void Degree_parseLine(Degree *degree, char *line) {
    if (strlen(line) > 3) {
        bool or = (line[0] == 'O' && line[1] == 'R' && line[2] == ' ');
        if (or) line += 3;
        Requirements_parseLine(degree->reqs, line, or);
    }
}

/**
 * Compares a degree struct to the name
 */
int Degree_compareString(const void *one, const void *two) {
    Degree *degree = (Degree *)one;
    char *degreeName = (char *)two;
    return strcmp(degree->name, degreeName);
}

/**
 * Removes by calling Requirements_removeCourse()
 */
void Degree_removeCourse(Degree *degree, char *courseName) {
    Requirements_removeCourse(degree->reqs, courseName);
}

/**
 * Convert to string. Used for printing Degree.
 * Rewrites str and writes each conjunct in a new line.
 */
void Degree_toString(const void *data, char *str) {
    Degree *degree = (Degree *) data;
    char delim[] = "\n";
    Requirements_toString(degree->reqs, str, delim);
}

/**
 * Destructs requirements first then frees reqs.
 * Requirements_innerListFree allows both dimensions to be freed.
 */
void Degree_free(void *data) {
    Degree *degree = (Degree *)data;
    Requirements_free(degree->reqs, Requirements_innerListFree);
    free(degree->reqs);
    degree->reqs = NULL;
}