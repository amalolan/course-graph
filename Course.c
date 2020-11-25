#include "Course.h"


/**
 * Copy over the strings and initialize prereqs
 */
void Course_init(Course *course, char *name, char *title) {
    strcpy(course->name, name);
    strcpy(course->title, title);
    course->prereqs = malloc(sizeof(Requirements));
    Requirements_init(course->prereqs);
}

/**
 * Line doesn't contain \n but may start with OR.
 * If there's an OR, its a disjunct, else it is implicitly a conjunct.
 * Call the Requirements_parseLine() based on that variation.
 */
void Course_parsePrereqsLine(Course *course, char *line) {
    if (strlen(line) > 3) {
        bool or = (line[0] == 'O' && line[1] == 'R' && line[2] == ' ');
        if (or) line += 3; // Increment by 3 to get rid of the 'OR '
        Requirements_parseLine(course->prereqs, line, or);
    }
}

/**
 * Convert the course to a string representation.
 * Used to print out departments. Convert prereqs to string using Requirements_toString
 */
void Course_toString(Course *course, char *str) {
    sprintf(str, "%s\n", course->name);
    strcat(str, course->title);
    strcat(str, "\n");
    char prereqsString[MAX_LINE_LENGTH], delim[]=", "; // By definition, max line length is the CSV of prereqs
    Requirements_toString(course->prereqs, prereqsString, delim);
    strcat(str, prereqsString);
    strcat(str, "\n");
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
/**
 * @param data
 * Destructor for Course. Free the requirements, then free the prereqs variable.
 * Requirements_innerListFree allows both dimensions to be freed.
 */
void Course_free(void *data) {
    Course *course = (Course *) data;
    Requirements_free(course->prereqs, Requirements_innerListFree);
    free(course->prereqs);
    course->prereqs = NULL;
}
