#include "InputHandler.h"


Degree *readDegree(FILE *fp) {
    char str[MAX_LINE_LENGTH]; // Definition of MAX_LINE_LENGTH
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
    /**
     * Go through every line of the file.
     */
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        removeNewline(str);
        if (count == 0) {  // Course name
            strcpy(courseName, str);
        } else if (count == 1) { // Course title
            course = malloc(sizeof(Course));
            Course_init(course, courseName, str);
            Department_addCourse(department, course);
        } else { // Prereqs
            Course_parsePrereqsLine(course->prereqs, str);
        }
        count++;
        count = count % 3;
    }
    return department;
}

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
        Student_addCourse(student, str);
    }
    return student;
}

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


