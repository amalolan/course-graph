#include "Requirements.h"

/**
 * Initialize the LinkedList
 */
void Requirements_init(Requirements *reqs) {
    reqs->ands = malloc(sizeof(LinkedList));
    LinkedList_init(reqs->ands);
}

void Requirements_parseLine(Requirements *reqs, char *line, bool or) {
    if (reqs == NULL) return;
    char lineCopy[MAX_LINE_LENGTH];
    strcpy(lineCopy, line);
    if (or) {
        LinkedList *ors = malloc(sizeof(LinkedList));
        LinkedList_init(ors);
        /**
         * Creates a single linked list for the disjuncts and puts all courses in it.
         * Parses using strtok
         */
        for (char *str=strtok(lineCopy, ","); str != NULL; str = strtok(NULL, ",")) {
            if (str[0] == ' ') str++;
            char *courseName = malloc(TITLE_LEN);
            strcpy(courseName, str);
            LinkedList_push(ors, courseName);
        }
        LinkedList_push(reqs->ands, ors);
    } else {
        /**
         * This loop creates a single linked list for each individual AND course.
         * It appends each list to reqs->ands
         * Uses strtok to parse through commas
         */
        for (char *str=strtok(lineCopy, ","); str != NULL; str = strtok(NULL, ",")) {
            if (str[0] == ' ') str++;
            LinkedList *single = malloc(sizeof(LinkedList));
            LinkedList_init(single);
            char *courseName = malloc(TITLE_LEN);
            strcpy(courseName, str);
            LinkedList_push(single, courseName);
            LinkedList_push(reqs->ands, single);
        }
    }
}

void Requirements_removeCourse(Requirements *reqs, char *courseName) {
    /**
     * Loop through all courses
     */
    for (Node *node = reqs->ands->head; node != NULL; node = node->next) {
        LinkedList *ors = (LinkedList *) node->data;
        if (LinkedList_remove(ors, courseName, string_compare, free_data)) {
            // Remove if found. Also if a 1 size list was removed from, delete that list from reqs
            if (ors->size == 0) {
                LinkedList_remove(reqs->ands, ors, direct_compare, free_data);
            }
            return;
        }
    }
}

void Requirements_findDifference(Requirements *reqs, BinaryTree *courseStrings, Requirements *remaining) {
    /**
     * each curr is a LinkedList. The loop then looks again at each element.
     */
    for (Node *curr = reqs->ands->head; curr != NULL; curr = curr->next) {
        LinkedList *ors = (LinkedList *) curr->data;
        char *found = LinkedList_find(ors, courseStrings, BinaryTree_findComparator);
        if (found == NULL) {
            // If not found then by definition, it is in the set difference. Append it t remaining.
            LinkedList_push(remaining->ands, ors);
        }
    }
}

void Requirements_toString(Requirements *reqs, char *str, char *delim) {
    strcpy(str, "");
    /**
     * each node is a LinkedList. The loop then looks again at each element.
     */
    for (Node *node = reqs->ands->head; node != NULL; node = node->next) {
        LinkedList *ors = (LinkedList *) node->data;
        if (ors->size > 1) {
            strcat(str, "OR ");
        }
        for (Node *courseNode =ors->head; courseNode != NULL; courseNode = courseNode->next) {
            strcat(str, courseNode->data);
            strcat(str, ", ");
        }
        str[strlen(str) - 2] = 0; // Remove extra , and space
        strcat(str, delim);
    }
    if (strlen(delim) > 1) str[strlen(str) - strlen(delim)] = 0; // Remove delim
}

/**
 * If two is in one, it returns 0 else -1. Useful to avoid a for loop
 * when checking if two is present in one.
 */
int Requirements_innerListFindComparator(const void *one, const void *two) {
    LinkedList *innerList = (LinkedList*)one;
    char *courseName = (char*) two;
    char *findData = LinkedList_find(innerList, courseName, string_compare);
    if (findData == NULL) return -1;
    return 0;
}

/**
 * Free the individual data elements and then free the list itself.
 */
void Requirements_innerListFree(void *list) {
    LinkedList_free(list, free_data);
    free(list);
}

/**
 * Destruct the outer linked list and then free the variable
 * data_free is usually Requirements_innerListFree except in cases when
 * the inner lists were copied over
 */
void Requirements_free(Requirements *reqs, void (*data_free)(void *)) {
    LinkedList_free(reqs->ands, data_free);
    free(reqs->ands);
    reqs->ands = NULL;
}