#ifndef COURSE_GRAPH_TEST_H
#define COURSE_GRAPH_TEST_H

#include <stdio.h>
#include "LinkedList.h"
#include "ArrayList.h"
#include "Degree.h"
#include "Graph.h"
#include "InputHandler.h"
#include "BinaryTree.h"
/**
 * tests the degree struct
 */
void testDegree();

/**
 * tests the course struct
 */
void testCourse();

/**
 * tests the department struct
 */
void testDepartment();

/**
 * tests Graph
 */
void testGraphDataStructure();

/**
 * reads degree and tests
 * @param filepath  filepath of the degree file to test
 */
void testAndReadDegree(char *filepath);

/**
 * tests all graph methods
 * @param graph An initialized graph instance
 */
void testGraph(Graph *graph);

/**
 * tests the binary tree implementation
 */
void testTree();
/**
 * runs all tests
 * @param argc  argc from main
 * @param argv  argv from main
 */
void tests(int argc, char **argv);

#endif //COURSE_GRAPH_TEST_H
