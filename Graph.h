#ifndef COURSE_GRAPH_GRAPH_H
#define COURSE_GRAPH_GRAPH_H

#include "Department.h"
#include "Degree.h"

#

typedef struct Graph_struct {
    ArrayList *departments;
    ArrayList *degrees;
} Graph;

void Graph_init(Graph *graph);

void Graph_addDepartment(Graph *graph, Department *department);

void Graph_addDegree(Graph *graph, Degree *degree);

Department *Graph_findDepartmentOfCourse(Graph *graph, char *courseName);

Course *Graph_findCourse(Graph *graph, char *courseName);

void Graph_findDegreesStr(Graph *graph, char *courseName, char *degrees, char* delimiter);

void Graph_describeCourse(Graph *graph, char *courseName);

void Graph_describeDegree(Graph *graph, char *degreeName);

void Graph_describeCourseEffect(Graph *graph, char *courseName);

void Graph_printCourse(Graph *graph, char *courseName);

void Graph_printDegree(Graph *graph, char *degreeName);

void Graph_printDepartment(Graph *graph, char *departmentName);

void Graph_degreeFree(void *data);

void Graph_print(Graph *graph);

void Graph_departmentFree(void *data);

void Graph_free(Graph *graph);

#endif //COURSE_GRAPH_GRAPH_H
