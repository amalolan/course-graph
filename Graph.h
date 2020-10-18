#ifndef COURSE_GRAPH_GRAPH_H
#define COURSE_GRAPH_GRAPH_H

#include "Department.h"
#include "Degree.h"


/**
 * Graph stores all the departments and degrees.
 * Also contains all the logic behind the commands the User inputs.
 */
typedef struct Graph_struct {
    ArrayList *departments;
    ArrayList *degrees;
} Graph;

/**
 * Initializes the graph
 * @param graph Graph to initialize.
 */
void Graph_init(Graph *graph);

/**
 * Adds a department to the graph
 * @param graph An initialized graph
 * @param department The department to add.
 */
void Graph_addDepartment(Graph *graph, Department *department);

/**
 * Adds a degree to the graph.
 * @param graph An initialized graph/
 * @param degree An initialized degree.
 */
void Graph_addDegree(Graph *graph, Degree *degree);

/**
 * Finds the course then returns the department it is under.
 * @param graph The graph to look in
 * @param courseName The course to look for
 * @return The department pointer containing that course.
 */
Department *Graph_findDepartmentOfCourse(Graph *graph, char *courseName);

/**
 * Finds a course in the graph and returns a pointer to it.
 * @param graph The graph to look in
 * @param courseName The course to look for
 * @return The pointer to that course if found, else NULL.
 */
Course *Graph_findCourse(Graph *graph, char *courseName);

/**
 * Finds all degrees associated with that course separated by delimiter.
 * @param graph The graph to look in
 * @param courseName  The course to look for
 * @param degrees The string to store the list of degrees in
 * @param delimiter The delimiter between each degree
 */
void Graph_findDegreesStr(Graph *graph, char *courseName, char *degrees, char* delimiter);

/**
 * The course to describe (i.e. print name and prereqs for that course)
 * @param graph Graph containing the course
 * @param courseName  The course to describe
 */
void Graph_describeCourse(Graph *graph, char *courseName);

/**
 * Describes a degree on the cli
 * @param graph The Graph with the degree
 * @param degreeName The degree to describe
 */
void Graph_describeDegree(Graph *graph, char *degreeName);

/**
 * Prints what happens if the course is taken (i.e. courses tthat have that as a prereq)
 * @param graph The graph
 * @param courseName The taken course
 */
void Graph_describeCourseEffect(Graph *graph, char *courseName);

/**
 * Prints a course to cli
 * @param graph Graph containing course
 * @param courseName course to print
 */
void Graph_printCourse(Graph *graph, char *courseName);

/**
 * Prints degree to cli
 * @param graph Graph containing degree
 * @param degreeName degree to print
 */
void Graph_printDegree(Graph *graph, char *degreeName);

/**
 * Prints the department to cli
 * @param graph Graph with the department
 * @param departmentName department to print
 */
void Graph_printDepartment(Graph *graph, char *departmentName);

/**
 * Wrapper to free degrees
 * @param data Degree to free and destruct
 */
void Graph_degreeFree(void *data);

/**
 * Prints graph for debugging
 * @param graph Graph to print
 */
void Graph_print(Graph *graph);

/**
 * Wrapper to free departments
 * @param data Department pointer to free and destruct
 */
void Graph_departmentFree(void *data);

/**
 * Destructs the graph and its elements
 * @param graph Graph to destruct
 */
void Graph_free(Graph *graph);

#endif //COURSE_GRAPH_GRAPH_H
