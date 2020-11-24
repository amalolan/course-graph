#ifndef COURSE_GRAPH_ARRAYLIST_H
#define COURSE_GRAPH_ARRAYLIST_H
#define ARRAYLIST_MIN 10

    #include <stdio.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include "Util.h"

/**
 * ArrayList implements resizable array. Doubles when capacity is reached.
 * Starts with ARRAYLIST_MIN elements (10).
 * Uses void * pointer as universal pointer.
 */
typedef struct ArrayList_struct {
    void **buf;
    size_t capacity;
    size_t size;
} ArrayList;

/**
 * Allocates memory for the array buf.
 * @param list A list that has memory allocated
 */
void ArrayList_init(ArrayList *list);

/**
 * Fetchs the ith element in the array
 * @param list An initialized list
 * @param index The index to fetch
 * @return The pointer to the object at that index
 */
void *ArrayList_get(const ArrayList *list, size_t index);

/**
 * Sets the array's value at that index to a pointer to an element
 * @param list An initialized list with size > index
 * @param index The index to set with data
 * @param data The pointer to store in the ArrayList
 */
void ArrayList_set(ArrayList *list, size_t index, void *data);

/**
 * Pushes an element to the end of the ArrayList. If too small, resizes by doubling.
 * @param list An initialized list
 * @param data The pointer to store at the end
 */
void ArrayList_push(ArrayList *list, void *data);

/**
 * Destructs the array list. Frees buf and calls free_data on the data to free whatever
 * the data needs to free.
 * @param list The ArrayList to free.
 * @param data_free destructor function for the data. Depending on the type of data, destructs and frees memory.
 */
void ArrayList_free(ArrayList *list, void (*data_free)(void *));

/**
 * Provides a string representation of the ArrayList for debugging.
 * @param list An initialized ArrayList
 * @param data_toString Function that gives the string representation of the each element
 * @param str The string to store in. Must have enough space allocated or will present with undefined behavior.
 */
void ArrayList_toString(ArrayList *list, void (*data_toString)(const void *, char *), char *str);

/**
 * Returns the  index of an element if found in the list (first occurence only).
 * @param list An intialized ArrayList
 * @param data The data to search for
 * @param compare The comparator function that tells us if we have a match between
 *                an element of the ArrayList and the data.
 * @return -1 if not found, else the index data was found at.
 */
int ArrayList_index(ArrayList *list, const void *data, int (*compare)(const void *, const void *));

/**
 * Returns the element in the list if it is found in the list (first occurence only).
 * Useful when we have courseName but want Course. We can send courseName as the *data,
 * and use a special comparator that compares course->name with data.
 * @param list An intialized ArrayList
 * @param data The data to search for
 * @param compare The comparator function that tells us if we have a match between
 *                an element of the ArrayList and the data.
 * @return NULL if not found, else the pointer of the element found.
 */
void *ArrayList_find(ArrayList *list, const void *data, int (*compare)(const void *, const void *));

#endif //COURSE_GRAPH_ARRAYLIST_H
