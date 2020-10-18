#ifndef COURSE_GRAPH_LINKEDLIST_H
#define COURSE_GRAPH_LINKEDLIST_H

#include "stdbool.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Util.h"
/**
 * Node for a linked list. Uses void* to point to data.
 */
typedef struct Node_struct {
    void *data;
    struct Node_struct *next;
} Node;

/**
 * Singly-LinkedList implementation using void * ptrs
 */
typedef struct LinkedList_struct {
    Node *head;
    size_t size;
} LinkedList;

/**
 * Initializes the linked list. Needs mem to be allocated
 * @param list The pointer to allocated memory.
 */
void LinkedList_init(LinkedList *list);

/**
 * Appends data to the end of the list
 * @param list Initialized list
 * @param data Data to append
 */
void LinkedList_push(LinkedList *list, void *data);

/**
 * Searches for an element in the list based on a comparator. Returns the
 * element if found. Useful when looking for Course object based on courseName.
 * We can use a special comparator to fetch the object associated with that name.
 * @param list an inialized list
 * @param data the data to find
 * @param compare the comparator function
 * @return NULL if not found, void* pointer to the found data.
 */
void * LinkedList_find(const LinkedList *list, const void *data, int (*compare)(const void *, const void *));

/**
 * Destructs an initialized list.
 * @param list initialized list.
 * @param data_free destructor of the elements of this list.
 */
void LinkedList_free(LinkedList *list, void (*data_free)(void *));



#endif //COURSE_GRAPH_LINKEDLIST_H
