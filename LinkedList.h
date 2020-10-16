#ifndef COURSE_GRAPH_LINKEDLIST_H
#define COURSE_GRAPH_LINKEDLIST_H

#include "stdbool.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Types.h"

typedef struct Node_struct {
    void *data;
    struct Node_struct *next;
} Node;

typedef struct LinkedList_struct {
    Node *head;
    size_t size;
} LinkedList;

void LinkedList_init(LinkedList *list);

void LinkedList_push(LinkedList *list, void *data);

bool LinkedList_in(const LinkedList *list, const void *data, int (*compare)(const void *, const void *));

void LinkedList_delete(LinkedList *list, const void *data, int (*compare)(const void *, const void *), void
(*data_free)(void *));

void LinkedList_free(LinkedList *list, void (*data_free)(void *));

void LinkedList_toString(LinkedList *list, void (*data_toString)(const void *, char *), char *);

void LinkedList_print(LinkedList *list, void (*data_toString)(const void *, char *));


#endif //COURSE_GRAPH_LINKEDLIST_H
