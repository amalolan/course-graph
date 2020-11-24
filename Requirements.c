#include "Requirements.h"

void Requirements_init(Requirements *reqs) {
    reqs->ands = malloc(sizeof(LinkedList));
    LinkedList_init(reqs->ands);
}

void Requirements_parseLine(Requirements *reqs, char *line, bool or) {
    if (reqs == NULL) return;
    if (or) {
        LinkedList *ors = malloc(sizeof(LinkedList));
        LinkedList_init(ors);
        for (char *str=strtok(line, ","); str != NULL; str = strtok(NULL, ",")) {
            if (str[0] == ' ') str++;
            char *courseName = malloc(TITLE_LEN);
            strcpy(courseName, str);
            LinkedList_push(ors, courseName);
        }
        LinkedList_push(reqs->ands, ors);
    } else { // ands
        for (char *str=strtok(line, ","); str != NULL; str = strtok(NULL, ",")) {
            if (str[0] == ' ') str++;
            Requirements_parseLine(reqs, str, true);
        }
    }
}

void Requirements_removeCourse(Requirements *reqs, char *courseName) {
    for (Node *node = reqs->ands->head; node != NULL; node = node->next) {
        LinkedList *ors = (LinkedList *) node->data;
        if (LinkedList_remove(ors, courseName, string_compare, free_data)) {
            if (ors->size == 0) {
                LinkedList_remove(reqs->ands, ors, direct_compare, free_data);
            }
            return;
        }
    }
}

void Requirements_findDifference(Requirements *reqs, BinaryTree *courseStrings, Requirements *remaining) {
    /**
     * each currLine is a LinkedList. The loop then looks again at each element.
     */
    for (Node *curr = reqs->ands->head; curr != NULL; curr = curr->next) {
        LinkedList *ors = (LinkedList *) curr->data;
        char *found = LinkedList_find(ors, courseStrings, BinaryTree_findComparator);
        if (found == NULL) {
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
    if (strlen(delim) > 1) str[strlen(str) - strlen(delim) + 1] = 0; // Remove delim
}

void Requirements_innerListFree(void *list) {
    LinkedList_free(list, free_data);
    free(list);
}

void Requirements_free(Requirements *reqs, void (*data_free)(void *)) {
    LinkedList_free(reqs->ands, data_free);
    free(reqs->ands);
    reqs->ands = NULL;
}