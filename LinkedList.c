#include "LinkedList.h"

void LinkedList_init(LinkedList *list) {
    if (list == NULL) return;
    list->head = NULL;
    list->size = 0;
}

/**
 * data * needs to be unique, don't push non-unique pointers.
 * Failsafe check in place
 */
void LinkedList_push(LinkedList *list, void *data) {
    if (list == NULL || data == NULL) return;

    if (list->size == 0) {
        Node *node = malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        list->head = node;
    } else {
        /*
         * Find the last node then append it there
         */
        Node *curr = list->head;
        if (curr->data == data) return;
        while (curr->next != NULL) {
            if (curr->next->data == data) return;
            curr = curr->next;
        }
        Node *node = malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        curr->next = node;
    }
    list->size++;
}
/**
 * find using the comparator provided
 */
void * LinkedList_find(const LinkedList *list, const void *data, int (*compare)(const void *, const void *)) {
    if (list == NULL || data == NULL) return NULL;
    // conside for loop
    for (Node *curr = list->head; curr != NULL; curr = curr->next)  {
        if (compare(curr->data, data) == 0) {
            return curr->data;
        }
    }
    return NULL;
}

/**
 * consider two cases for removal, head and non-head. Simply manipulate where
 * the nodes point to and free the removed node by calling its destructor
 */
bool LinkedList_remove(LinkedList *list, const void *data, int (*compare)(const void *, const void *),
                         void (*data_free)(void *)) {
    if (list == NULL || data == NULL) return false;

    for (Node *curr = list->head, *prev = NULL; curr != NULL; curr = curr->next) {
        if (compare(curr->data, data) == 0) {
            if (prev == NULL) {
                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            list->size--;
            // Now the data has been removed. Can be freed.
            data_free(curr->data);
            free(curr);
            return true;
        }
        prev = curr;

    }
    return false;
}

/**
 * Iteratively free all data then their nodes.
 */
void LinkedList_free(LinkedList *list, void (*data_free)(void *)) {
    if (list == NULL) return;
    for ( Node *curr = list->head, *next; curr != NULL;  curr = next) {
        next = curr->next;
        data_free(curr->data);
        free(curr);
    }
    list->head = NULL;
    list->size = 0;
}

