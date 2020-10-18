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

Department *Graph_findDepartmentOfCourse(Graph *graph, char *courseName) {
    for (size_t i = 0; i < graph->departments->size; i++) {
        Department *department = ArrayList_get(graph->departments, i);
        Course *course = ArrayList_find(department->courses, courseName, Course_compareString);
        if (course != NULL) {
            return department;
        }
    }
    return NULL;
}

Course *Graph_findCourse(Graph *graph, char *courseName) {
    for (size_t i = 0; i < graph->departments->size; i++) {
        Department *department = ArrayList_get(graph->departments, i);
        Course *course = ArrayList_find(department->courses, courseName, Course_compareString);
        if (course != NULL) {
            return course;
        }
    }
    return NULL;
}


void Graph_findDegreesStr(Graph *graph, char *courseName, char *degrees, char* delimiter) {
    Course *course = NULL;
    strcpy(degrees, "");
    Degree *degree;
    bool first = true;
    for (size_t i = 0; i < graph->degrees->size; i++) {
        degree = ArrayList_get(graph->degrees, i);
        course = LinkedList_find(degree->reqs, courseName, Degree_compareCourseLineString);
        if (course != NULL) {
            if (!first) {
                strcat(degrees, delimiter);
            }
            strcat(degrees, degree->name);
            first = false;
        }
    }
}

void Graph_describeCourse(Graph *graph, char *courseName) {
    Course *course = Graph_findCourse(graph, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    printf("%s\n", course->title);
    char line[MAX_LINE_LENGTH];
    Course_prereqsToString(course, line);
    printf("%s", line);
    // if course != null, print title and prereqs string
}

void Graph_describeDegree(Graph *graph, char *degreeName) {
    Degree *degree = ArrayList_find(graph->degrees, degreeName, Degree_compareString);
    if (degree == NULL)  {
        printf("NOT FOUND\n");
        return;
    }
    char courses[LIST_LENGTH]; // List of Max line lengths
    Degree_toString(degree, courses);
    printf("%s", courses);
    // look through degrees
    // if degree 1= null, print courses
}

void Graph_describeCourseEffect(Graph *graph, char *courseName) {
    // find course through depts
    // if it exists, for every other course check which has it as a prereq and print thtat list
    // find degrees with this course in it
    Course *course = Graph_findCourse(graph, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    Department *department;
    bool first = true;
    for (size_t i = 0; i < graph->departments->size; i++) {
        department = ArrayList_get(graph->departments, i);
        for (size_t j = 0; j < department->courses->size; j++) {
            Course *parent = ArrayList_get(department->courses, j);
            Course *foundPrereq = LinkedList_find(parent->prereqs, course->name, string_compare);
            if (foundPrereq != NULL) {
                if (!first) {
                    printf(", ");
                }
                first = false;
                printf("%s", parent->name);
            }
        }
//        Course *parent = ArrayList_find(department->courses, course, Course_comparePrereq);
//        while (parent != NULL) {
//
//            parent = ArrayList_find(department->courses, course, Course_comparePrereq);
//        }
    }
    if (first == true) printf("No courses have %s as a pre-requisite", courseName);
    // Many courses could have it as prereq
    char str[MAX_LINE_LENGTH * 2], delim[] = "\n";
    Graph_findDegreesStr(graph, courseName, str, delim);
    printf("\n%s\n", str);
}

void Graph_printCourse(Graph *graph, char *courseName) {
    // find course through depts
    // if not null, print dept,
    // find degrees with this course in it
    // printt prereqs listt
    Course *course = Graph_findCourse(graph, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    Department *department = Graph_findDepartmentOfCourse(graph, courseName);
    printf("department: %s\n", department->name);
    char str[MAX_LINE_LENGTH * 2], delim[] = ", ";
    Graph_findDegreesStr(graph, courseName, str, delim);
    printf("degree: %s\n", str);
    Course_prereqsToString(course, str);
    if (strlen(str) == 1) strcpy(str, "NONE\n");
    printf("pre-requisites: %s", str);

}

void Graph_printDegree(Graph *graph, char *degreeName) {
    // find degree through depts
    // print degree: name
    // print courses
    Degree *degree = ArrayList_find(graph->degrees, degreeName, Degree_compareString);
    if (degree == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    char str[LIST_LENGTH]; // List of max line lengths
    Degree_toString(degree, str);
    printf("%s", str);
}

void Graph_printDepartment(Graph *graph, char *departmentName) {
    // find department with the same name
    Department *department = ArrayList_find(graph->departments, departmentName, Department_compareString);
    if (department == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    char str[2 * LIST_LENGTH]; // List of  2* max line lengths
    Department_toString(department, str);
    printf("%s", str);
}

void Graph_print(Graph *graph) {
    printf("Printing Graph.\n");
    char *str = malloc(32 * LIST_LENGTH); // Debugging, can include every file read 256KB
    ArrayList_toString(graph->departments, Department_toString, str);
    printf("Departments.\n");
    printf("%s", str);
    ArrayList_toString(graph->degrees, Degree_toString, str);
    printf("Degrees.\n");
    printf("%s", str);
    free(str);
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