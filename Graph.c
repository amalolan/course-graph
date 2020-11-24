#include "Graph.h"

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

// no \n
void Graph_addCourse(Graph *graph, char *line) {
    if (line == NULL) return;
    char *str;
    char courseName[COURSE_NAME_LEN];
    // First, parse department
    str = strtok(line, ",");
    if (str == NULL) {
        printf("ERROR ADDING COURSE\n");
        return;
    }
    Department *department = ArrayList_find(graph->departments, str, Department_compareString);
    if (department == NULL) {
        printf("CANNOT ADD COURSE. DEPARTMENT NOT FOUND\n");
        return;
    }

    // Next, parse course name and title
    str = strtok(NULL, ",");
    if (str == NULL) {
        printf("ERROR ADDING COURSE\n");
        return;
    }
    str++;
    strcpy(courseName, str);

    str = strtok(NULL, ",");
    if (str == NULL) {
        printf("ERROR ADDING COURSE\n");
        return;
    }
    str++;
    Course *course = malloc(sizeof(Course));
    Course_init(course, courseName, str);
    Department_addCourse(department, course);

    // Finally, parse prereqs
    str = strtok(NULL, ",");
    bool disjunct = false;
    while (str != NULL) {
        str++;
        if (strlen(str) < 2) {
            printf("ERROR ADDING COURSE\n");
            return;
        }
        if (str[0] == 'O' && str[1] == 'R') {
            str += 3;
            disjunct = true;
        }
        char *prereqName = malloc(COURSE_NAME_LEN);
        strcpy(prereqName, str);
        LinkedList_push(course->prereqs, prereqName);
        str = strtok(NULL, ",");
        if (! disjunct) break;
    }
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
    /**
     * Go through every degree and check if course in any list.
     */
    for (size_t i = 0; i < graph->degrees->size; i++) {
        degree = ArrayList_get(graph->degrees, i);
        /**
         * Use special comparator to make life easy.
         */
        course = LinkedList_find(degree->reqs, courseName, Degree_compareCourseLineString);
        if (course != NULL) {
            if (!first) {
                strcat(degrees, delimiter);
            }
            strcat(degrees, degree->name);
            first = false;
        }
    }
//    if (graph->degrees->size > 0) {
//        degrees[strlen(degrees) - strlen(delimiter) + 1] = 0; // Remove extra delimiter
//    }
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
}

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
    LinkedList *reqs = malloc(sizeof(LinkedList));
    LinkedList_init(reqs);
    Degree_findReqsDifference(degree, student->courses, reqs);
    char line[MAX_LINE_LENGTH];
    Degree_reqsToString(reqs, line);
    printf("%s", line);
    LinkedList_free(reqs, dont_free);
    free(reqs);
}

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
    LinkedList *reqs = malloc(sizeof(LinkedList));
    LinkedList_init(reqs);
    Degree_findReqsDifference(degree, student->courses, reqs);

    Node *currLine = reqs->head;
    /**
     * each currLine is a LinkedList. The loop then looks again at each elemen.
     */
    while (currLine != NULL) {
        LinkedList *courseList = (LinkedList *) currLine->data;
        Node *currCourse = courseList->head;
        while (currCourse != NULL) {
            bool prereqMet = false;
            Course *course = Graph_findCourse(graph, currCourse->data);
            if (course->prereqs->size == 0) {
                prereqMet = true;
            } else {
                Node *prereq = course->prereqs->head;
                while (prereq != NULL) {
                    if (ArrayList_find(student->courses, prereq->data, string_compare) != NULL) {
                        prereqMet = true;
                        break;
                    }
                    prereq = prereq->next;
                }
            }
            if (prereqMet) {
                printf("%s\n", course->name);
            }
            currCourse = currCourse->next;
        }
        currLine = currLine->next;
    }


    LinkedList_free(reqs, dont_free);
    free(reqs);
}

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
    int index = ArrayList_index(department->courses, str, Course_compareString);
    if (index == -1) {
        printf("Course not in Department\n");
    } else {
        Course *course  = ArrayList_get(department->courses, index); // TODO: Binary Tree
        Course_free(course);
        free(course);
        course = malloc(sizeof(Course));
        Course_init(course, "DEL", "DELETED");
        ArrayList_set(department->courses, index, course);
    }
    // TODO: Remove from department->courses binary tree

    // Remove from Degrees
    for (size_t i = 0; i < graph->degrees->size; i++) {
        Degree_removeCourse(ArrayList_get(graph->degrees, i), str);
    }

    // Remove from prereqs
    Course *parent;
    for (size_t i = 0; i < graph->departments->size; i++) {
        department = ArrayList_get(graph->departments, i);
        for (size_t j = 0; j < department->courses->size; j++) {
            parent = ArrayList_get(department->courses, j); // TODO: Binary Tree
            LinkedList_remove(parent->prereqs, str, string_compare, data_free);
        }
    }

}

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
    /**
     * Go through every department.
     */
    for (size_t i = 0; i < graph->departments->size; i++) {
        department = ArrayList_get(graph->departments, i);
        /**
         * Go through every course and check if this is a prereq for any of them.
         * Use special compator to check, and print it if it is.
         */
        for (size_t j = 0; j < department->courses->size; j++) {
            Course *parent = ArrayList_get(department->courses, j);
            Course *foundPrereq = LinkedList_find(parent->prereqs, course->name, string_compare);
            if (foundPrereq != NULL) {
                if (!first) {
                    printf(", "); // Ensures proper delim placement.
                }
                first = false;
                printf("%s", parent->name);
            }
        }
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