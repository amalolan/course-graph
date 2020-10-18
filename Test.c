#include "Test.h"

void testCourse() {
    char line1[] = "OR CS 104, CS 105, CS 106";
    Course c;
    Course_init(&c, "CS 150", "DS and A");
    Course_parseLine(c.prereqs, line1);
    char *courseStr = malloc(1000);
    Course_toString(&c, courseStr);
    printf("%s", courseStr);
    Course_free(&c);
    free(courseStr);
}

void testDepartment() {
    printf("Test Department\n");
    Course *c1 = malloc(sizeof(Course)), *c2  = malloc(sizeof(Course)), * c3 = malloc(sizeof(Course)), * c4 = malloc
            (sizeof(Course));
    char line1[] = "OR CS 104, CS 105, CS 106", line2[] = "CS 150", line3[] = "";
    Course_init(c1, "CS 150", "DS and A");
    Course_parseLine(c1->prereqs, line1);
    Course_init(c2, "CS 205", "Software Engineering");
    Course_parseLine(c2->prereqs, line2);
    Course_init(c3, "CS 200", "Computers and Society");
    Course_parseLine(c3->prereqs, "");
    Course_init(c4, "CS 202", "Analysis of Algorithms");
    Course_parseLine(c4->prereqs, line2);

    Department d;
    Department_init(&d, "CS");
    Department_addCourse(&d, c1);
    Department_addCourse(&d, c2);
    Department_addCourse(&d, c3);
    Department_addCourse(&d, c4);
    char *departmentStr = malloc(2000);
    Department_toString(&d, departmentStr);
    printf("%s", departmentStr);
    Department_free(&d);
    free(departmentStr);
}

void testDegree() {
    char line1[] = "OR CS 104, CS 105, CS 106", line2[] = "CS 150", line3[] = "OR MATH 186, MATH 286, MATH 336";
    Degree *d = malloc(sizeof(Degree));
    Degree_init(d, "BA Computer Science");
    Degree_parseLine(d, line1);
    Degree_parseLine(d, line2);
    Degree_parseLine(d, line3);
    char *degreeStr = malloc(strlen(line1) + strlen(line2) + strlen(line3)+100);
    Degree_toString(d, degreeStr);
    printf("%s", degreeStr);
    Degree_free(d);
    free(degreeStr);
    free(d);
}


void testAndReadDegree(char *input) {
    char str[MAX_LINE_LENGTH];
    FILE* fp = fopen(input, "r");
    fgets(str, MAX_LINE_LENGTH, fp);
    fgets(str, MAX_LINE_LENGTH, fp); // Degree Name
    size_t ln = strlen(str)-1;
    if (str[ln] == '\n')
        str[ln] = '\0';
    Degree *d = malloc(sizeof(Degree));
    Degree_init(d, str);
    while (fgets(str, MAX_LINE_LENGTH, fp)) {
        ln = strlen(str)-1;
        if (str[ln] == '\n')
            str[ln] = '\0';
        Degree_parseLine(d, str);
    }
    char *degreeStr = malloc(MAX_LINE_LENGTH * 100);
    Degree_toString(d, degreeStr);
    printf("%s", degreeStr);
    Degree_free(d);
    free(d);
    free(degreeStr);
}


void testGraphDataStructure() {
    Graph *g = malloc(sizeof(Graph));
    Graph_init(g);

    Graph_print(g);
    Graph_free(g);
    free(g);
}

void tests(int argc, char **argv) {
    testDegree();
    testCourse();
    if (argc > 1) {
        testAndReadDegree(argv[1]);
    }
    testDepartment();
    testGraphDataStructure();
}
