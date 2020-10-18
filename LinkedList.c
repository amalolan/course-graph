#include "LinkedList.h"

void LinkedList_init(LinkedList *list) {
    if (list == NULL) return;
    list->head = NULL;
    list->size = 0;
}

// data ptr needs to be unique, don't push non-unique pointers.
// Failsafe check in place
void LinkedList_push(LinkedList *list, void *data) {
    if (list == NULL || data == NULL) return;

    if (list->size == 0) {
        Node *node = malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        list->head = node;
    } else {
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

void * LinkedList_find(const LinkedList *list, const void *data, int (*compare)(const void *, const void *)) {
    if (list == NULL || data == NULL) return false;
    Node *curr = list->head;
    while (curr != NULL) {
        if (compare(curr->data, data) == 0) {
            return curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

void LinkedList_free(LinkedList *list, void (*data_free)(void *)) {
    if (list == NULL) return;
    Node *curr = list->head, *next;
    while (curr != NULL) {
        next = curr->next;
        data_free(curr->data);
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->size = 0;
}

