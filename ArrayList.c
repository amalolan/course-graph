#include "ArrayList.h"

/**
 * Allocate size of element * capacity for the array
 */
void ArrayList_init(ArrayList *list) {
    if (list == NULL) return;
    list->capacity = ARRAYLIST_MIN;
    list->buf = malloc(sizeof(*list->buf) * list->capacity);
    list->size = 0;
}

/**
 * set the array element at the index
 */
void *ArrayList_get(const ArrayList *list, size_t index) {
    if (list == NULL) return NULL;
    return list->buf[index];
}

/**
 * set the array element at the index
 */
void ArrayList_set(ArrayList *list, size_t index, void *data) {
    if (list == NULL || data == NULL) return;
    list->buf[index] = data;
}

/**
 * Don't push duplicate pointers. If capacity is reached, double and realloc
 */
void ArrayList_push(ArrayList *list, void *data) {
    if (list == NULL || data == NULL) return;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->buf = realloc(list->buf, sizeof(*list->buf) * list->capacity);
    }
    ArrayList_set(list, list->size++, data);
}

/**
 * Destruct array by individually freeing every element of the array.
 * Then, free the array itself, and reset size.
 */
void ArrayList_free(ArrayList *list, void (*data_free)(void *)) {
    if (list == NULL) return;
    for (size_t i = 0; i < list->size; i++) {
        data_free(list->buf[i]);
    }
    free(list->buf);
    list->buf = NULL;
    list->size = 0;
    list->capacity = 0;
}

/**
 * Look through the array, and use the comparator do determine a match
 */
int ArrayList_index(ArrayList *list, const void *data, int (*compare)(const void *, const void *)) {
    for (size_t i = 0; i < list->size; i++) {
        void *value = ArrayList_get(list, i);
        if (compare(value, data) == 0) return i;
    }
    return -1;
}

/**
 * Use ArrayList_index() to find the index then return the element at that index
 */
void *ArrayList_find(ArrayList *list, const void *data, int (*compare)(const void *, const void *)) {
    int index = ArrayList_index(list, data, compare);
    if (index == -1) return NULL;
    else return ArrayList_get(list, index);
}

/**
 * Provide string representation for debugging. Iterate and call each elements
 * respective toString method.
 */
void ArrayList_toString(ArrayList *list, void (*data_toString)(const void *, char *), char *str) {
    if (list == NULL) return;
    sprintf(str, "[");
    // Might print out arraylist of all departments during debugging which can take a lot of space
    char *data_str = malloc(LIST_LENGTH);
    for (size_t i = 0; i < list->size; i++) {
        data_toString(ArrayList_get(list, i), data_str);
        strcat(str, data_str);
        strcat(str, ",");
    }
    free(data_str);
    str[strlen(str) - 1] = 0;
    strcat(str, "]\n");
}
