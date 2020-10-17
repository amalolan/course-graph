#include "Graph.h"

void Graph_init(Graph *graph) {
    graph->degrees = malloc(sizeof(ArrayList));
    graph->departments = malloc(sizeof(ArrayList));
    ArrayList_init(graph->degrees);
    ArrayList_init(graph->departments);
}

void Graph_addDepartment(Graph *graph, Department *department) {
    ArrayList_push(graph->departments, department);

}

void Graph_addDegree(Graph *graph, Degree *degree) {
    ArrayList_push(graph->degrees, degree);
}

Course *Graph_findCourseDepartment(Graph *graph, Department *department, char *courseName) {
    Course *course = NULL;
    if (department == NULL) {
        for (size_t i = 0; i < graph->departments->size; i++) {
            department = ArrayList_get(graph->departments, i);
            course = ArrayList_find(department->courses, courseName, Course_compareString);
            if (course != NULL) {
                return course;
            }
        }
        department = NULL;
        return course;
    } else {
        return ArrayList_find(department->courses, courseName, Course_compareString);
    }
}

Degree *Graph_findDegree(Graph *graph, char *degreeName) {
    Degree *degree = NULL;
    for (size_t i = 0; i < graph->degrees->size; i++) {
        degree = ArrayList_get(graph->degrees, i);

    }
}

Department *Graph_findDepartment(Graph *graph, char *departmentName);

char **Graph_findDegreesStrWithCourse(Graph *graph, char *courseName) {
    return NULL;
}

void Graph_describeCourse(Graph *graph, char *courseName) {
    Department *department = NULL;
    Course *course = Graph_findCourseDepartment(graph, department, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    printf("%s\n", course->title);
    char line[MAX_LINE_LENGTH];
    Course_prereqsToString(course, line);
    printf("%s\n", line);
    // if course != null, print title and prereqs string
}

void Graph_describeDegree(Graph *graph, char *degreeName) {
    printf("In describe degree %s\n", degreeName);
    // look through degrees
    // if degree 1= null, print courses
}

void Graph_describeCourseEffect(Graph *graph, char *courseName) {
    // find course through depts
    // if it exists, for every other course check which has it as a prereq and print thtat list
    // find degrees with this course in it
    printf("In course effect %s\n", courseName);
}

void Graph_printCourse(Graph *graph, char *courseName) {
    // find course through depts
    // if not null, print dept,
    // find degrees with this course in it
    // printt prereqs listt
    printf("In print course %s\n", courseName);
}

void Graph_printDegree(Graph *graph, char *degreeName) {
    // find degree through depts
    // print degree: name
    // print courses
    printf("In print degree %s\n", degreeName);
}

void Graph_printDepartment(Graph *graph, char *departmentName) {
    // find department with the same name
    printf("In print department %s\n", departmentName);
}

void Graph_print(Graph *graph) {
    printf("Printing Graph.\n");
    char str[MAX_LINE_LENGTH * 256];
    ArrayList_toString(graph->departments, Department_toString, str);
    printf("Departments.\n");
    printf("%s", str);
    ArrayList_toString(graph->degrees, Degree_toString, str);
    printf("Degrees.\n");
    printf("%s", str);
}

void Graph_free(Graph *graph) {
    ArrayList_free(graph->departments, Graph_departmentFree);
    ArrayList_free(graph->degrees, Graph_degreeFree);
    free(graph->departments);
    free(graph->degrees);
    graph->degrees = NULL;
    graph->departments = NULL;
}

void Graph_departmentFree(void *data) {
    Department_free(data);
    free(data);
}

void Graph_degreeFree(void *data) {
    Degree_free(data);
    free(data);
}