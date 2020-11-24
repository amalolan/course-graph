#include "Test.h"
#include "InputHandler.h"
#include <stdlib.h>

/**
 * Checks for user input and goes to the switch statement for that input.
 * Runs until x is entered
 * @param graph the graph it uses to run on.
 */
void run(Graph *graph) {
    char command;
    char *line = malloc(MAX_LINE_LENGTH), *initialLine = line;
    while (true) {
        fgets(line, MAX_LINE_LENGTH, stdin);
        if (strlen(line) == 0) continue;
        command = line[0];
        if (command == 'x') break;
        line += 2;
        removeNewline(line);
        /**
         * Switches between the different commands.
         */
        switch(command) {
            case 'c':
                Graph_describeCourse(graph, line);
                break;
            case 'd':
                Graph_describeDegree(graph, line);
                break;
            case 's':
                Graph_describeCourseEffect(graph, line);
                break;
            case 'a':
                Graph_addCourse(graph, line);
                break;
            case 'm':
                Graph_describeDegreeReq(graph, line);
                break;
            case 'p':
                command = line[0];
                line += 2;
                switch(command) {
                    case 'c':
                        Graph_printCourse(graph, line);
                        break;
                    case 'd':
                        Graph_printDepartment(graph, line);
                        break;
                    case 'g':
                        Graph_printDegree(graph, line);
                        break;
                    case 's':
                        Graph_printStudent(graph, line);
                        break;
                    default:
                        printf("Invalid Input. Please try again\n");
                        break;
                }
                break;
            default:
                printf("Invalid Input. Please try again\n");
        }
        line = initialLine;
    }
    free(initialLine);
}


/**
 * Main function called from cli
 * @param argc Number of args
 * @param argv Each arg as string
 * @return 0 if no error
 */
int main(int argc, char *argv[]) {
    Graph *graph = malloc(sizeof(Graph));
    Graph_init(graph);
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            readFile(graph, argv[i]);
        }
    }
    run(graph);
    Graph_free(graph);
    free(graph);
    return 0;
}
