#ifndef COURSE_GRAPH_INPUTHANDLER_H
#define COURSE_GRAPH_INPUTHANDLER_H
#include "LinkedList.h"
#include "Graph.h"

Degree* readDegree(FILE *fp);
Department* readDepartment(FILE *fp);
void readFile(Graph *g, char *filePath);
#endif //COURSE_GRAPH_INPUTHANDLER_H
