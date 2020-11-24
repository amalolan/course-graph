#include "Test.h"

void testCourse() {
    char line1[] = "OR CS 104, CS 105, CS 106";
    Course c;
    Course_init(&c, "CS 150", "DS and A");
    Course_parsePrereqsLine(c.prereqs, line1);
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
    char line1[] = "OR CS 104, CS 105, CS 106", line2[] = "CS 150";
    Course_init(c1, "CS 150", "DS and A");
    Course_parsePrereqsLine(c1->prereqs, line1);
    Course_init(c2, "CS 205", "Software Engineering");
    Course_parsePrereqsLine(c2->prereqs, line2);
    Course_init(c3, "CS 200", "Computers and Society");
    Course_parsePrereqsLine(c3->prereqs, "");
    Course_init(c4, "CS 202", "Analysis of Algorithms");
    Course_parsePrereqsLine(c4->prereqs, line2);

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



void testTree() {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    BinaryTree_init(tree, string_compare);

    char *f = malloc(10), *b = malloc(10), *a = malloc(10),
    *c = malloc(10), *g = malloc(10), *d = malloc(10), *h = malloc(10);
    strcpy(f, "f");
    strcpy(b, "b");
    strcpy(a, "a");
    strcpy(c, "c");
    strcpy(g, "g");
    strcpy(h, "h");
    strcpy(d, "d");
    BinaryTree_insert(tree, f, NULL);
    BinaryTree_insert(tree, b, NULL);
    BinaryTree_insert(tree, a, NULL);
    BinaryTree_insert(tree, c, NULL);
    BinaryTree_insert(tree, h, NULL);
    BinaryTree_insert(tree, g, NULL);
    BinaryTree_insert(tree, d, NULL);
//    BinaryTree_serialize(tree, list);

    char line[MAX_LINE_LENGTH];
//    ArrayList_toString(list, string_toString, line);
//    printf("%s\n", line);

    BinaryTree_remove(tree, a, free_data);
    BinaryTree_remove(tree, c, free_data);
    BinaryTree_remove(tree, f, free_data);
    f =  malloc(10);
    strcpy(f,"f");
    BinaryTree_remove(tree, f, free_data);
    free(f);
//    TreeNode *node = BinaryTree_find(tree, "g");
//    printf("find g: %s\nleft: %s\nright: %s\n", node->data, node->left->data, node->right->data);

    BinaryTree_toString(tree, string_toString, line);
    printf("%s\n", line);

    BinaryTree_free(tree, free_data);
    free(tree);
}

void tests(int argc, char **argv) {
    testDegree();
    testCourse();
    if (argc > 1) {
        testAndReadDegree(argv[1]);
    }
    testDepartment();
    testGraphDataStructure();
    testTree();
}

void testGraph(Graph *graph) {

    printf("\n%s\n", "Testing c");
    // c
    printf("%s\n", "c CS 150");
    Graph_describeCourse(graph, "CS 150");
    printf("%s\n", "c CS 404");
    Graph_describeCourse(graph, "CS 404");


    printf("\n%s\n", "Testing d");
    // d
    printf("%s\n", "d BS Computer Science");
    Graph_describeDegree(graph, "BS Computer Science");
    printf("%s\n", "d Random Degree");
    Graph_describeDegree(graph, "Random Degree");


    printf("\n%s\n", "Testing s");
    // s
    printf("%s\n", "s CS 150");
    Graph_describeCourseEffect(graph, "CS 150");
    printf("%s\n", "s CS 205");
    Graph_describeCourseEffect(graph, "CS 205");
    printf("%s\n", "s CS 404");
    Graph_describeCourseEffect(graph, "CS 404");

    printf("\n%s\n", "Testing p");
    // p
    printf("%s\n", "p c CS 150");
    Graph_printCourse(graph, "CS 150");
    printf("%s\n", "p c CS 404");
    Graph_printCourse(graph, "CS 404");
    printf("%s\n", "p g AB Computer Science");
    Graph_printDegree(graph, "AB Computer Science");
    printf("%s\n", "p g Random Degree");
    Graph_printDegree(graph, "Random Degree");
    printf("%s\n", "p d Computer Science");
    Graph_printDepartment(graph, "Computer Science");
    printf("%s\n", "p d Random Department");
    Graph_printDepartment(graph, "Random Department");
    printf("%s\n", "p s Alicia Hunter");
    Graph_printStudent(graph, "Alicia Hunter");
    printf("%s\n", "p s Random Name");
    Graph_printStudent(graph, "Random Name");


    printf("\n%s\n", "Testing a");
    //a
    char str[MAX_LINE_LENGTH] = "Computer Science, CS 206, Systems Software, CS 202, CS 203";
    printf("a %s\n", str);
    Graph_addCourse(graph, str);
    strcpy(str, "Computer Science, CS 320, Databases, OR CS 202, CS 205");
    printf("a %s\n", str);
    Graph_addCourse(graph, str);
    // Invalid prereqs are accepted

    printf("%s\n", "p d Computer Science");
    Graph_printDepartment(graph, "Computer Science");

    printf("\n%s\n", "Testing m");
    //m
    printf("%s\n", "m Alicia Hunter");
    Graph_describeDegreeReq(graph, "Alicia Hunter");
    printf("%s\n", "m Random Name");
    Graph_describeDegreeReq(graph, "Random Name");


    printf("\n%s\n", "Testing n");
    //n
    printf("%s\n", "n Alicia Hunter");
    Graph_describeNextDegreeReqs(graph, "Alicia Hunter");
    printf("%s\n", "n Random Name");
    Graph_describeNextDegreeReqs(graph, "Random Name");


    printf("\n%s\n", "Testing q");
    //q
    strcpy(str, "BS Computer Science, CS 105");
    printf("q %s\n", str);
    Graph_removeCourseDegree(graph, str);
    strcpy(str, "BS Computer Science, MATH 162");
    printf("q %s\n", str);
    Graph_removeCourseDegree(graph, str);
    strcpy(str, "AB Computer Science, MATH 182");
    printf("q %s\n", str);
    Graph_removeCourseDegree(graph, str);
    strcpy(str, "BS Computer Science, CS 404");
    printf("q %s\n", str);
    Graph_removeCourseDegree(graph, str);

    printf("\n%s\n", "Testing r");
    //r
    strcpy(str, "Computer Science, CS 150");
    printf("r %s\n", str);
    Graph_removeCourse(graph, str);
    strcpy(str, "Computer Science, CS 404");
    printf("r %s\n", str);
    Graph_removeCourse(graph, str);

    // Prints to ensure deletion was done correctly.
    printf("%s\n", "p c CS 150");
    Graph_printCourse(graph, "CS 150");
    printf("%s\n", "p d Computer Science");
    Graph_printDepartment(graph, "Computer Science");
    printf("%s\n", "p g BS Computer Science");
    Graph_printDegree(graph, "BS Computer Science");
    printf("%s\n", "p g AB Computer Science");
    Graph_printDegree(graph, "AB Computer Science");
    printf("%s\n", "p c CS 203");
    Graph_printCourse(graph, "CS 203");
    printf("%s\n", "s CS 104");
    Graph_describeCourseEffect(graph, "CS 104");
    printf("%s\n", "m Alicia Hunter");
    Graph_describeDegreeReq(graph, "Alicia Hunter");
}