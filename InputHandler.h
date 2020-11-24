#ifndef COURSE_GRAPH_INPUTHANDLER_H
#define COURSE_GRAPH_INPUTHANDLER_H
#include "LinkedList.h"
#include "Graph.h"

/**
 * Reads the degree file and returns a degree object
 * @param fp The Degree FILE
 * @return the degree pointer with space on the heap
 */
Degree* readDegree(FILE *fp);

/**
 * Reads the department file and returns a department object.
 * @param fp The Department FILE
 * @return the department pointer with space on the heap.
 */
Department* readDepartment(FILE *fp);

Student* readStudent(FILE *fp);

/**
 * Reads any file. Calls its respective read function
 * @param g The graph being used to store everything
 * @param filePath The relative filePath to the file.
 */
void readFile(Graph *g, char *filePath);
#endif //COURSE_GRAPH_INPUTHANDLER_H
