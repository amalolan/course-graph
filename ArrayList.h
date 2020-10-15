#ifndef COURSE_GRAPH_ARRAYLIST_H
#define COURSE_GRAPH_ARRAYLIST_H
#define ARRAYLIST_MIN 10

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Types.h"

typedef struct ArrayList_struct {
    void **buf;
    size_t capacity;
    size_t size;
} ArrayList;

extern void ArrayList_init(ArrayList *list);

extern void *ArrayList_get(const ArrayList *list, size_t index);

extern void ArrayList_set(ArrayList *list, size_t index, void *data);

extern void ArrayList_push(ArrayList *list, void *data);

extern void ArrayList_free(ArrayList *list);

extern void ArrayList_toString(ArrayList *list, void (*data_toString)(const void *, char *), char *);

extern void ArrayList_print(ArrayList *list, void (*data_toString)(const void *, char *));


#endif //COURSE_GRAPH_ARRAYLIST_H
