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
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->size == 0) {
        list->head = node;
    } else {
        Node *curr = list->head;
        if (curr->data == data) return;
        while (curr->next != NULL) {
            if (curr->next->data == data) return;
            curr = curr->next;
        }
        curr->next = node;
    }
    list->size++;
}

bool LinkedList_in(const LinkedList *list, const void *data, int (*compare)(const void *, const void *)) {
    if (list == NULL || data == NULL) return false;
    Node *curr = list->head;
    while (curr != NULL) {
        if (compare(curr->data, data) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
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
    free(list);
}

void LinkedList_toString(LinkedList *list, void (*data_toString)(const void *, char*), char*str) {
    if (list == NULL) return;
    strcat(str, "[");
    Node *curr = list->head;
    char *data_str = malloc(100);
    while (curr != NULL) {
        data_toString(curr->data, data_str);
        strcat(str, data_str);
        strcat(str, ",");
        curr = curr->next;
    }
    free(data_str);
    str[strlen(str)-1] = 0;
    strcat(str, "]\n");
}

void LinkedList_print(LinkedList *list, void (*data_toString)(const void *, char*)) {
    if (list == NULL) return;
    char *list_str = malloc(10000);
    strcpy(list_str, "");
    LinkedList_toString(list, data_toString, list_str);
    printf("%s", list_str);
    fflush(stdout);
    free(list_str);
}


void LinkedList_delete(LinkedList *list, const void *data, int (*compare)(const void *, const void *), void
(*data_free)(void *)) {
    if (list == NULL || data == NULL) return;
    Node *curr = list->head, *prev = NULL;
    while (curr != NULL) {
        if (compare(curr->data, data) == 0) {
            prev->next = curr->next;
            curr->next = NULL;
            list->size--;
            data_free(curr->data);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
