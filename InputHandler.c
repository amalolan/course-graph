#include "InputHandler.h"


Degree *readDegree(FILE *fp) {
    char str[MAX_LINE_LENGTH]; // Definition
    fgets(str, MAX_LINE_LENGTH, fp); // Degree Name
    removeNewline(str);
    Degree *degree = malloc(sizeof(Degree));
    Degree_init(degree, str);
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        removeNewline(str);
        Degree_parseLine(degree, str);
    }
    return degree;
}

Department *readDepartment(FILE *fp) {
    char str[MAX_LINE_LENGTH],
        courseName[COURSE_NAME_LEN];

    fgets(str, MAX_LINE_LENGTH, fp); // Department Name
    removeNewline(str);
    Department *department = malloc(sizeof(Department));
    Department_init(department, str);
    int count = 0;
    Course *course;
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        removeNewline(str);
        if (count == 0) {  // Course name
            strcpy(courseName, str);
        } else if (count == 1) { // Course title
            course = malloc(sizeof(Course));
            Course_init(course, courseName, str);
            Department_addCourse(department, course);
        } else { // Prereqs
            Course_parseLine(course->prereqs, str);
        }
        count++;
        count = count % 3;
    }
    return department;
}

void readFile(Graph *graph, char *filePath) {
    char str[MAX_LINE_LENGTH];
    FILE* fp = fopen(filePath, "r");
    fgets(str, MAX_LINE_LENGTH, fp); // DEPARMENT
    if (strcmp(str, "DEPARTMENT\n") == 0) {
        Graph_addDepartment(graph, readDepartment(fp));
    } else {
        Graph_addDegree(graph, readDegree(fp));
    }

}


