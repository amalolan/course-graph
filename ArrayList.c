#include "ArrayList.h"

void ArrayList_init(ArrayList *list) {
    if (list == NULL) return;
    list->capacity = ARRAYLIST_MIN;
    list->buf = malloc(sizeof(*list->buf) * list->capacity);
    list->size = 0;
}

void *ArrayList_get(const ArrayList *list, size_t index) {
    if (list == NULL) return NULL;
    return list->buf[index];
}

void ArrayList_set(ArrayList *list, size_t index, void *data) {
    if (list == NULL || data == NULL) return;
    list->buf[index] = data;
}

// Don't push duplicate pointers
void ArrayList_push(ArrayList *list, void *data) {
    if (list == NULL || data == NULL) return;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->buf = realloc(list->buf, sizeof(*list->buf) * list->capacity);
    }
    ArrayList_set(list, list->size++, data);
}


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

int ArrayList_index(ArrayList *list, const void *data, int (*compare)(const void *, const void *)) {
    for (size_t i = 0; i < list->size; i++) {
        void *value = ArrayList_get(list, i);
        if (compare(value, data) == 0) return i;
    }
    return -1;
}

void *ArrayList_find(ArrayList *list, const void *data, int (*compare)(const void *, const void *)) {
    int index = ArrayList_index(list, data, compare);
    if (index == -1) return NULL;
    else return ArrayList_get(list, index);
}


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
