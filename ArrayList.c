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

void ArrayList_push(ArrayList *list, void *data) {
    if (list == NULL || data == NULL) return;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->buf = realloc(list->buf, sizeof(*list->buf) * list->capacity);
    }
    ArrayList_set(list, list->size++, data);
}

void ArrayList_free(ArrayList *list) {
    if (list == NULL) return;
    free(list->buf);
}


void ArrayList_toString(ArrayList *list, void (*data_toString)(const void *, char*), char* str) {
    if (list == NULL) return;
    strcat(str, "[");
    char *data_str = malloc(100);
    for (size_t i = 0; i < list->size; i++) {
        data_toString(ArrayList_get(list, i), data_str);
        strcat(str, data_str);
        strcat(str, ",");
    }
    free(data_str);
    str[strlen(str)-1] = 0;
    strcat(str, "]\n");
}

void ArrayList_print(ArrayList *list, void (*data_toString)(const void *, char *)) {
    if (list == NULL) return;
    char *list_str = malloc(10000);
    strcpy(list_str, "");
    ArrayList_toString(list, data_toString, list_str);
    printf("%s", list_str);
    free(list_str);
    fflush(stdout);
}