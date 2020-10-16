#include "Parser.h"

// Initialized list and line without \n
void parseCoursesLine(LinkedList *list, char* line) {
    if (list == NULL) return;
    if (strlen(line) <= 2) return;
    if (line[0] == 'O' && line[1] == 'R') {
        char *str;
        line += 2;
        str = strtok(line, ",");
        while (str != NULL) {
            str++;
            char *courseName = malloc(COURSE_NAME_LEN);
            strcpy(courseName, str);
            LinkedList_push(list, courseName);
            str = strtok(NULL, ",");
        }
    } else {
        char *courseName = malloc(COURSE_NAME_LEN);
        strcpy(courseName, line);
        LinkedList_push(list, courseName);
    }
}