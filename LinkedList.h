#ifndef COURSE_GRAPH_LINKEDLIST_H
#define COURSE_GRAPH_LINKEDLIST_H

#include "stdbool.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Util.h"

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

void * LinkedList_find(const LinkedList *list, const void *data, int (*compare)(const void *, const void *));

void LinkedList_free(LinkedList *list, void (*data_free)(void *));



#endif //COURSE_GRAPH_LINKEDLIST_H
