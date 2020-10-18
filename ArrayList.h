#ifndef COURSE_GRAPH_ARRAYLIST_H
#define COURSE_GRAPH_ARRAYLIST_H
#define ARRAYLIST_MIN 10

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Util.h"

typedef struct ArrayList_struct {
    void **buf;
    size_t capacity;
    size_t size;
} ArrayList;

void ArrayList_init(ArrayList *list);

void *ArrayList_get(const ArrayList *list, size_t index);

void ArrayList_set(ArrayList *list, size_t index, void *data);

void ArrayList_push(ArrayList *list, void *data);

void ArrayList_free(ArrayList *list, void (*data_free)(void *));

void ArrayList_toString(ArrayList *list, void (*data_toString)(const void *, char *), char *);

int ArrayList_index(ArrayList *list, const void *data, int (*compare)(const void *, const void *));

void *ArrayList_find(ArrayList *list, const void *data, int (*compare)(const void *, const void *));

#endif //COURSE_GRAPH_ARRAYLIST_H
