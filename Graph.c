#include "Graph.h"

/**
 * Initialize all arraylists.
 */
void Graph_init(Graph *graph) {
    graph->degrees = malloc(sizeof(ArrayList));
    graph->departments = malloc(sizeof(ArrayList));
    graph->students = malloc(sizeof(ArrayList));
    ArrayList_init(graph->degrees);
    ArrayList_init(graph->departments);
    ArrayList_init(graph->students);
}

void Graph_addDepartment(Graph *graph, Department *department) {
    ArrayList_push(graph->departments, department);

}

void Graph_addDegree(Graph *graph, Degree *degree) {
    ArrayList_push(graph->degrees, degree);
}

void Graph_addStudent(Graph *graph, Student *student) {
    ArrayList_push(graph->students, student);
}

/**
 * The line contains no \n
 *
 * First get the department name, check for existence. Then course name and title.
 * Finally, use Course_parsePrereqsLine() to parse the prereqs.
 */
void Graph_addCourse(Graph *graph, char *line) {
    if (line == NULL) return;
    // Store a copy cause strtok changes the line
    char courseName[COURSE_NAME_LEN], lineCopy[MAX_LINE_LENGTH];
    strcpy(lineCopy, line);
    Department *department;
    Course *course;
    char *str = strtok(lineCopy, ",");
    /**
     * Runs 4 times only, cause 4 substrings are used
     */
    for (int count = 0; count < 4; count++) {
        if (str == NULL) {
            printf("ERROR ADDING COURSE\n");
            return;
        }
        if (count == 0) {     // First, parse department
            department = ArrayList_find(graph->departments, str, Department_compareString);
            if (department == NULL) {
                printf("CANNOT ADD COURSE. DEPARTMENT NOT FOUND\n");
                return;
            }
        } else if (count == 1) { // course name
            str++;
            strcpy(courseName, str);
        } else if (count == 2) { // course title
            str++;
            course = malloc(sizeof(Course));
            Course_init(course, courseName, str);
            Department_addCourse(department, course);
        } else {
            /**
             * Now, the rest are the prereqs. To find where it starts, strtok cannot be used.
             * We need to count exactly how many chars the past 3 substrings took
             * and go forward in line by that amount.
             */
            line += strlen(department->name)  + strlen(courseName) +
                    strlen(course->title) + 6;
            Course_parsePrereqsLine(course, line);
            break;
        }
        str = strtok(NULL, ",");
    }
}

/**
 * Look through every department for the course and return the department.
 * O(d log(n)). d is usually small so just O(log(n))
 */
Department *Graph_findDepartmentOfCourse(Graph *graph, char *courseName) {
    for (size_t i = 0; i < graph->departments->size; i++) {
        Department *department = ArrayList_get(graph->departments, i);
        Course *course = BinaryTree_find(department->courses, courseName);
        if (course != NULL) {
            return department;
        }
    }
    return NULL;
}

/**
 * Look through every department.
 * O(d log n) but d is usually small so O(log(n))
 */
Course *Graph_findCourse(Graph *graph, char *courseName) {
    for (size_t i = 0; i < graph->departments->size; i++) {
        Department *department = ArrayList_get(graph->departments, i);
        Course *course = BinaryTree_find(department->courses, courseName);
        if (course != NULL) {
            return course;
        }
    }
    return NULL;
}

/**
 * Go through every degree and try to find the course in the 2d linked list.
 * If found, add the degree to the degrees string separated by the delimiter.
 * O(n) because n courses total, each degree has a 2D linked list so it totals up to all courses.
 */
void Graph_findDegreesStr(Graph *graph, char *courseName, char *degrees, char* delimiter) {
    Course *course = NULL;
    strcpy(degrees, "");
    Degree *degree;
    bool first = true;
    /**
     * Go through every degree and check if course in any list.
     */
    for (size_t i = 0; i < graph->degrees->size; i++) {
        degree = ArrayList_get(graph->degrees, i);
        /**
         * Use special comparator to make life easy.
         */
        course = LinkedList_find(degree->reqs->ands, courseName,
                                 Requirements_innerListFindComparator);
        if (course != NULL) {
            if (!first) {
                strcat(degrees, delimiter);
            }
            strcat(degrees, degree->name);
            first = false;
        }
    }
}

/**
 * First find student and degree then
 * [erform set difference for the student's degree and print it
 */
void Graph_describeDegreeReq(Graph *graph, char *studentName) {
    Student *student = ArrayList_find(graph->students, studentName, Student_compareString);
    if (student == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    Degree *degree = ArrayList_find(graph->degrees, student->degree, Degree_compareString);
    if (degree == NULL) {
        printf("ERROR, DEGREE NOT FOUND.\n");
        return;
    }
    /**
     * Create a new Requirements object, to easily print out.
     */
    Requirements *remaining = malloc(sizeof(Requirements));
    Requirements_init(remaining);
    Requirements_findDifference(degree->reqs, student->courses, remaining);
    char line[MAX_LINE_LENGTH], delim[] = "\n";
    Requirements_toString(remaining, line, delim);
    printf("%s", line);
    Requirements_free(remaining, dont_free);
    free(remaining);
}

/**
 * Find student, degree, then perform set difference.
 * Then, for every course in that set difference check if the student's courses
 * meet its prereqs. If so, print.
 * Set difference is O(nlogn) (loop then lookup in binary tree)
 * Assume O(n/10) = O(n) courses in set difference.
 *
 * Find course is O(n) so we are currently at O(n^2) Then we have to try to find all of
 * them in the binary tree so that is O(log(n))
 * summing up to O(n^2 log(n))
 *
 * With pointers we would have an O(nlog(n)) as we would save the O(n) course look up.
 */
void Graph_describeNextDegreeReqs(Graph *graph, char* studentName) {
    Student *student = ArrayList_find(graph->students, studentName, Student_compareString);
    if (student == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    Degree *degree = ArrayList_find(graph->degrees, student->degree, Degree_compareString);
    if (degree == NULL) {
        printf("ERROR, DEGREE NOT FOUND.\n");
        return;
    }
    Requirements *remaining = malloc(sizeof(Requirements));
    Requirements_init(remaining);
    Requirements_findDifference(degree->reqs, student->courses, remaining);
    /**
     * each currLine is a LinkedList. The loop then looks again at each element.
     */
     for (Node *currLine = remaining->ands->head; currLine != NULL;currLine = currLine->next) {
         LinkedList *courseList = (LinkedList *) currLine->data;
         for (Node *currCourse = courseList->head; currCourse != NULL; currCourse = currCourse->next) {
             bool canTake = true;
             /**
              * Find the course from the set difference.
              */
             Course *course = Graph_findCourse(graph, currCourse->data);
             /**
              * Now look at all of the sttudents courses and try to see if prereqs are met.
              */
             for (Node *curr = course->prereqs->ands->head; curr != NULL; curr = curr->next) {
                 /**
                  * The comparator handles the OR requirement. This for loop handles
                  * the AND requirement. All prereqs need to be met for it to be printed.
                  */
                 LinkedList *ors = (LinkedList *) curr->data;
                 char *found = LinkedList_find(ors, student->courses, BinaryTree_findComparator);
                 if (found == NULL) {
                     canTake = false;
                     break;
                 }
             }
             if (canTake) printf("%s\n", course->name);
         }
     }

    Requirements_free(remaining, dont_free);
    free(remaining);
}

/**
 * Remove the course first from the department, O(log(n)), then from degrees O(n)
 * then from all courses' prereqs O(pn) Since prereqs are small,
 * it is essentially O(n)
 */
void Graph_removeCourse(Graph *graph, char *line) {
    if (line == NULL) return;
    char *str;
    // First, parse department
    str = strtok(line, ",");
    if (str == NULL) {
        printf("ERROR REMOVING COURSE\n");
        return;
    }
    Department *department = ArrayList_find(graph->departments, str, Department_compareString);
    if (department == NULL) {
        printf("CANNOT REMOVE COURSE. DEPARTMENT NOT FOUND\n");
        return;
    }

    // Next, parse course name and title
    str = strtok(NULL, ",");
    if (str == NULL) {
        printf("ERROR REMOVING COURSE\n");
        return;
    }
    str++;
    Course *course = BinaryTree_find(department->courses, str);
    if (course == NULL) {
        printf("Course not in Department\n");
    } else {
        BinaryTree_remove(department->courses, str, Department_courseFree);
    }

    // Remove from Degrees
    for (size_t i = 0; i < graph->degrees->size; i++) {
        Degree_removeCourse(ArrayList_get(graph->degrees, i), str);
    }

    // Remove from prereqs
    Course *parent;
    for (size_t i = 0; i < graph->departments->size; i++) {
        department = ArrayList_get(graph->departments, i);
        ArrayList *list = malloc(sizeof(ArrayList));
        ArrayList_init(list);
        BinaryTree_serialize(department->courses, list);
        for (size_t j = 0; j < list->size; j++) {
            parent = ArrayList_get(list, j);
            Requirements_removeCourse(parent->prereqs, str);
        }
        ArrayList_free(list, dont_free);
        free(list);
    }

}


/**
 * Goes through every possible course and checks if it has a prereq with
 * courseName. If so, prints the parent course out. Also prints the degrees
 * associated with courseName
 *
 * O(a d n) + O(dn) where n is the number of courses. Note that since the number
 * of prereqs is always low (1-3), and so is degrees it is just O(n) + O(n) = O(n)
 */
void Graph_describeCourseEffect(Graph *graph, char *courseName) {
    Course *course = Graph_findCourse(graph, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    Department *department;
    bool first = true;
    /**
     * Go through every department.
     */
    for (size_t i = 0; i < graph->departments->size; i++) {
        department = ArrayList_get(graph->departments, i);
        /**
         * Go through every course and check if this is a prereq for any of them.
         * Use special comparator to check, and print it if it is.
         */
        ArrayList *list = malloc(sizeof(ArrayList));
        ArrayList_init(list);
        BinaryTree_serialize(department->courses, list);
        for (size_t j = 0; j < list->size; j++) {
            Course *parent = ArrayList_get(list, j);
            /**
             * Comparator finds the course in the list without needing another for loop
             */
            Course *foundPrereq = LinkedList_find(parent->prereqs->ands, course->name,
                                                  Requirements_innerListFindComparator);
            if (foundPrereq != NULL) {
                if (!first) {
                    printf(", "); // Ensures proper delim placement.
                }
                first = false;
                printf("%s", parent->name);
            }
        }
        ArrayList_free(list, dont_free);
        free(list);
    }
    if (first == true) printf("No courses have %s as a pre-requisite", courseName);
    // Many courses could have it as prereq
    char str[MAX_LINE_LENGTH * 2], delim[] = "\n";
    Graph_findDegreesStr(graph, courseName, str, delim);
    printf("\n%s\n", str);
}

/**
 * First find the degree and course then remove it from the degree
 * Should be O(n) to find the course and O(1) to find the degree cause there are only
 * a few degrees.
 */
void Graph_removeCourseDegree(Graph *graph, char *line) {
    if (line == NULL) return;
    char *str;
    // First, parse department
    str = strtok(line, ",");
    if (str == NULL) {
        printf("ERROR REMOVING COURSE\n");
        return;
    }
    Degree *degree = ArrayList_find(graph->degrees, str, Degree_compareString);
    if (degree == NULL) {
        printf("CANNOT REMOVE COURSE. DEGREE NOT FOUND\n");
        return;
    }

    // Next, parse course name and title
    str = strtok(NULL, ",");
    if (str == NULL) {
        printf("ERROR REMOVING COURSE\n");
        return;
    }
    str++;
    Degree_removeCourse(degree, str);
}

/**
 * Print the title and prereqs
 */
void Graph_describeCourse(Graph *graph, char *courseName) {
    Course *course = Graph_findCourse(graph, courseName);
    if (course == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    printf("%s\n", course->title);
    char line[MAX_LINE_LENGTH], delim[] = ", ";
    Requirements_toString(course->prereqs, line, delim);
    printf("%s\n", line);
}

/**
 * Print the reqs
 */
void Graph_describeDegree(Graph *graph, char *degreeName) {
    Degree *degree = ArrayList_find(graph->degrees, degreeName, Degree_compareString);
    if (degree == NULL)  {
        printf("NOT FOUND\n");
        return;
    }
    char courses[LIST_LENGTH]; // List of Max line lengths
    Degree_toString(degree, courses);
    printf("%s", courses);
}

/**
 * Find the department and degrees first, print them and then print the
 * course prereqs in a single line
 */
void Graph_printCourse(Graph *graph, char *courseName) {
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
    if (course->prereqs->ands->size == 0) {
        strcpy(str, "NONE");
    } else {
        Requirements_toString(course->prereqs, str, delim);
    }
    printf("pre-requisites: %s\n", str);

}

/**
 * Print the reqs
 */
void Graph_printDegree(Graph *graph, char *degreeName) {
    Degree *degree = ArrayList_find(graph->degrees, degreeName, Degree_compareString);
    if (degree == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    char str[LIST_LENGTH]; // List of max line lengths
    Degree_toString(degree, str);
    printf("%s", str);
}

/**
 * Print every course by calling Course_toString on all of them
 */
void Graph_printDepartment(Graph *graph, char *departmentName) {
    Department *department = ArrayList_find(graph->departments, departmentName, Department_compareString);
    if (department == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    char str[2 * LIST_LENGTH]; // List of  2* max line lengths
    Department_toString(department, str);
    printf("%s", str);
}

void Graph_printStudent(Graph* graph, char *studentName) {
    Student *student = ArrayList_find(graph->students, studentName, Student_compareString);
    if (student == NULL) {
        printf("NOT FOUND\n");
        return;
    }
    char str[LIST_LENGTH];
    Student_toString(student, str);
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
    ArrayList_toString(graph->students, Student_toString, str);
    printf("Students.\n");
    printf("%s", str);
    free(str);
}

/**
 * Call each of the the wrapper frees for the Arraylists then free the lists themselves
 */
void Graph_free(Graph *graph) {
    ArrayList_free(graph->departments, Graph_departmentFree);
    ArrayList_free(graph->degrees, Graph_degreeFree);
    ArrayList_free(graph->students, Graph_studentFree);
    free(graph->departments);
    free(graph->degrees);
    free(graph->students);
    graph->students = NULL;
    graph->degrees = NULL;
    graph->departments = NULL;
}

void Graph_departmentFree(void *data) {
    Department_free(data);
    free(data);
}

void Graph_studentFree(void *data) {
    Student_free(data);
    free(data);
}

void Graph_degreeFree(void *data) {
    Degree_free(data);
    free(data);
}