#include "InputHandler.h"

/**
 * Loop through the file and read the lines one by one. Use parser function
 * from Degree
 */
Degree *readDegree(FILE *fp) {
    char str[MAX_LINE_LENGTH]; // Definition of MAX_LINE_LENGTH
    fgets(str, MAX_LINE_LENGTH, fp); // Degree Name
    removeNewline(str);
    Degree *degree = malloc(sizeof(Degree));
    Degree_init(degree, str);
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        removeNewline(str);
        if(strlen(str) != 0)
            Degree_parseLine(degree, str);
    }
    return degree;
}

/**
 * Loop through the file. Use parser function from Course
 */
Department *readDepartment(FILE *fp) {
    char str[MAX_LINE_LENGTH],
        courseName[COURSE_NAME_LEN];

    fgets(str, MAX_LINE_LENGTH, fp); // Department Name
    removeNewline(str);
    Department *department = malloc(sizeof(Department));
    Department_init(department, str);
    int count = 0;
    Course *course;
    /**
     * Go through every line of the file.
     */
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        removeNewline(str);
        if (count == 0) {  // Course name
            if(strlen(str) == 0) break;
            strcpy(courseName, str);
        } else if (count == 1) { // Course title
            course = malloc(sizeof(Course));
            Course_init(course, courseName, str);
            Department_addCourse(department, course);
        } else { // Prereqs
            Course_parsePrereqsLine(course, str);
        }
        count++;
        count = count % 3;
    }
    return department;
}

/**
 * Loop through every line. Every line is a single course name so no need to parse.
 */
Student *readStudent(FILE *fp) {
    char str[MAX_LINE_LENGTH],
            studentName[MAX_LINE_LENGTH];; // Definition of MAX_LINE_LENGTH
    fgets(str, MAX_LINE_LENGTH, fp); // Student Name
    removeNewline(str);
    strcpy(studentName, str);
    fgets(str, MAX_LINE_LENGTH, fp); // Degree Name
    removeNewline(str);
    Student *student = malloc(sizeof(Student));
    Student_init(student, studentName, str);
    while (fgets(str, COURSE_NAME_LEN, fp)) {
        removeNewline(str);
        if(strlen(str) != 0)
            Student_addCourse(student, str);
    }
    return student;
}

/**
 * Depending on the value of the first line call the respective function
 * and add it to graph.
 */
void readFile(Graph *graph, char *filePath) {
    char str[MAX_LINE_LENGTH];
    FILE* fp = fopen(filePath, "r");
    fgets(str, MAX_LINE_LENGTH, fp); // DEPARMENT or DEGREE or STUDENT
    if (strcmp(str, "DEPARTMENT\n") == 0) {
        Graph_addDepartment(graph, readDepartment(fp));
    } else if (strcmp(str, "DEGREE\n") == 0)  {
        Graph_addDegree(graph, readDegree(fp));
    } else {
        Graph_addStudent(graph, readStudent(fp));
    }

}


